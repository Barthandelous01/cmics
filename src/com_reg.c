#ifndef COM_REG_C_
#define COM_REG_C_

#include <stdlib.h>
#include <stdio.h> // not sure if this is truly necessary, but...
#include <regex.h>
#include <sys/stat.h>

char *regexp (char *string, char *patrn, int *begin, int *end) {
  int i, w=0, len;
  char *word = NULL;
  regex_t rgT;
  regmatch_t match;
  regcomp(&rgT,patrn,REG_EXTENDED);
  if ((regexec(&rgT,string,1,&match,0)) == 0) {
    *begin = (int)match.rm_so;
    *end = (int)match.rm_eo;
    len = *end-*begin;
    word=malloc(len+1);
    for (i=*begin; i<*end; i++) {
      word[w] = string[i];
      w++; }
    word[w]=0;
  }
  regfree(&rgT);
  return word;
}

char *get_com_url(char *file /* to search */, char *pattern /* to search file for */) {
  /* open file */
  FILE *fp;
  fp = fopen(file, "r+");
  /* get size of file for buffer */
  struct stat st;
  stat(file, &st);
  int size = st.st_size;
  /* create and fill buffer */
  char buff[size+1];
  fgets(buff, size, fp);
  /* init variables for regex */
  int b, e;
  /* perform regex */
  char *url;
  url = regexp(buff, pattern, &b, &e);
  /* extract answer */
  char *ans = (char *)malloc(100);
  for (int i = 0; i < (e-b); i++) {
    ans[i] = url[i+b];
  }
  return ans;
}

#endif /* COM_REG_C_ */
