#include "mythreads.h"
#include "iterative_sleep.h"
#include <pthread.h>
#include <unistd.h>

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;


void *signaler(void *arg) {
  Pthread_mutex_lock(&m);
  Pthread_cond_signal(&c);
  Pthread_mutex_unlock(&m);
  return NULL;
}

void *waiter(void *arg) {
  Pthread_mutex_lock(&m);
  Pthread_cond_wait(&c, &m);
  printf("Back from wait\n");
  Pthread_mutex_unlock(&m);
  return NULL;
}

int main() {
  pthread_t signaler0, waiter0, waiter1;
  
  printf("Starting two threads, both of which wait on a conditional variable...\n");
  Pthread_create(&waiter0, NULL, waiter, NULL);
  Pthread_create(&waiter1, NULL, waiter, NULL);

  printf("Sleeping, both threads are waiting...\n");
  iterative_sleep(5);

  printf("Sending a signal and sleeping for a bit to see who receives it...\n");
  Pthread_create(&signaler0, NULL, signaler, NULL);
  iterative_sleep(5);

  return 0;
}
