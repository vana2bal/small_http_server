#include "httprequest.h"
#include "helpers.h"
#include "error.h"

#include <stdlib.h>
#include <stdio.h>

int get_request(int c_socket, http_request *request) {
        int buff_len = 4096;
        char buff[buff_len];

        do {
                read_line(c_socket, buff, buff_len-1);
                trim(buff);
                fprintf(stdout, "%s\n",buff);
        } while(buff[0] != '\0');

        return 1;
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
        free(request);
}
