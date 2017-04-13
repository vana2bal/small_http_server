#include "httprequest.h"
#include "helpers.h"
#include "error.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

#define BUFF_MAX_LEN  4096


/* utilities : should parse a string and update request if necessary
   It returns 0 til everyting is fine with the upcoming request
   It return -1 and update Request Status to 400 when something is wrong about
   the request
   It return -1 and update Request Status to 501 when the request method is not
   supported */
static int update_http_request(http_request * request, char * buff) {

        static int is_first_line = 1;
        int resource_len;
        char *endptr,*temp;

        if (is_first_line == 1) {
                /* DECIPHER HTTP METHOD = FIRST WORD OF FIRST LINE */
                if (!strncmp(buff, "GET", 3)) {
                        request->method = GET;
                        buff += 4;
                }
                else if ( !strncmp(buff, "HEAD", 4))  {
                        request->method = HEAD;
                        buff += 5;
                }
                else {
                        request->method = UNSUPPORTED;
                        request->status = 501;
                        return -1;
                }

                while ( *buff && isspace(*buff))
                        buff++;


                /*  Calculate string length of resource...  */

                endptr = strchr(buff, ' ');
                if ( endptr == NULL )
                        resource_len = strlen(buff);
                else
                        resource_len = endptr - buff;
                if ( resource_len == 0 ) {
                        request->status = 400; // Bad request
                        return -1;
                }

                request->resource_name = (char *) malloc((resource_len+1)*sizeof(char));
                if (request->resource_name == NULL)
                        error("Error while allocating memory for resource_name in update_http_request()");
                strncpy(request->resource_name, buff, resource_len);

                buff += resource_len;
                while ( *buff && isspace(*buff))
                        buff++;

                if ( strstr(buff, "HTTP/") ) {
                        request->type = FULL;
                        endptr = strchr(buff, '/') + 1;
                        if (endptr == NULL) {
                                request->status = 400; // Bad request
                                return -1;
                        }

                        request->http_version = (char *) malloc((strlen(endptr) + 1) * sizeof(char));
                        if (request->http_version == NULL)
                                error("Could not allocate memory for http_version");
                        strncpy(request->http_version, endptr, strlen(endptr));
                } else
                        request->type = SIMPLE;
                is_first_line = 0;
                return 0;
        } else {
                /*We have more than one line thus we need to decipher headers
                   and so on header are of the form NAME.HEADER:value, where
                   NAME.HEADER does not contain any ':'
                   Such that one can split the line with respect */

                endptr = strchr(buff, ':');
                if (endptr == NULL) {
                        request->status = 400;    // Bad request
                        return -1;
                }

                // Comparison to UPPER CASE version of the incoming header is
                // a lot safer !
                temp = (char *) malloc( ((endptr - buff) + 1)* sizeof(char) );
                if (temp == NULL)
                        error("Could not allocate memory for header comparison");
                strncpy(temp, buff, (endptr - buff));
                to_upper(temp);

                /*  Increment buffer so that it now points to the value.
                   If there is no value, just return.                    */

                buff = endptr + 1;
                while ( *buff && isspace(*buff) )
                        ++buff;
                if ( *buff == '\0' )
                        return 0;

                /* now really compare the temp the temp str to the USER-AGENT...*/

                if( !strcmp(temp, "USER-AGENT")) {
                        request->useragent = (char *) malloc( (strlen(buff) + 1) * sizeof(char) );
                        if (request->useragent == NULL)
                                error("Could not allocate space for user-agent value");
                        strcpy(request->useragent, buff);
                } else if ( !strcmp(temp, "REFERER")) {
                        request->referer = (char *) malloc( (strlen(buff) + 1) * sizeof(char) );
                        if (request->referer == NULL)
                                error("Could not allocate space for referer value");
                        strcpy(request->referer, buff);
                } else if ( !strcmp(temp, "EXPECT")) {
                        request->expect = (char *) malloc( (strlen(buff) + 1) * sizeof(char) );
                        if (request->expect == NULL)
                                error("Could not allocate space for expect value");
                        strcpy(request->expect, buff);
                }

                free(temp);
                return 0;
        }
}

int get_request(int c_socket, http_request *request) {
        char buff[BUFF_MAX_LEN] = {0};

        int rval;
        fd_set fds;
        struct timeval tv;

        /*  Set timeout to 5 seconds  */
        tv.tv_sec  = 5;
        tv.tv_usec = 0;


        do {
                /*  Reset file descriptor set  */

                FD_ZERO(&fds);
                FD_SET (c_socket, &fds);


                /*  Wait until the timeout to see if input is ready  */

                rval = select(c_socket+ 1, &fds, NULL, NULL, &tv);
                /*  Take appropriate action based on return from select()  */
                if ( rval < 0 ) {
                        error("Error calling select() in get_request()");
                }
                else if ( rval == 0 ) {
                        /*  input not ready after timeout  */
                        return -1;
                }
                else {
                        read_line(c_socket, buff, BUFF_MAX_LEN-1);
                        trim(buff);
                        if (buff[0] == '\0')
                                break;
                        if (update_http_request(request, buff))
                                break;
                }
        } while(request->type != SIMPLE);

        return 0;
}

http_request *createHttpRequest() {
        http_request * request = (http_request *) malloc(sizeof(http_request));
        if (request == NULL)
                error("Problem while allocating memory in createHttpRequest()");
        request->referer = NULL;
        request->useragent = NULL;
        request->resource_name = NULL;
        request->method = UNSUPPORTED;
        request->status = 200;
        return request;
}

void freeHttpRequest(http_request *request) {
        if (request->referer)
                free(request->referer);
        if (request->useragent)
                free(request->useragent);
        if (request->resource_name)
                free(request->resource_name);
        if (request->http_version)
                free(request->http_version);
        free(request);
}
