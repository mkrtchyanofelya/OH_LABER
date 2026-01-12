#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Ծնող պրոցես
        printf("Parent process PID: %d\n", getpid());
        sleep(120);  // Ծնողը սպասում է, բայց չի կանչում wait()
    } 
    else if (pid == 0) {
        // Երեխա պրոցես
        printf("Child process PID: %d exiting...\n", getpid());
        exit(0);    // Երեխան ավարտվում է՝ դառնալով zombie
    } 
    else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
