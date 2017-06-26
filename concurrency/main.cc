#include "stdlib.h"
#include "threads.h"
#include "unistd.h"
#include <iostream>
#include <string>
using namespace std;

void square(int a) {
  int res = a * a;
  printf("Square of %d = %d\n", a, res);
}

void a_number() {
  int r = rand() % 100;
  printf("A random number is: %d\n", r);
}

void square2(int a, int *out) {
  *out = a * a;
}

void get_six(int *a) {
  *a = 6;
}

int main() {
  srand(time(NULL));
}
