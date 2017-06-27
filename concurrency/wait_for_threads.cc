#include "pthread_utils.h"
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

const int NUM_THREADS = 10;

pthread_mutex_t output_mutex;
sem_t * semaphore;

void *some_work(void *args) {
  int t = rand() % 5;
  pthread_t thread_id = pthread_self();

  Pthread_mutex_lock(&output_mutex);
  cout << "I'm thread " << thread_id << ". I'll sleep for " << t << " seconds.\n";
  Pthread_mutex_unlock(&output_mutex);

  sleep(t);

  Pthread_mutex_lock(&output_mutex);
  cout << "I'm thread " << thread_id << ". I'm done.\n";
  Pthread_mutex_unlock(&output_mutex);

  sem_post(semaphore);
  return NULL;
}

const char *SEM_NAME="/wait_for_threads";

int main() {
  srand(time(0));
  Pthread_mutex_init(&output_mutex);

  // A named semaphore. Not sure how to create an unnamed one.
  semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 0);

  if (semaphore == SEM_FAILED) {
    if (errno == EEXIST) {
      sem_unlink(SEM_NAME);
    }
    perror("Semaphore");
    return -1;
  }

  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    Pthread_create(&threads[i], NULL, some_work, NULL);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    sem_wait(semaphore);
  }

  sem_unlink(SEM_NAME);
}
