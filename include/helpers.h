/*
 *
 * A simple web server helpers functions prototypes.
 *
 */
 #ifndef HELPERS_H
 #define HELPERS_H

int read_line(int socket, void *vptr, int len);
int write_line(int socket, void *vptr, int len);
int trim(char *buffer);
int to_upper(char * str);
void clean_URL(char * buffer);

 #endif
