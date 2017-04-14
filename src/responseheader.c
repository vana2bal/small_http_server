#include "responseheader.h"
#include "httprequest.h"
#include "mimetypes.h"
#include "error.h"
#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int output_http_headers(int socket, http_request * request) {
        char buffer[100];
        char *mime_type;

        sprintf(buffer, "HTTP/%s %d OK\r\n",request->http_version,
                request->status);
        write_line(socket, buffer, strlen(buffer));

        write_line(socket, "Server: MYWebServ v0.1\r\n", 24);

        mime_type = decode_mime_type(request->resource_name);
        fprintf(stdout, "mime type  in out_http_headers %s\n", mime_type);
        sprintf(buffer,"Content-Type: %s\r\n", mime_type );
        write_line(socket, buffer, strlen(buffer));
        free(mime_type);

        write_line(socket, "\r\n", 2);

        return 0;
}
