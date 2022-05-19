#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	printf("be in progress \"three\"\n");
	printf("PID from \"three\": %d\n", getpid());

	execvp("./processes/exe/process1", NULL);

	return 0;
}
