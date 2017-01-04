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

  // No arguments.
  Thread anum(a_number);
  anum.join();

  // One argument.
  Thread sq(square, 5);
  sq.join();

  // One argument, one return value.
  int ret;
  Thread sq2(square2, 5, &ret);
  sq2.join();
  cout << ret << endl;
}
