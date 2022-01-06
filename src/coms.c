#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <stdio.h>		// not sure if this is truly necessary, but...
#include <stdlib.h>
#include <curl/curl.h>
#include <regex.h>

#include "constants.h"
#include "utils.h"

char *proxy;

/**
 * get_url() - Call out to libcurl to download a file into a file
 *
 * @param[in] url: the url to receive
 * @param[in] file: full path to the file to output to
 */
static int get_url(char *url, char *file)
{
	FILE *fp = NULL;
	CURL *handle = curl_easy_init();
	if (handle) {
		fp = fopen(file, "w");
		if (fp) {
			curl_easy_setopt(handle, CURLOPT_URL, url);
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, NULL);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(handle, CURLOPT_PROXY, proxy);
		} else {
			return 1;
		}
	} else {
		return 1;
	}
	CURLcode result = curl_easy_perform(handle);
	if (result) {
		return 1;
		fprintf(stderr, "Request failed. Please check your internet"
			" and proxy settings.\n");
	}


	curl_easy_cleanup(handle);
	fclose(fp);
	return 0;
}

/**
 * regexp() - Perform a length-bounded regex search
 *
 * @param[in] string: the string to search
 * @param[in] patrn: the pattern to search for
 * @param[in/out] begin: the beginning of the match
 * @param[in/out] end: the end of the match
 * @param[out] word: the result, of length `len`
 * @param[in] len: the maximum length of the response buffer
 */
static void regexp(char *string, char *patrn, int *begin, int *end, char *word, int len)
{
	int i = 0, w = 0;
	regex_t rgT;
	regmatch_t match;
	regcomp(&rgT, patrn, REG_EXTENDED);
	if ((regexec(&rgT, string, 1, &match, 0)) == 0) {
		*begin = (int) match.rm_so;
		*end = (int) match.rm_eo;
		for (i = *begin; i < *end; i++) {
			if ((i - *begin) > len)
				break;

			word[w] = string[i];
			w++;
		}
		word[w] = 0;
	}
	regfree(&rgT);
}

/**
 * get_com_url() - Search a file for a regex
 *
 * @param[in] file: the file to search
 * @param[in] pattern: the pattern to search for
 * @param[out] result: the result buffer
 * @param[in] len: the max length of the result buffer
 */
static void get_com_url(char *file, char *pattern, char *result, int len)
{
	/* open file */
	char *buffer = 0;
	FILE *fp;
	fp = fopen(file, "r+");
	/* get size of file for buffer */
	if (fp) {
		fseek(fp, 0, SEEK_END);
		int length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		buffer = malloc(length);
		if (buffer) {
			fread(buffer, 1, length, fp);
		}
	}
	/* init variables for regex */
	int b, e;
	/* perform regex */
	regexp(buffer, pattern, &b, &e, result, len);
	/* extract answer */
	fclose(fp);
	free(buffer);
}

static int log_sql(sqlite3 *db, char *name, int success, char *url)
{
	int rc;
	char *errMsg = 0;
	char *command = malloc(SQL_LOG_LEN);
	if (command == NULL) {
		fprintf (stderr, "%s", "Error allocating memory for SQL command.\n");
		exit(-1);
	}

	/* time */
	time_t curtime;
	struct tm *loc_time;
	curtime = time (NULL);
	loc_time = localtime(&curtime);

	/* build command */
	sprintf(command, "INSERT INTO requests (COMIC, SUCCESS, URL, TIME) "\
		"VALUES ('%s', %d, '%s', '%s');", name, success, url, asctime(loc_time));

	rc = sqlite3_exec(db, command, NULL, 0, &errMsg);

	if (rc != SQLITE_OK) {
		fprintf (stderr, "SQL Error: %s\n", errMsg);
		sqlite3_free(errMsg);
		exit(1);
	}
	free(command);
	return 0;
}

/**
 * env_macro() - Append a home directory to a macro
 *
 * @param[in] macro: The macro to append to
 * @param[out] dest: the destination buffer.
 *
 * Please make careful note that no bounds checking is performed here.
 */
static void env_macro(char *macro, char *dest)
{
	strcpy(dest, getenv("HOME"));
	strcat(dest, macro);
}

#define BUILD_TEMP(macro)			\
	char temp[HOME_DIR_LEN];		\
	env_macro(macro, temp)

#define DOWNLOAD_SITE(name, url)				\
	win_print(win, placement, 2, "===> " name);		\
	win_print(win, placement, 2, "==> Downloading Site");	\
	int res = get_url(url, temp);				\
	error_print(win, placement, res, "Site downloaded!",	\
		"Site not found")

