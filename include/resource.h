/*
 *
 * Interface to functions for returning a resource.
 *
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include "httprequest.h"

int return_resource (int conn, int resource, http_request * request);
int check_resource  (http_request * request);
int http_error_msg(int conn, http_request * request);

#endif
