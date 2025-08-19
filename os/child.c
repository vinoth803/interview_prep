// child.c
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("Child process (PID: %d) is starting.\n", getpid());
    printf("Child process will now run the 'ls -l' command.\n");

    // Use execlp to run the 'ls' command
    // 'ls' is searched for in the PATH environment variable
    execlp("ls", "ls", "-l", NULL);

    // This code will only be reached if execlp() fails
    perror("execlp failed");
    exit(1);
}