/*
 * mime type definition
 */

#ifndef MIME_TYPE_H
#define MIME_TYPE_H
#include "hashmap.h"

#define KEY_MAX_LENGTH (256)
#define VALUE_MAX_LENGTH (256)
extern map_t mime_types;
extern char * default_mime;

void initialize_mime_type();
void freeMimeTypes();

char * decode_mime_type(char *resource_name);

#endif
