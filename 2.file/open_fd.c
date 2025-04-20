#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
  int fd;
  char buf_msg[64];
  
  printf("low level file handle \n");

  if ( (fd = open("fd_test.log", O_CREAT | O_WRONLY, 0644 )) == -1 )
  {
    fprintf(stderr, "Fail : open %d[%s] \n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }

  // dprintf로 쓰기  
  dprintf(fd, "PID(%d) low level file handle \n", getpid());

  // write로 쓰기 
  strcpy(buf_msg, "write: Test message \n");
  write(fd, buf_msg, strlen(buf_msg));

  close(fd);
  return EXIT_SUCCESS;

}
