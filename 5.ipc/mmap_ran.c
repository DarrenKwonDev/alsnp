#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MMAP_FILENAME   "mmapfile.dat"
#define MMAP_SIZE       64


int main(int argc, char *argv[])
{
  int fd, n_write;
  int flag_mmap = MAP_SHARED;   // shared mmap을 만들 것임  
  char *p_map;
  char a_input[100];
  int cur_len = 0;

  // mmap용으로 쓸 파일 오픈
  if ( (fd = open(MMAP_FILENAME, O_RDWR|O_CREAT, 0664) ) == -1 )
  {
    printf("Fail: open() : (%d:%s)\n", errno, strerror(errno));
    return EXIT_FAILURE;
  }

  // mmap size 이상으로 파일 사이즈를 키우기
  if (ftruncate(fd, MMAP_SIZE) == -1)
  {
    printf("Fail: ftruncate() : (%d:%s)\n", errno, strerror(errno));
    return EXIT_FAILURE;
  }

  // mmap 하기
  if ( (p_map = mmap(NULL, MMAP_SIZE, PROT_READ|PROT_WRITE, flag_mmap, fd, 0)) == MAP_FAILED)
  {
    printf("Fail: mmap() : (%d:%s)\n", errno, strerror(errno));
    return EXIT_FAILURE;
  }

  close(fd);

  printf("mmap file %s \n", MMAP_FILENAME);

  memset(p_map, 0, MMAP_SIZE);

  printf("start \n");

  while( 1 )
  {
    printf(" '*' print current mmap otherwise input text to mmap. >> ");
    if (fgets(a_input, sizeof(a_input), stdin) == NULL)
    {
      printf("Fail: fgets from stdin \n");
    }
    if (a_input[0] == '*')
    {
      printf("Current mmap -> '%.*s' \n", MMAP_SIZE, p_map);
    }
    else 
    {
      if (cur_len + strlen(a_input) <= MMAP_SIZE)
      {
        a_input[strlen(a_input) - 1] = 0; // 의도적으로 개행 문자를 제거한다  
        memcpy(p_map + cur_len, a_input, strlen(a_input));
        
        // 사실상 cur_len이 공유자원임. 메모리 내에 길이를 저장하던가 다른 동기화 방식을 써야 함
        // 그런데 지금은 데모 버전이니까... 그냥 이렇게 내버려 두자.  
        cur_len += strlen(a_input);

        if (msync(p_map, MMAP_SIZE, MS_SYNC) == -1) // blocking sync 한다  
        {
          printf("Fail: msync() : (%d:%s)\n", errno, strerror(errno));
          return EXIT_FAILURE;
        }
      }
      else 
      {  
        printf("Current mmap full -> '%.*s' \n", MMAP_SIZE, p_map);
        return EXIT_SUCCESS;
      }

    }
  }

  return EXIT_SUCCESS;
}
