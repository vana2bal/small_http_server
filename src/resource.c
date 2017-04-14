#include "resource.h"
#include "httprequest.h"
#include "mimetypes.h"
#include "error.h"
#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static char server_root[1000] = "/home/florian/work/fun/CBasics/small_http_server/serverroot";
static char * index_html = "index.html";

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

        if( !strcmp(request->resource_name,"/") ) {
                request->resource_name = (char *) realloc(request->resource_name,
                                                          (strlen(index_html) + 1 + 1) * sizeof(char));
                if (request->resource_name == NULL)
                        error("Could not realloc memory for resource_name");

                strcat(request->resource_name, index_html);
        }

        strcat(server_root, request->resource_name);
        return open(server_root, O_RDONLY);
}

int http_error_msg(int socket, http_request * request) {

        char buffer[100];
        char *mime_type;

        mime_type = decode_mime_type(request->resource_name);
        if(mime_type != NULL && strncmp(mime_type, "text/html", strlen("text/html")) == 0) {

                sprintf(buffer, "<HTML>\n<HEAD>\n<TITLE>Server Error %d</TITLE>\n"
                        "</HEAD>\n\n", request->status);
                write_line(socket, buffer, strlen(buffer));

                sprintf(buffer, "<BODY>\n<H1>Server Error %d</H1>\n", request->status);
                write_line(socket, buffer, strlen(buffer));

                sprintf(buffer, "<P>The request could not be completed.</P>\n"
                        "</BODY>\n</HTML>\n");
                write_line(socket, buffer, strlen(buffer));
        }
        free(mime_type);
        return 0;
}
