#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_KEY 0x1234

struct shmseg {
  int written;
  int read;
  char message[256];
};

int main() {
  int shmid;
  struct shmseg* shm;

  shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0666);

  if (shmid == -1) {
    perror("shmget failed");
    exit(1);
  }

  shm = (struct shmseg *) shmat(shmid, NULL, 0);
  if (shm == (void*) -1) {
    perror("shmat failed");
    exit(1);
  }

  printf("[Reader] Waiting for message...\n");

  while (shm->written == 0) {
    usleep(100000);
  }

  printf("[Reader] Message received: %s", shm->message);

  shm->read = 1;

  printf("[Reader] Acknowledged reading to writer.\n");

  shmdt((void*) shm);
  return 0;
}
