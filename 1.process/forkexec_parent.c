#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  pid_t pid_child;
  printf("Parent (%d) : Start \n", getpid());

  int fd = open("forkexec.log", O_WRONLY|O_CREAT|O_APPEND, 0644);
  if (fd == -1)
  {
    perror("FAIL: open");
    exit(EXIT_FAILURE);
  }
  dprintf(fd, "Parent (%d): Open log file (fd = %d) \n", getpid(), fd);

#ifdef APPLY_FD_CLOEXEC
  int ret_fctl;
  if ( (ret_fctl = fcntl(fd, F_SETFD, FD_CLOEXEC)) == -1 )
  {
    perror("FAIL: fcntl");
    exit(EXIT_FAILURE);
  }
#endif

  char *argv_exec[] = { "forkexec_child", (char *)NULL };
  switch ( (pid_child = fork()) )
  {
    case 0:
      execv(argv_exec[0], argv_exec); // 별다른 path 설정이 없으므로 현재 경로에서 forkexec_child 를 찾음   
      // 자식 프로세스인 forkexec_child 에선 FD_CLOEXEC가 없다면 fd를 상속 받아 사용하게 됨  
      break;
    case -1:
      perror("FAIL: FORK");
      break;
    default:
      wait(NULL);
      break;
  }

  printf("Parent (%d) : Exit \n", getpid());

  return 0;
}
