#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  #if defined(__GNUC__)
    #if defined(__i386__)
      __asm__("pushf\norl $0x40000, (%esp)\npopf"); /* enable align check on x86*/
    #elif defined(__x86_64__)
      __asm__("pushf\norl $0x40000, (%rsp)\npopf"); /* enable align check on x86_64*/
    #endif
  #endif

  char *p_buf;
  if ( (p_buf = (char *)malloc(sizeof(char) * 65536)) == NULL )
  {
    return EXIT_FAILURE;
  }

  memcpy(p_buf, "1234567890abc", 13);
  //p_buf += 13;
  p_buf += 16;
  *((long *)p_buf) = 123456;
  
  return EXIT_SUCCESS;
}
