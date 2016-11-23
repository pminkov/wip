#include <stdio.h>
#include <assert.h>
#include "mythreads.h"
#include "regular_counter.h"
#include "sloppy_counter.h"

const int LIMIT = 1 * 1000 * 1000;

void *incrementer(void *args_ptr) {
  for (int i = 0; i < LIMIT; i++) {
    increment(&counter);
  }
  return NULL;
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

  int j = 3;
  for (int i = 0; i < 10000000; i++) {
    j -= i;
    
  }

  printf("Done. Value = %d", get(&counter));
}

void* sloppy_incrementer(void *args_ptr) {
  for (int i = 0; i < LIMIT; i++) {
    sloppy_increment(&sloppy_counter, pthread_self());
  }
  sloppy_flush(&sloppy_counter, pthread_self());
  return NULL;
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

  char type;
  int N = 1;
  if (argc == 3) {
    type = argv[1][0];
    assert(type == 'r' || type == 's');
    N = atoi(argv[2]);
  } else {
    printf("counters [r|s] num-threads");
    exit(0);
  }

  if (type == 'r') {
    regular_benchmark(N);
  } else {
    sloppy_benchmark(N);
  }
} 
