/*
 * Interface to Http Request Headers
 *
 */

 #ifndef HTTP_REQUEST_HEADER_H
 #define HTTP_REQUEST_HEADER_H

/*  Type Definitions */
typedef enum Http_Request_Method {
        GET,
        HEAD,
        UNSUPPORTED
} http_request_method;

typedef enum Http_Request_Type {
        FULL,
        SIMPLE
} http_request_type;

typedef struct Http_Request {
        http_request_method method;
        http_request_type type;
        char *referer;
        char *useragent;
        char *resource_name;
        char * http_version;
        int status;
} http_request;

/* Function prototypes */
/* read from the socket and fill the content of the request*/
int get_request(int c_socket, http_request *request);
/* allocate memory on the stack for the request and returns it initalized*/
http_request *createHttpRequest();
/*free allocated memory for the request*/
void freeHttpRequest(http_request *request);

#endif
