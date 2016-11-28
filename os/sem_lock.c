#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t* lock_sem;

int count = 0;

void *worker(void *arg) {
  while (1) { // w0
    sem_wait(lock_sem);  // w1
    count++; // w2
    printf("work(%s): %5d\n", (char*)arg, count); // w3
    sem_post(lock_sem); // w4
  }
}

int main() {
  lock_sem = sem_open("main semaphore", 777, 1);

  pthread_t p0;
  pthread_create(&p0, NULL, worker, "p0");

  pthread_t p1;
  pthread_create(&p1, NULL, worker, "p1");

  sleep(2);
}
