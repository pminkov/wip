#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  int page_size = getpagesize();
  printf("Page size: %d\n", page_size);

  // If we're accessing an array of integers and jump from index "i" to index "i+jump", we'll
  // be accessing a different page, since "jump" integers span across a single page.
  int jump = page_size / sizeof(int);
  printf("Jump: %d\n", jump);

  assert(argc == 2);
  // How many pages are we going to access?
  int num_pages = atoi(argv[1]);

  int array_size = sizeof(int) * num_pages * jump;
  printf("Allocating a %dkB array\n", array_size / 1024);
  int *a = malloc(array_size);

  int begin = clock();
  int array_loops = 0;
  int big_loops = 0;

  double time_elapsed;
  while (1) {
    big_loops++;
    for (int tt = 0; tt < 10000; tt++) {
      array_loops += 1;
      // This code will access "num_pages" pages.
      for (int i = 0; i < num_pages * jump; i += jump) {
        a[i] += 1;
      }
    }

    int end = clock();
    time_elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    if (time_elapsed > 1.0) {
      break;
    }
  }

  printf("Time: %.2f\n", time_elapsed);
  printf("Big loops: %d\n", big_loops);
  printf("Array loops: %d\n", array_loops);

  double time_ns = time_elapsed / (array_loops * num_pages) * (1000.0 * 1000.0);

  printf("Array access nanoseconds: %.5f\n", time_ns);
}
