#include "resource.h"
#include "httprequest.h"
#include "error.h"
#include "helpers.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static char server_root[1000] = "/home/florian/work/fun/CBasics/small_http_server/serverroot";

int return_resource (int socket, int resource, http_request * request) {
        char c;
        int i;

        while ( (i = read(resource, &c, 1)) ) {
                if (i < 0)
                        error("Error reading from resource");
                if (write( socket, &c, 1) < 1)
                        error("Error sending file");
        }

        return 0;
}
int check_resource  (http_request * request) {
        clean_URL(request->resource_name);
        strcat(server_root, request->resource_name);
        return open(server_root, O_RDONLY);
}

int http_error_msg(int socket, http_request * request) {

        char buffer[100];

        sprintf(buffer, "<HTML>\n<HEAD>\n<TITLE>Server Error %d</TITLE>\n"
                "</HEAD>\n\n", request->status);
        write_line(socket, buffer, strlen(buffer));

        sprintf(buffer, "<BODY>\n<H1>Server Error %d</H1>\n", request->status);
        write_line(socket, buffer, strlen(buffer));

        sprintf(buffer, "<P>The request could not be completed.</P>\n"
                "</BODY>\n</HTML>\n");
        write_line(socket, buffer, strlen(buffer));

        return 0;
}
