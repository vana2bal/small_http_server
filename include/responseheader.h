/*
 * Interface functions to output headers.
 *
 *
 */
#include "httprequest.h"

#ifndef RESPONSE_HEADER_H
#define RESPONSE_HEADER_H

int output_http_headers(int socket, http_request * request);

#endif