#define DOWNLOAD_IMAGE(macro, url)				\
	win_print(win, placement, 2, "==> Downloading image");	\
	env_macro(macro, temp);					\
	int res2 = get_url(url, temp);				\
	error_print(win, placement, res2, "Image downloaded",	\
		"Image not found")


int get_xkcd(WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(XKCD_HTML);

	DOWNLOAD_SITE("XKCD", "https://xkcd.com/");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	get_com_url(temp, "https://imgs.xkcd.com/comics/[^2\"]*.png", url, COMIC_URL_LEN);

	DOWNLOAD_IMAGE(XKCD_IMG, url);

	log_sql(db, "xkcd", res2, url);
	free(url);
	return 0;
}

int get_bc(WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(BC_HTML);

	DOWNLOAD_SITE("BC", "https://johnhartstudios.com/bc/");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	char final[COMIC_URL_LEN] = "https://johnhartstudios.com";
	get_com_url(temp, "/bcstrips/[^\"]*", url, COMIC_URL_LEN);
	strncat(final, url, COMIC_URL_LEN - 1);

	DOWNLOAD_IMAGE(BC_IMG, final);

	log_sql(db, "bc", res2, final);
	free(url);
	return 0;
}

int get_garfield(WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(GARFIELD_HTML);

	DOWNLOAD_SITE("Garfield", "https://www.gocomics.com/garfield");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	get_com_url(temp, "https://assets.amuniversal.com/[1234567890abcdef]*",
		url, COMIC_URL_LEN);

	DOWNLOAD_IMAGE(GARFIELD_IMG, url);

	log_sql(db, "garfield", res2, url);
	free(url);
	return 0;
}

int get_far_side (WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(FAR_SIDE_HTML);

	DOWNLOAD_SITE("The Far Side", "https://www.thefarside.com");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	get_com_url(temp, "https://assets.thefarside.com/uploads/splash[^\"]*.(png|gif|jpg)",
		url, COMIC_URL_LEN);

	DOWNLOAD_IMAGE(FAR_SIDE_IMG, url);

	log_sql(db, "far_side", res2, url);
	free(url);
	return 0;
}

int get_dilbert (WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(DILBERT_HTML);

	DOWNLOAD_SITE("Dilbert", "https://dilbert.com");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	get_com_url(temp, "assets.amuniversal.com/([a-f]|[[:digit:]]){32}",
		url, COMIC_URL_LEN);
	char *final = NULL;
	final = malloc(COMIC_URL_LEN + (1 << 5));
	strcpy(final, "https://");
	strcat(final, url);

	DOWNLOAD_IMAGE(DILBERT_IMG, final);

	log_sql(db, "dilbert", res2, final);
	free(final);
	free(url);
	return 0;
}

int get_family_circus(WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(FAMILY_CIRCUS_HTML);

	DOWNLOAD_SITE("Family Circus", "https://www.arcamax.com/thefunnies/familycircus");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	char final[COMIC_URL_LEN] = "https://resources.arcamax.com";
	get_com_url(temp, "/newspics/[^&\"]*.(jpg|gif|png)", url, COMIC_URL_LEN);
	strcat(final, url);

	DOWNLOAD_IMAGE(FAMILY_CIRCUS_IMG, final);

	log_sql(db, "family_circus", res2, final);
	free(url);
	return 0;
}

int get_beetle_bailey(WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(BEETLE_HTML);

	DOWNLOAD_SITE("Beetle Bailey", "https://www.arcamax.com/thefunnies/beetlebailey");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	char final[COMIC_URL_LEN] = "https://resources.arcamax.com";
	get_com_url(temp, "/newspics/[^n&]*.(gif|jpg|png)", url, COMIC_URL_LEN);
	strcat(final, url);

	DOWNLOAD_IMAGE(BEETLE_IMG, final);

	log_sql(db, "beetle_bailey", res2, final);
	free(url);
	return 0;
}

int get_blondie(WINDOW *win, int *placement, sqlite3 *db)
{
	BUILD_TEMP(BLONDIE_HTML);

	DOWNLOAD_SITE("Blondie", "https://www.arcamax.com/thefunnies/blondie");

	win_print(win, placement, 2, "==> Finding URL of image");
	char *url = NULL;
	url = malloc(COMIC_URL_LEN);
	char final[COMIC_URL_LEN] = "https://resources.arcamax.com";
	get_com_url(temp, "/newspics/[^n&]*.(jpg|gif)", url, COMIC_URL_LEN);
	strcat(final, url);

	DOWNLOAD_IMAGE(BLONDIE_IMG, final);

	log_sql(db, "blondie", res2, final);
	free(url);
	return 0;
}
