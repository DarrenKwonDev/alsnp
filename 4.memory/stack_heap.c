#include <stdio.h>

// 1024 * 1024 는... 
#define SZ_BUFFER 1024 * 1024 

int exhaust_stack(int count)
{
  char buffer[SZ_BUFFER];
  if (count <= 0)
  {
    printf(">> reach breka position, stop recurse \n");
    return 0;
  }
  sprintf(buffer, ">> exhause 1MiB stack(addr : %p), will more %d MiB  \n", buffer, count - 1);
  printf("%s\n", buffer);
  exhaust_stack(count - 1);
  return 0;
}

int main() 
{
  exhaust_stack(10); // ulimit -a 로 stack size 확인해볼 것 
}
