#include <stdio.h>


void exam_vla(int vlen)
{
  char buffer[vlen];
  printf("size %lu \n", sizeof(buffer) );

}

int main()
{
  #ifdef __STDC_NO_VLA__
    printf("__STDC_NO_VLA__ NO defined");
  #else
    printf("__STDC_NO_VLA__ defined");
  #endif  

  exam_vla(3);  
  exam_vla(5);  
}
