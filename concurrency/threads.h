#include "pthread_utils.h"
#include <iostream>
#include <string>
using namespace std;

class Mutex {
public:
  Mutex() {
    Pthread_mutex_init(&mutex);
  }
  void lock() {
    Pthread_mutex_lock(&mutex);
  }
  void unlock() {
    Pthread_mutex_unlock(&mutex);
  }
  ~Mutex() {
    Pthread_mutex_destroy(&mutex);
  }
private:
  friend class CondVar;
  pthread_mutex_t mutex;
};

class CondVar {
public:
  CondVar() {
    Pthread_cond_init(&condvar);
  }

  void wait(Mutex *m) {
    Pthread_cond_wait(&condvar, &m->mutex);
  }

  void signal() {
    Pthread_cond_signal(&condvar);
  }

private:
  pthread_cond_t condvar;
};

