#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void do_child() { printf("i'm child \n "); }
void do_errorcatch() { printf("err catch  \n "); }
void do_parent() { printf("parent  \n "); }


int main()
{
  int ret = 0;

  switch ( (ret = fork()) )
  {
    case 0:
      do_child();
      break;
    case -1:
      do_errorcatch();
      break;
    default:
      do_parent();
      waitpid(ret, NULL, 0);
      break;
  }

}
