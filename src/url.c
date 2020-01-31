#ifndef URL_C_
#define URL_C_

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

void function_pt(void *ptr, size_t size, size_t nmemb, void *stream) {
  FILE *fp;
  fp = fopen("/tmp/scratch_comichtml", "a+");
  if (fp)
    fputs(ptr, fp);
  fclose(fp);
}

void get_site(char *url) {
  CURL *curl;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
}

#endif /* URL_C_ */
