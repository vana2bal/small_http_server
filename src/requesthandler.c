#include "requesthandler.h"
#include "httprequest.h"
#include "response.h"

#include <stdio.h>

int handle_request(int c_socket) {
        http_request *request;

        request = createHttpRequest();

        if (get_request(c_socket, request) < 0) {
                freeHttpRequest(request);
                return -1;
        }

        if (respond(c_socket, request) < 0) {
                freeHttpRequest(request);
                return -1;
        }

        freeHttpRequest(request);
        return 0;
}
