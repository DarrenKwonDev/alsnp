#include <stdio.h>
#include <unistd.h> // // POSIX 기능 매크로가 정의된 헤더

int main(void)
{
  
  #ifdef _POSIX_ASYNCHRONOUS_IO
    printf("_POSIX_ASYNCHRONOUS_IO is defined! \n");
  #else
    printf("_POSIX_ASYNCHRONOUS_IO NOT DEFINED \n");
  #endif


  #ifdef _POSIX_SPAWN
    printf("_POSIX_SPAWN is defined! \n");
  #else
    printf("_POSIX_SPAWN NOT DEFINED \n");
  #endif
}
