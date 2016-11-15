#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

struct Stats {
  double std;
  double mean;
  double min;
  double max;
};

struct Stats standard_deviation(int n, double *timings) {
  double max = timings[0];
  double min = timings[0];
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += timings[i];
    if (timings[i] > max) max = timings[i];
    if (timings[i] < min) min = timings[i];
  }
  double mean = sum / n;

  double ss = 0;
  for (int i = 0; i < n; i++) {
    ss += (timings[i] - mean) * (timings[i] - mean);
  }
  ss /= n;

  double std = sqrt(ss);

  struct Stats s;
  s.std = std;
  s.mean = mean;
  s.min = min;
  s.max = max;

  return s;
}

int main(int argc, char *argv[]) {
  int N = 100; 

  double *timings = malloc(sizeof(double) * N);
  
  for (int t = 0; t < N; t++) {
    int begin = clock();
    int result = 0;
    for (int i = 0; i < 1000000; i++)
      result += sqrt(i);
    int end = clock();
    double time_elapsed = (double)(end - begin) / CLOCKS_PER_SEC * 1000.0 * 1000.0;
    timings[t] = time_elapsed;
    printf("%f ns\n", time_elapsed);
  }

  struct Stats stats = standard_deviation(N, timings);

  int one_std = 0;
  int two_std = 0;
  for (int i = 0; i < N; i++) {
    if (stats.mean - stats.std < timings[i] && timings[i] < stats.mean + stats.std) {
      one_std++;
    }
    if (stats.mean - 2.0 * stats.std < timings[i] && timings[i] < stats.mean + 2.0 * stats.std) {
      two_std++;
    }
  }

  double one = (double)one_std / N * 100.0;
  double two = (double)two_std / N * 100.0;

  printf(
    "\n\nMax:%.2f\n"
    "Min:%.2f\n"
    "Mean:%.2f\n"
    "Standard deviation:%.2f\n"
    "Within one std:%.2f%%\n"
    "Within two std:%.2f%%\n", 
    stats.max, stats.min,
    stats.mean, stats.std, 
    one, two);
}

