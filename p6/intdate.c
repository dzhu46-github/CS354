#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

/* global variable in seconds */
int t = 3;

void handler_SIGALRM(int sig) {
	
	time_t curr_time;
	if ((time(&curr_time) == (time_t)- 1) || (time(&curr_time) == 0)) {
		printf("time() ERROR\n");
		exit(1);
	}

	time(&curr_time);

	pid_t pid;
	pid = getpid();

	if (ctime(&curr_time) == NULL) {
		printf("ctime ERROR\n");
		exit(1);
	}

	printf("PID: %d | Current Time: %s", pid, ctime(&curr_time) );
	alarm(t);
}


int count = 0;
void handler_SIGUSR1(int sig) {
	count++;
	printf("SIGUSR1 caught!\n");
}

void handler_SIGINT(int sig) {
	printf("SIGUSR1 was received %d times. Exiting now.\n", count);
	exit(0);
}


int main (int argc, char *argv[]) {
	
	// initialize SIGALRM
	struct sigaction alrm;
	memset(&alrm, 0, sizeof(alrm));
	alrm.sa_handler = handler_SIGALRM;
	alrm.sa_flags = 0;

	// initalize SIGUSR1
	struct sigaction usr1;
	memset(&usr1, 0, sizeof(usr1));
	usr1.sa_handler = handler_SIGUSR1;
	usr1.sa_flags = 0;

	// initialize SIGINT
	struct sigaction sint;
	memset(&sint, 0, sizeof(sint));
	sint.sa_handler = handler_SIGINT;
	sint.sa_flags = 0;	
	

	printf("Pid and time will be printed every 3 seconds.\n");
	printf("Enter ^C to end the program.\n");
	
	
	if (sigaction(SIGALRM, &alrm, NULL) != 0) {
		printf("ERROR: BINDING SIGALRM HANDLER.\n");
		exit(1);
	}

	if (sigaction(SIGUSR1, &usr1, NULL) != 0) {
		printf("ERROR: BINDING SIGUSR1 HANDLER.\n");
		exit(1);
	}

	if (sigaction(SIGINT, &sint, NULL) != 0) {
		printf("ERROR: BINDING SIGINT HANDLER.\n");
		exit(1);
	}


	/* set alarm to go off 3 seconds later */
	alarm(t);

	while(1){

	}

	return 0;
}

