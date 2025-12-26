#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd[2];

    fprintf(stderr, "(parent_process>forking…)\n");

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    int pid = fork();

    if (pid == 0) {
        /* child 1 */
        fprintf(stderr, "(child1>redirecting stdout to the write end of the pipe…)\n");

        close(STDOUT_FILENO);
        dup(fd[1]);
        close(fd[1]);

        fprintf(stderr, "(child1>going to execute cmd: ls -lsa)\n");

        char *cmd[] = {"ls", "-lsa", NULL};
        execvp(cmd[0], cmd);
        perror("execvp ls");
        exit(1);
    }

    fprintf(stderr, "(parent_process>created process with id: %d)\n", pid);
    fprintf(stderr, "(parent_process>closing the write end of the pipe…)\n");
    close(fd[1]);

    fprintf(stderr, "(parent_process>forking…)\n");
    int pid2 = fork();

    if (pid2 == 0) {
        /* child 2 */
        fprintf(stderr, "(child2>redirecting stdin to the read end of the pipe…)\n");

        close(STDIN_FILENO);
        dup(fd[0]);
        close(fd[0]);

        fprintf(stderr, "(child2>going to execute cmd: tail -n 3)\n");

        char *cmd2[] = {"tail", "-n", "3", NULL};
        execvp(cmd2[0], cmd2);
        perror("execvp tail");
        exit(1);
    }

    fprintf(stderr, "(parent_process>created process with id: %d)\n", pid2);
    fprintf(stderr, "(parent_process>closing the read end of the pipe…)\n");
    close(fd[0]);

    fprintf(stderr, "(parent_process>waiting for child processes to terminate…)\n");
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);

    fprintf(stderr, "(parent_process>exiting…)\n");
    return 0;
}