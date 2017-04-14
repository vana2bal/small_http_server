#include "mimetypes.h"
#include "hashmap.h"
#include "error.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

map_t mime_types;
char * default_mime = "application/octet-stream";

char * decode_mime_type(char *resource_name) {
        char *retour;
        void *buff;
        char key[KEY_MAX_LENGTH];
        char * dot_ptr;

        retour = (char *) calloc((VALUE_MAX_LENGTH + 1), sizeof(char));
        if (retour == NULL)
                error("Could not allocate memory in decode_mime_type()");

        dot_ptr = strchr(resource_name, '.');
        if (dot_ptr != NULL) {
                strcpy(key, dot_ptr);
                hashmap_get(mime_types, key, &buff);
        }

        if (buff != NULL) {
                strcpy(retour, buff);
        } else {
                strcpy(retour, default_mime);
        }

        return retour;
}


void initialize_mime_type() {
        mime_types = hashmap_new();
        if(mime_types == NULL)
                error("Problem while creating MIME type map");

        hashmap_put(mime_types, ".htm", "text/html");
        hashmap_put(mime_types, ".html", "text/html");
        hashmap_put(mime_types, ".css", "text/css");
        hashmap_put(mime_types, ".txt","text/plain");
        hashmap_put(mime_types, ".xml", "text/xml");

        hashmap_put(mime_types, ".jpeg", "image/jpeg");
        hashmap_put(mime_types, ".jpg", "image/jpg");
        hashmap_put(mime_types, ".png","image/png");
        hashmap_put(mime_types, ".gif","image/gif");

        hashmap_put(mime_types, ".mp3", "audio/mpeg");
        hashmap_put(mime_types, ".avi", "video/x-msvideo");

        hashmap_put(mime_types, ".js", "application/x-javascript");
        hashmap_put(mime_types, ".doc", "application/msword");
        hashmap_put(mime_types, ".pdf", "application/pdf");
        hashmap_put(mime_types, ".ppt", "application/vnd.ms-powerpoint");
        hashmap_put(mime_types, ".zip", "application/zip");

}

void freeMimeTypes() {
        if (mime_types > 0 )
                hashmap_free(mime_types);

}
