#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "mythreads.h"

const int LIMIT = 1000000;

/* Simple counter 

This counter is slow when it's updated by more than one thread. Why?

There's probably some overhead that comes from calling the lock
and unlock functions.

Also this doesn't scale well. If we jump from 2 to 4 threads, we're doubling
the time taken. That's somewhat expected, since all the threads are
piling on a single lock and thus we can't execute in parallel on different
cores.
*/ 
struct counter_t {
  int value;
  pthread_mutex_t lock;
};

static struct counter_t counter;

#define min(a,b) ((a) < (b) ? (a) : (b))

void init(struct counter_t *c) {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

void increment_by(struct counter_t *c, int by) {
  Pthread_mutex_lock(&c->lock);
  c->value += by;
  Pthread_mutex_unlock(&c->lock);
}

void increment(struct counter_t *c) {
  increment_by(c, 1);
}

int get(struct counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  int rc = c->value;
  Pthread_mutex_unlock(&c->lock);
  return rc;
}

void *incrementer(void *args_ptr) {
  for (int i = 0; i < LIMIT; i++) {
    increment(&counter);
  }
  return NULL;
}


/* Sloppy counter */

const uint64_t SZ = 29;

struct sloppy_counter_t {
  int value;

  struct counter_t gcounter;

  // Instead of sharing a single lock for every thread that increments the
  // counter, the goal here is for each thread to have its own lock.
  // We're using a hash table for that purpose. Why do we even need a lock
  // if each counter is only updated by one thread? Good question. It's safer
  // this way in case there are collisions.
  pthread_mutex_t locks[SZ];
  int lcounters[SZ];
};

static struct sloppy_counter_t sloppy_counter;

void sloppy_init(struct sloppy_counter_t *c) {
  for (int i = 0; i < SZ; i++) {
    pthread_mutex_init(&c->locks[i], NULL);
    c->lcounters[i] = 0;
  }

  init(&c->gcounter);
}

void sloppy_increment(struct sloppy_counter_t *c, pthread_t thread_id) {
  uint64_t ptid = 0;
  memcpy(&ptid, &thread_id, min(sizeof(thread_id), sizeof(ptid)));
  
  int cid = ptid % SZ;

  Pthread_mutex_lock(&c->locks[cid]);

  c->lcounters[cid]++;
  if (c->lcounters[cid] > 2) {
    increment_by(&c->gcounter, c->lcounters[cid]);
    c->lcounters[cid] = 0;
  }

  Pthread_mutex_unlock(&c->locks[ptid % SZ]);
}

void* sloppy_incrementer(void *args_ptr) {
  for (int i = 0; i < LIMIT; i++) {

    sloppy_increment(&sloppy_counter, pthread_self());
  }
  return NULL;
}

int sloppy_get(struct sloppy_counter_t *counter) {
  return get(&counter->gcounter);
}

void regular_benchmark(int N) {
  pthread_t* threads = malloc(N * sizeof(pthread_t));

  init(&counter);

  for (int i = 0; i < N; i++) {
    Pthread_create(&threads[i], NULL, incrementer, NULL);
  }
  
  for (int i = 0; i < N; i++) {
    Pthread_join(threads[i], NULL);
  }

  printf("Done. Value = %d", get(&counter));
}


void sloppy_benchmark(int N) {
  pthread_t* threads = malloc(N * sizeof(pthread_t));

  sloppy_init(&sloppy_counter);

  for (int i = 0; i < N; i++) {
    Pthread_create(&threads[i], NULL, sloppy_incrementer, NULL);
  }
  
  for (int i = 0; i < N; i++) {
    Pthread_join(threads[i], NULL);
  }

  printf("Done. Value = %d", sloppy_get(&sloppy_counter));
}

int main(int argc, char *argv[]) { 
  init(&counter);

  int N = 1;
  if (argc == 2) {
    N = atoi(argv[1]);
  } else {
    printf("counters num-threads");
    exit(0);
  }

  sloppy_benchmark(N);
} 
