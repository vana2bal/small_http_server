#include "requesthandler.h"
#include "httprequest.h"
#include "helpers.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>


static int respond(int socket, char *s) {
        int result = send(socket, s, strlen(s), 0);
        if (result == -1)
                fprintf(stderr, "%s: %s", "Error while replying to client", strerror(errno));
        return result;
}


static char* response = "HTTP/1.1 200 OK\r\nDate: Mon, 27 Jul 2009 12:28:53 GMT\r\nServer: My Little Server\r\nLast Modified: Mon, 27 Jul 2009 12:27:00 GMT\r\nContent-Length: 88\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html><body><h1>Bonjour tout le monde</h1></body></html>\r\n";

int handle_request(int c_socket) {
        http_request *request;

        request = createHttpRequest();
        get_request(c_socket, request);

        fprintf(stdout, "%s, %s\n", request->resource_name, request->http_version);
        freeHttpRequest(request);

        int resp;
        if((resp=respond(c_socket, response)) != -1)
                fprintf(stdout, "Responded:\n\n %s\n", response);


        return resp;
}
