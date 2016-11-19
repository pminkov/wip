#include <unistd.h>
#include <stdio.h>

int main() {
  printf("Conf processors: %ld\n", sysconf(_SC_NPROCESSORS_CONF));
  printf("Available processors: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
}
