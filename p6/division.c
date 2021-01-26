#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int successes = 0;

void handler_SIGFPE(int sig) {
	printf("ERROR\n");
	printf("Total number of operations completed successfully: %d\n", successes);
	printf("The program will be terminated.\n");
	exit(0);
}

void handler_SIGINT(int sig) {
	printf("Total number of operations completed successfully: %d\n", successes);
	printf("The program will be terminated.\n");
	exit(0);
}

int main(int argc, char *argv[]) {
	int first = 0;
	int second = 0;
	int quotient = 0;
	int remainder = 0;

	struct sigaction sfpe;
	memset(&sfpe, 0, sizeof(sfpe));
	sfpe.sa_handler = handler_SIGFPE;
	sfpe.sa_flags = 0;

	struct sigaction sint;
	memset(&sint, 0, sizeof(sint));
	sint.sa_handler = handler_SIGINT;
	sint.sa_flags = 0;

	if(sigaction(SIGFPE, &sfpe, NULL) != 0) {
		printf("ERROR\n");
		exit(1);
	}
	if(sigaction(SIGINT, &sint, NULL) != 0) {
		printf("ERROR\n");
		exit(1);
	}

	while(1) {
		printf("Enter first integer: ");
		char buf[100];
		fgets(buf, 100, stdin);
		if (buf == NULL) {
			printf("ERROR\n");
			exit(1);
		}
		first = atoi(buf);

		printf("Enter second integer: ");
		fgets(buf, 100, stdin);
		if (buf == NULL) {
			printf("ERROR\n");
			exit(1);
		}

		second = atoi(buf);

		quotient = first / second;
		remainder = first % second;

		printf("%d / %d is %d with a remainder of %d\n", first, second, quotient, remainder);
		successes = successes + 1;
	}
	return 0;
}
