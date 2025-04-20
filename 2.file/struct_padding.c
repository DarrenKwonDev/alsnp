#include <stdio.h>
#include <stddef.h>

#define pr_struct(pfix_name)  \
  printf("sizeof(MY_ST_"#pfix_name")=%zd ", sizeof(MY_ST_##pfix_name)); \
  printf("offsetof(...,cnt)=0x%04zx\n", offsetof(MY_ST_##pfix_name,cnt))

typedef struct my_st_a {
        char    str[7];
        char    cnt[4];
} MY_ST_A;

typedef struct my_st_b {
        char    str[7];
        int     cnt;
} MY_ST_B;

typedef struct my_st_c {
        char    str[7];
        short   cnt;
} MY_ST_C;

typedef struct my_st_d {
        char    str[9];
        double  cnt;
} MY_ST_D;

typedef struct my_st_e {
        char    str[9];
        double  cnt;
} __attribute__((packed)) MY_ST_E;

#pragma pack(push, 1)
typedef struct my_st_f {
        char    str[9];
        double  cnt;
} MY_ST_F;
#pragma pack(pop)


int main()
{
        pr_struct(A); // 7 + 4 = 11 
        pr_struct(B); // 7 + (1) + 4 = 12
        pr_struct(C); // 7 + (1) + 2 = 10 ( 2 바이트가 있으면 2바이트 경계까지 진행함. 4 바이트 경계가 아님!)
        pr_struct(D); // 9 + (3) + 8 = 20 
        pr_struct(E); // 9 + 8 = 17 
        pr_struct(F); // 9 + 8 = 17 
        return 0;
}
