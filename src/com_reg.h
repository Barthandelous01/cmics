#ifndef COM_REG_C_
#define COM_REG_C_

char *regexp(char *string, char *patrn, int *begin, int *end);
char *get_com_url(char *file /* to search */ ,
		  char *pattern /* to search file for */ );

#endif				/* COM_REG_C_ */
