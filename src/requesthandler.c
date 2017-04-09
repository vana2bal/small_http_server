#include "requesthandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>

static int respond(int socket, char *s) {
	int result = send(socket, s, strlen(s), 0);
	if (result == -1)
		fprintf(stderr, "%s: %s", "Error while replying to client", strerror(errno));
	return result;
}

static int read_in(int socket, char *buff, int len) {
  char *s = buff;
  int slen = len;
  int c = recv(socket, s, slen, 0);
  while ( (c>0) && (s[c-1] != '\n') ) { //
    s += c ;
    slen = slen - c;
    c = recv(socket, s, slen, 0);
  }

  if( c < 0) {
    return c;
  } else if (c == 0) {
    buff[0] = '\0';
  } else {
    s[c-1] = '\0';
  }

  return len - slen;
}

static char* response = "HTTP/1.1 200 OK\r\nDate: Mon, 27 Jul 2009 12:28:53 GMT\r\nServer: My Little Server\r\nLast Modified: Mon, 27 Jul 2009 12:27:00 GMT\r\nContent-Length: 88\r\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html><body><h1>Bonjour tout le monde</h1></body></html>\r\n";

int handle_request(int c_socket) {
  int buff_len = 4096;
  char buff[buff_len];

  if (read_in(c_socket, buff, buff_len) != -1)
    fprintf(stdout, "Received: %s\n", buff);
  if(respond(c_socket, response) != -1)
    fprintf(stdout, "Responded:\n\n %s\n", response);

  return 1;
}
