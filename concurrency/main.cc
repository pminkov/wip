#include "threads.h"
#include "unistd.h"
#include <iostream>
#include <string>
using namespace std;

void *hello(string *arg) {
  printf("hi\n");
  printf("hello: %s\n", arg->c_str());
  
  return NULL;
}

int main() {
  Mutex mutex;

  Thread t;

  string s = "petko";

  t.start(hello, s);

  sleep(1);
}
