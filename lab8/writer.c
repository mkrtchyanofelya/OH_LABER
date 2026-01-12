#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 0x1234

struct shmseg {
  int written;
  int read;
  char message[256];
};

int main() {
  int shmid;
  struct shmseg *shm;

  shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | 0666);
  if (shmid == -1) {
    perror("shmget failed");
    exit(1);
  }

  shm = (struct shmseg*) shmat(shmid, NULL, 0);
  if (shm == (void*) -1) {
    perror("shmat failed");
    exit(1);
  }

  shm->written = 0;
  shm->read = 0;

  printf("Enter message to send: ");
  fgets(shm->message, sizeof(shm->message), stdin);
  shm->written = 1;
  shm->read = 0;

  printf("[Writer] Message written. Waiting for reader to read it...\n");

  while (shm->read == 0) {
    usleep(100000);
  }

  printf("[Writer] Reader has read the message. \n");

  shmdt((void*) shm);
  shmctl(shmid, IPC_RMID, NULL);
  printf("[Writer] Shared memory removed.\n");

  return 0;
}
