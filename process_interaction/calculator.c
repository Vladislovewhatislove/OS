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

int main() {
    int fd_fifo;
    int pipe_fd;
    int open_mode = O_RDONLY;
    char buffer[MAX_BUFFER_SIZE - 1];

    memset(buffer, '\0', sizeof(buffer));

    pipe_fd = open(FIFO_NAME, open_mode);

    if (pipe_fd != -1)
    {
        fd_fifo = read(pipe_fd, buffer, MAX_BUFFER_SIZE);
        (void)close(pipe_fd);
    }
    else
    {
        exit(EXIT_FAILURE);
    }

    int a, b;
    char c;
    sscanf(buffer, "%d %c %d", &a, &c, &b);

    switch (c)
    {
    case '+':
        printf("%d %c %d = %d\n", a, c, b, a + b);
        break;
    case '-':
        printf("%d %c %d = %d\n", a, c, b, a - b);
        break;
    case '*':
        printf("%d %c %d = %d\n", a, c, b, a * b);
        break;
    case '/':
        if (b == 0) {
            fprintf(stderr, "Can't divide by zero\n");
            exit(EXIT_FAILURE);
        }
        printf("%d %c %d = %d\n", a, c, b, a / b);
        break;
    default:
        fprintf(stderr, "No such operation exists\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
