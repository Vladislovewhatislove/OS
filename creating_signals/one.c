#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char* lines[] = {
	"Base line",
	"Line after call SIGUSR1",
	"Line after call SIGUSR2"
};

int i = 0;

void handler(int sig)
{
        switch (sig)
        {
                case SIGUSR1: i = 1; break;
		case SIGUSR2: i = 2; break;
                default: i = 0;
        }
}

int main(void)
{
	printf("PID = %d\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);

	while (1){
		char* line = lines[i];
		printf("%s\n", line);
		sleep(4);
	}

	return 0;
}
