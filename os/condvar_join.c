#include "mythreads.h"
#include <pthread.h>
#include <unistd.h>
#include "iterative_sleep.h"

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
  Pthread_mutex_lock(&m);
  done = 1;

  // This won't release "m" immediately. When "m" is released at the end of this function,
  // that's when the wait() in thr_join() returns.
  Pthread_cond_signal(&c);

  printf("Child thread signaled that it's done. Now waiting for a bit...\n");
  iterative_sleep(5);
  printf("Calling unlock from child thread.\n");
  Pthread_mutex_unlock(&m);
}

void *child(void *arg) {
  printf("Hello from child thread. That's it, I'm done.\n");
  thr_exit();
  return NULL;
}

void thr_join() {
  // If we put a sleep here, we will force the child to finish way
  // before the join and we won't even make a wait() call below.

  Pthread_mutex_lock(&m);
  while (done == 0) {
    // Unlocks "m". Upon return, locks "m".
    printf("Calling wait() and waiting for child to finish.\n");
    Pthread_cond_wait(&c, &m);
    printf("Back from waiting in parent thread.\n");
  }

  Pthread_mutex_unlock(&m);
}

int main() {
  pthread_t p;
  Pthread_create(&p, NULL, child, NULL);
  thr_join();
  printf("Process quits.");
  return 0;
}
