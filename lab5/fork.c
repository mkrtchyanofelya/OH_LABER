#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void rect_area() {
    int a = 5, b = 3;
    printf("RECT: pid=%d ppid=%d area=%d\n", getpid(), getppid(), a * b);
}

void tri_area() {
    int a = 4, h = 6;
    double s = 0.5 * a * h;
    printf("TRI: pid=%d ppid=%d area=%.2f\n", getpid(), getppid(), s);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        printf("Child before exec-like: pid=%d ppid=%d\n", getpid(), getppid());
        tri_area();
        exit(0);
    } else {
        printf("Parent before waiting: pid=%d ppid=%d child=%d\n", getpid(), getppid(), pid);
        wait(NULL);
        rect_area();
    }

    return 0;
}
