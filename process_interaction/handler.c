#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define MAX_BUFFER_SIZE 128

int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Not enough items\n");
        exit(EXIT_FAILURE);
    } else if (argc > 4) {
        fprintf(stderr, "Excess elements\n");
        exit(EXIT_FAILURE);
    }

    int buffer_size = strlen(argv[1]) + strlen(argv[2]) + strlen(argv[3]);
    if (buffer_size > MAX_BUFFER_SIZE) {
        fprintf(stderr, "Allowed number of characters 128\n");
        exit(EXIT_FAILURE);
    }
    char *buffer = malloc(buffer_size + 1);
    strcpy(buffer, argv[1]);
    strcat(buffer, argv[2]);
    strcat(buffer, argv[3]);

    int pipe_fd;
    int fd_fifo;
    int open_mode = O_WRONLY;

    if (access(FIFO_NAME, F_OK) == -1)
    {
        fd_fifo = mkfifo(FIFO_NAME, 0777);

        if (fd_fifo != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }

    pipe_fd = open(FIFO_NAME, open_mode);

    if (pipe_fd != -1) {
        fd_fifo = write(pipe_fd, buffer, strlen(buffer));
        if (fd_fifo == -1) {
            fprintf(stderr, "Write error on pipe\n");
            exit(EXIT_FAILURE);
        }
        (void)close(pipe_fd);
    }
    else
    {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
