#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EXPR_SUB_MATCH  10
#define DEFAULT_REGEX_STR   "(</.+>).*<br>"
#define DEFAULT_DEST_STR    "<center>align to center</center> align to left<br>New Line<br><br><p>"

int main(int argc, char **argv)
{
  int i, ret;
  char *p_dest_str;     // 검색할 문자열 (HTML 코드)
  char *p_regex_str;    // 패턴 문자열
  regex_t re_expr;

  /*
   * typedef struct {
   *  regoff_t rm_so;  // 매치 시작 위치 (start offset)
   *  regoff_t rm_eo;  // 매치 끝 위치 (end offset)
   * } regmatch_t;
   */
  regmatch_t rm_matchtab[MAX_EXPR_SUB_MATCH];
  char errbuf[0xff];

  if (argc != 3)
  {
    printf("Using default string!!\n");
    printf("* Dest str : [%s] \n", DEFAULT_DEST_STR);
    printf("* Regex str : [%s] \n", DEFAULT_REGEX_STR);
    p_dest_str = strdup(DEFAULT_DEST_STR);
    p_regex_str = strdup(DEFAULT_REGEX_STR);
  }
  else
  {
    p_dest_str = strdup(argv[1]);
    p_regex_str = strdup(argv[2]);
  }

  // --------------------------------------
  // make regex_t
  if ( (ret = regcomp(&re_expr, p_regex_str, REG_EXTENDED|REG_NEWLINE)) ) // compile a regular expression
  {
    regerror(ret, &re_expr, errbuf, sizeof(errbuf));
    printf("Error regcomp() [%s] \n", errbuf);
    exit(EXIT_FAILURE);
  }
  printf("regcomp : [%s]\n", p_regex_str);

  // --------------------------------------
  // match
  memset(rm_matchtab, 0x00, sizeof(rm_matchtab));
  if (regexec(&re_expr, p_dest_str, MAX_EXPR_SUB_MATCH, rm_matchtab, 0)) // match a null-terminated string against the precompiled pattern buffer
  {
    printf("fail to match\n");
  }
  else 
  {
    // rm_matchtab[0]은 항상 전체 매치 정보를 담습니다.
    // rm_matchtab[1]부터는 괄호()로 그룹화된 서브매치 정보를 담습니다.
    printf("* All Match offset : (%d -> %d), len(%d) : %.*s \n",
           rm_matchtab[0].rm_so,  // 시작
           rm_matchtab[0].rm_eo,  // 끝
           rm_matchtab[0].rm_eo - rm_matchtab[0].rm_so,  // 길이  
           rm_matchtab[0].rm_eo - rm_matchtab[0].rm_so, &p_dest_str[rm_matchtab[0].rm_so]);  // 매칭되는 부분을 출력해보자  

    for (i=1; i<MAX_EXPR_SUB_MATCH; i++)
    {
      // 이 부분이 조금 독특합니다.
      // regexec를 호출한 후, sub match가 없는 부분은 regmatch_t 구조체의 rm_so, rm_eo가 다 -1로 세팅됩니다.
      if (rm_matchtab[i].rm_so == -1) break;
      printf("* Submatch (%d) offset: (%d -> %d), len(%d) : %.*s\n",
             i,
             rm_matchtab[i].rm_so, 
             rm_matchtab[i].rm_eo,
             rm_matchtab[i].rm_eo - rm_matchtab[i].rm_so,
             rm_matchtab[i].rm_eo - rm_matchtab[i].rm_so, &p_dest_str[rm_matchtab[i].rm_so]);
    }

  }

  regfree(&re_expr);
  free(p_dest_str);
  free(p_regex_str);
  return 0;
}
