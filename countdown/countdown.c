#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

//#define LOG_STREAM stdout
#define LOG_STREAM stderr
#include "seethe.h"

#define DEFAULT_SECONDS 60

void catchSignals();

int main(int argc, char *argv[]) {
    const char *tag = NULL;
    int countdown = DEFAULT_SECONDS;
    // process command-line arguments
    if (argc > 1) {
        tag = argv[1];
        if (argc > 2) {
            countdown = atoi(argv[2]);
        }
        else { //if the only argument is a number, don't treat it as a tag
            if (atoi(tag) > 0) {
                countdown = atoi(tag);
                tag = NULL;
            }
        }
    }

    // Set up to log when signals happen
    catchSignals();

    if (tag) info("[%s] countdown started", tag);

    // Do the countdown
    while (countdown > 0)
    {
        printf("%d", countdown);
        if (tag)
            printf(" [%s]\n", tag);
        else
            printf("\n");
        fflush(stdout); //make sure everything is printed immeiately

	countdown--;
	debug("countdown updated to %d", countdown);

	sleep(1);
    }

    if (tag) info("[%s] countdown completed", tag);
    return 0;
}

//Code from https://stackoverflow.com/questions/10114711/log-the-reason-for-process-termination-with-c-on-linux
void signalHandler(int sig)
{
   // Uninstall this handler, to avoid the possibility of an infinite regress
   signal(sig, SIG_DFL);

   //reinstall appropriate stop/continue handler for opposite of current sig
   if (sig == SIGTSTP)
       signal(SIGCONT,  signalHandler);
   if (sig == SIGCONT)
       signal(SIGTSTP,  signalHandler);

   if (sig != SIGTSTP && sig != SIGCONT)
       critical("Program terminated with signal %i", sig);
   else
       notice("Program received signal %i", sig);
   info("Program re-raising signal %i", sig);
   raise(sig);
}

void catchSignals()
{
   signal(SIGSEGV, signalHandler);
   signal(SIGBUS,  signalHandler);
   signal(SIGILL,  signalHandler);
   signal(SIGABRT, signalHandler);
   signal(SIGFPE,  signalHandler);
   signal(SIGINT,  signalHandler);
   signal(SIGTSTP,  signalHandler);
   signal(SIGCONT,  signalHandler);
}

