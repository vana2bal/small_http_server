#include "responseheader.h"
#include "httprequest.h"
#include "helpers.h"

#include <stdio.h>
#include <string.h>

int output_http_headers(int socket, http_request * request) {
        char buffer[100];

        sprintf(buffer, "HTTP/%s %d OK\r\n",request->http_version,
                request->status);
        write_line(socket, buffer, strlen(buffer));

        write_line(socket, "Server: MYWebServ v0.1\r\n", 24);
        write_line(socket, "Content-Type: text/html\r\n", 25);
        write_line(socket, "\r\n", 2);

        return 0;
}
