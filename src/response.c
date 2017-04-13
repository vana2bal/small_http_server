#include "httprequest.h"
#include "response.h"
#include "responseheader.h"
#include "resource.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
/*
   static int respond_message(int socket, char *s) {
        int result = send(socket, s, strlen(s), 0);
        if (result == -1)
                fprintf(stderr, "%s: %s", "Error while replying to client", strerror(errno));
        return result;
   }

   static char* response = "HTTP/1.1 200 OK\r\nDate: Mon, 27 Jul 2009 12:28:53 GMT\r\nServer: My Little Server\r\nLast Modified: Mon, 27 Jul 2009 12:27:00 GMT\r\nContent-Length: 88\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html><body><h1>Bonjour tout le monde</h1></body></html>\r\n";
 */
int respond(int c_socket, http_request *request) {

        int resource = 0;

        if (request->status == 200 ) {
                /* everyting wen't fine while parsing the request
                   , hence one has a functional request let's respond
                   accordingly.
                   100 OK continue is not supported since we only support for now
                   GET and HEAD request METHOD */

                if ( (resource = check_resource(request)) < 0 ) {
                        if ( errno == EACCES )
                                request->status = 401;
                        else
                                request->status = 404;
                }



        }


        /*  Output HTTP response headers if we have a full request  */

        if ( request->type == FULL )
                output_http_headers(c_socket, request);

        if ( request->status == 200 ) {
                if(request->type == SIMPLE || request->method == GET) {
                        if ( return_resource(c_socket, resource, request) )
                                error("Something wrong returning resource.");
                }
        }
        else {
                http_error_msg(c_socket, request);
        }

        if (resource > 0)
                if (close(resource) <0)
                        error("Could not close resource");

        return 0;
}
