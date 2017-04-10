#include "error.h"

#include <stdio.h>    /* for fprintf */
#include <stdlib.h>   /* for exit and EXIT_FAILURE */
#include <errno.h>    /* for errno */
#include <string.h>   /* for strerror */

void error(char *msg) {
        fprintf(stderr, "%s: %s\n", msg, strerror(errno));
        exit(EXIT_FAILURE);
}
