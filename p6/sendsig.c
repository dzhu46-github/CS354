#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// send signals to other running processes
int main(int argc, char *argv[]) {

	if(argc != 3) {
		printf("usage: <signal type> <pid>");
	}
	// extract the command line args
	char *sigtype = argv[1];
	int pid = atoi(argv[2]);

	// send signal to other programs
	if(strcmp(sigtype, "-i") == 0) {
		if(kill(pid, SIGINT) == -1) {
			printf("kill() ERROR\n");
			exit(1);
		}
		kill(pid, SIGINT);
	}
	else if(strcmp(sigtype, "-u") == 0) {
		if(kill(pid,SIGINT) == -1) {
			printf("kill() ERROR\n");
			exit(1);
		}
		kill(pid, SIGUSR1);
	}
	else {
		printf("ERROR: INVALID ARGUMENT");
		exit(1);
	}
	exit(0);
}
