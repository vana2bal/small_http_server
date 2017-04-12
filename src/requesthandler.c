#include "requesthandler.h"
#include "httprequest.h"
#include "response.h"

#include <stdio.h>

int handle_request(int c_socket) {
        int resp;
        http_request *request;

        request = createHttpRequest();
        get_request(c_socket, request);

        fprintf(stdout, "USER-AGENT %s\n", request->useragent);
        fprintf(stdout, "REFERER %s\n", request->referer );
        resp = respond(c_socket, request);

        freeHttpRequest(request);
        return resp;
}
