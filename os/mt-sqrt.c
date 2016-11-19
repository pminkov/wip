/*
An exercise in multithreading:

Computes SUM(1 to N, sqrt(i)) % 100.

Takes one argument: number of threads.


$ time ./mt-sqrt 1
sum = 15

real    0m1.527s
user    0m1.520s
sys     0m0.004s

$ time ./mt-sqrt 8
sum = 15

real    0m0.407s
user    0m2.780s
sys     0m0.006s

*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const int LIMIT = 1 << 27;

struct sqrt_args {
  int start;
  int step;
};


void *calculator(void *args_ptr) {
  struct sqrt_args* args = (struct sqrt_args*) args_ptr;
  int start = args->start;
  int step = args->step;

  int* sum = malloc(sizeof(int));

  for (int i = start; i < LIMIT; i += step) {
    *sum += ((int)sqrt((double)i)) % 100;
    *sum = *sum % 100;
  }

  return sum;
}


int main(int argc, char *argv[]) { 
  int N = 1;
  if (argc == 2) {
    N = atoi(argv[1]);
  } else {
    printf("mt-sqrt num-threads");
    exit(0);
  }
  
  pthread_t* threads = malloc(N * sizeof(pthread_t));
  struct sqrt_args* args = malloc(N * sizeof(struct sqrt_args));
  
  for (int i = 0; i < N; i++) {
    args[i].start = i;
    args[i].step = N;
    
    struct sqrt_args * args1 = &args[i];
    void *args = (void*) args1;
    
    pthread_create(&threads[i], NULL, calculator, args);
  }
  
  int sum = 0; 
  for (int i = 0; i < N; i++) {
    int* partial_sum;
    pthread_join(threads[i], (void**) &partial_sum);
    sum += *partial_sum;
    sum = sum % 20;
  }
  
  printf("sum = %d\n", sum);
} 
