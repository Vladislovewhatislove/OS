#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	pid_t pid = atoi(argv[1]);

	if (strcmp(argv[2] ,"SIGUSR1") == 0){
		kill(pid, SIGUSR1);
	} else if (strcmp(argv[2], "SIGUSR2") == 0) {
		kill(pid, SIGUSR2);
	}

	return 0;
}
