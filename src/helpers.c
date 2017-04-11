#include "helpers.h"
#include "error.h"

#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int read_line(int socket, void *vptr, int len) {
        int n, rc;
        char c, *buffer;

        buffer = vptr;

        for (n = 1; n < len; n++) {
                if ( (rc = read(socket, &c, 1)) == 1) {
                        *buffer++ = c;
                        if(c == '\n')
                                break;
                } else if (rc == 0) {
                        if (n == 1)
                                return 0;
                        else
                                break;
                } else {
                        if (errno == EINTR)
                                continue;
                        error("Error in read_line()");
                }
        }
        *buffer = 0;
        return n;
}

int trim(char *buffer) {
        int n = strlen(buffer) - 1;

        while ( !isalnum(buffer[n]) && n >= 0) {
                buffer[n--] = '\0';
        }

        return 0;
}

int write_line(int socket, void *vptr, int len) {
        int nleft;
        int nwritten;
        const char *buffer;

        buffer = vptr;
        nleft = len;

        while ( nleft > 0) {
                if ( (nwritten = write(socket, buffer, nleft)) <= 0) {
                        if ( errno == EINTR )
                                nwritten = 0;
                        else
                                error("Error in write_line()");
                }
                nleft -= nwritten;
                buffer += nwritten;
        }

        return len;
}
