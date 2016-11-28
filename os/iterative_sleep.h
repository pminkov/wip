#include <unistd.h>

void iterative_sleep(int n) {
  for (int i = 0; i < n; i++) {
    printf("sleep %d\n", i);
    sleep(1);
  }
}
