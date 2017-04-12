/*
 * Public interface to the response module.
 *
 */
#include "httprequest.h"

#ifndef RESPONSE_H
#define RESPONSE_H

int respond(int c_socket, http_request *request);

#endif
