#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int fd = -1;
  if ( (fd = open(argv[1], O_CREAT|O_RDWR, 0644)) < 0)
  {
    printf("open err (%d)[%s]", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  // 이 시점에 보통 file ftruncate 해서 크기는 mmap 사용하고자 하는 만큼 늘림  

  // void *mmap(void addr[.length], size_t length, int prot, int flags, int fd, off_t offset);
  char *p_map = mmap(NULL, 64, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if (p_map == MAP_FAILED)
  {
    printf("mmap err (%d)[%s]", errno, strerror(errno));
    close(fd);
    exit(EXIT_FAILURE);
  }

  // mmap 이 성공적으로 만들어진 후 fd는 닫아도 됨  
  close(fd);

  /* do something with mmap */

  if (msync(p_map, 64, MS_SYNC) == -1)
  {
    printf("msync err (%d)[%s]", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }
 
  if (munmap(p_map, 64) == -1)
  {
    printf("munmap err (%d)[%s]", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}
