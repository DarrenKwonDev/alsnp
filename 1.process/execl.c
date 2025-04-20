#include <unistd.h>
#include <stdio.h>

int main()
{
  if (execl("/bin/ls", "ls", "-al", NULL) == -1)
  {
    perror("execl");
  }

  printf("useless print \n");

  return 0;
}
