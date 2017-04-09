#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "error.h"
#include "requesthandler.h"
#include "signalhandler.h"

static int open_listener_socket() {
	int s = socket(PF_INET, SOCK_STREAM, 0);

  if (s == -1)
		error("Can't open socket");

	return s;
}

static void bind_to_port(int socket, int port) {
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	int reuse = 1;
	if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
		error("Can't set the reuse option on the socket");
	int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
	if (c == -1)
		error("Can't bind to socket");
}

int listener_d, connect_d;

static char* pid_storage_file_path = "/run/smallhttpserver/smallhttpserver.pid";

int main(int argc, char *argv[]) {
  struct sockaddr_storage client_addr;
  unsigned int addr_size = sizeof(client_addr);
  pid_t deamon_pid;
  FILE * fd_pid;

  setup_signal_handlers();

  puts("Opening listening socket");
	listener_d = open_listener_socket();

  puts("Binding socket to port 8080");
	bind_to_port(listener_d, 8080); //binding to port 8080;

	if (listen(listener_d, 10) == -1)
		error("Can't listen on port: 8080");

  //Demonizing the server
  if (!(deamon_pid =fork())) {
	   puts("Waiting for connections ...");

     while(1) {
       connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &addr_size);

       if (connect_d == -1)
			    error("Can't open secondary socket");

       if (!fork()) {

			      if(close(listener_d) < 0)
              error("Error closing listening socket in child process.");

            if(handle_request(connect_d) <0)
              fprintf(stderr, "Request could'nt be handled\n");

            if(close(connect_d) < 0)
              error("Error closing connection socket in child process.");

            exit(EXIT_SUCCESS);
        } else {

          if(close(connect_d) < 0)
             error("Error closing connection socket in parent process.");

       }

	   }
     //No one should ever be here
     exit(EXIT_FAILURE);
  } else {

    if(close(listener_d) == -1)
      fprintf(stderr, "%s: %s", "Could not close main listening socket", strerror(errno));


    fd_pid = fopen(pid_storage_file_path, "wb+");
    if (fd_pid == NULL)
      fprintf(stderr, "%s: %s\n", "Could not open deamon pid storage file", strerror(errno));
    else {
      fprintf(fd_pid, "%d",deamon_pid );
      fclose(fd_pid);
    }

    puts("Service is up an running");
    exit(EXIT_SUCCESS);
  }
}
