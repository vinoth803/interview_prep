#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    printf("Parent process (PID: %d) is starting.\n", getpid());

    // Create a new child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running.\n", getpid());
        printf("Child process will now exit.\n");
        exit(0); // The child process exits
    } else {
        // Parent process
        printf("Parent process created a child with PID: %d.\n", pid);
        printf("Parent process is waiting for the child to finish.\n");

        // Wait for the child process to terminate
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent process detected that the child has exited with status %d.\n", WEXITSTATUS(status));
        }
    }

    printf("Parent process (PID: %d) is exiting.\n", getpid());

    return 0;
}