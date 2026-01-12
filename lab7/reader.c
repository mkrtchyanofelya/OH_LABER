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

    // Միանում ենք արդեն գոյություն ունեցող shared memory-ին
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    shared_mem = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // Միանում ենք գոյություն ունեցող semaphore-ներին
    sem_write = sem_open(SEM_WRITE, 0);
    sem_read  = sem_open(SEM_READ, 0);

    printf("Reader process started.\n");

    while (1) {
        sem_wait(sem_read);  // սպասում ենք, մինչև writer-ը գրի
        printf("Received: %s", shared_mem);
        sem_post(sem_write); // թույլ ենք տալիս writer-ին նորից գրել
    }

    munmap(shared_mem, SIZE);
    close(shm_fd);
    sem_close(sem_write);
    sem_close(sem_read);

    return 0;
}
