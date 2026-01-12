#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shared_memory"
#define SEM_WRITE "/sem_write"
#define SEM_READ "/sem_read"
#define SIZE 256

int main() {
    int shm_fd;
    char *shared_mem;
    sem_t *sem_write, *sem_read;

    // Ստեղծում ենք shared memory
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    shared_mem = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Ստեղծում ենք semaphore-ներ
    sem_write = sem_open(SEM_WRITE, O_CREAT, 0666, 1);
    sem_read  = sem_open(SEM_READ,  O_CREAT, 0666, 0);

    printf("Writer process started.\n");

    while (1) {
        char input[SIZE];
        printf("Enter message (or 'exit'): ");
        fgets(input, SIZE, stdin);

        if (strncmp(input, "exit", 4) == 0)
            break;

        sem_wait(sem_write); // սպասում ենք գրելու թույլտվությանը
        strcpy(shared_mem, input);
        sem_post(sem_read);  // թույլ ենք տալիս reader-ին կարդալ
    }

    // Մաքրել ռեսուրսները
    munmap(shared_mem, SIZE);
    close(shm_fd);
    sem_close(sem_write);
    sem_close(sem_read);

    printf("Writer exiting...\n");
    return 0;
}
