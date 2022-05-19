#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{
        pid_t pid = fork ();

        if (pid == 0) {
                printf ("new parent(ex-child) (pid=%d, parent's pid=%d)\n", getpid(), getppid());
        } else {
                printf ("parent (pid=%d, child's pid=%d)\n", getpid(), pid);
        }

	return 0;
}

