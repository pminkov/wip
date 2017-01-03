#include "pthread_utils.h"
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

template <class T>
class Args {
public:
  T *func_arg;
  void *(*start_routine)(T *);
};

template <class T>
void *wrapper(void *s) {
  Args<T> *args = (Args<T> *)s;
  assert(args->start_routine);
  assert(args->func_arg);
  printf("Starting\n");
  args->start_routine(args->func_arg);
  return NULL;
};

class Thread {
  public:
    void start(void *(*start_routine)(string *), string &s) {
      Args<string>* args = new Args<string>;
      args->func_arg = &s;
      args->start_routine = start_routine;
      void *(*wrapper_routine)(void*) = &wrapper<string>;
      Pthread_create(&thread, NULL, wrapper_routine, (void*)(&args));
    }
    void start(void *(*start_routine)(void *), void *arg) {
      Pthread_create(&thread, NULL, start_routine, arg);
    }

  private:
    pthread_t thread;
};


