#include "signalhandler.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

extern int listener_d;
extern int connect_d;

static void handle_shutdown(int sig)
{
	if (listener_d)
		close(listener_d);
  if (connect_d)
    close(connect_d);
	fprintf(stdout, "Bye thanks for the ride!\n");
	exit(0);
}


static int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction (sig, &action, NULL);
}

int setup_signal_handlers()
{
  puts("Setting up signal handlers");

  int r_sig_int, r_sig_chld;
  if ((r_sig_int = catch_signal(SIGINT, handle_shutdown)) == -1)
    error("Error while setting the interrupt handler");
  if ((r_sig_chld = catch_signal(SIGCHLD, SIG_IGN)) == -1)
    error("Error while setting up child signal ignore");

  return 1;
}
