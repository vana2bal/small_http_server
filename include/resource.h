/*
 *
 * Interface to functions for returning a resource.
 *
 */
#include "httprequest.h"

#ifndef RESOURCE_H
#define RESOURCE_H

int return_resource (int conn, int resource, http_request * request);
int check_resource  (http_request * request);
int http_error_msg(int conn, http_request * request);

#endif
