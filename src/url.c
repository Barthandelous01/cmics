#ifndef URL_C_
#define URL_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int get_url(char *url, char *file)
{
     FILE *fp = NULL;
     CURL *handle = curl_easy_init();
     if (handle) {
          fp = fopen(file, "w");
          if (fp) {
               curl_easy_setopt(handle, CURLOPT_URL, url);
               curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, NULL);
               curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
          } else {
               return 1;
          }
     } else {
          return 1;
     }
     CURLcode result = curl_easy_perform(handle);
     if (result)
          return 1;

     curl_easy_cleanup(handle);
     free(file);
     fclose(fp);
     return 0;
}

#endif				/* URL_C_ */
