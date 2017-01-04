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


class NoArgs {
public:
  void (*start_routine)();
};


void *wrapper_no_args(void *s) {
  NoArgs *args = (NoArgs *)s;
  args->start_routine();
  delete args;
}


template <class ParamT>
class Args {
public:
  ParamT func_arg;
  void (*start_routine)(ParamT);
};


template <class ParamT, class OutputT>
class ArgsWithOutput {
public:
  ParamT func_arg;
  OutputT *output;
  void (*start_routine)(ParamT, OutputT*);
};


template <class ParamT>
void *wrapper(void *s) {
  Args<ParamT> *args = (Args<ParamT> *)s;
  args->start_routine(args->func_arg);
  delete args;
};


template <class ParamT, class OutputT>
void *wrapper_with_output(void *s) {
  ArgsWithOutput<ParamT, OutputT> *args = (ArgsWithOutput<ParamT, OutputT> *)s;
  args->start_routine(args->func_arg, args->output);
  delete args;
};


class Thread {
  public:
    // One input parameter, one output parameter.
    template <class ParamT, class OutputT>
    Thread(void (*start_routine)(ParamT, OutputT*), ParamT s, OutputT *out) {
      ArgsWithOutput<ParamT, OutputT>* args = new ArgsWithOutput<ParamT, OutputT>;
      args->func_arg = s;
      args->start_routine = start_routine;
      args->output = out;

      void *(*wrapper_routine)(void*) = &wrapper_with_output<ParamT, OutputT>;

      Pthread_create(&thread, NULL, wrapper_routine, (void*)(args));
    }

    // No input, no output.
    Thread(void (*start_routine)()) {
      NoArgs* args = new NoArgs;
      args->start_routine = start_routine;

      void *(*wrapper_routine)(void*) = &wrapper_no_args;

      Pthread_create(&thread, NULL, wrapper_routine, (void*)(args));
    }


    // One input parameter.
    template <class ParamT>
    Thread(void (*start_routine)(ParamT), ParamT s) {
      Args<ParamT>* args = new Args<ParamT>;
      args->func_arg = s;
      args->start_routine = start_routine;

      void *(*wrapper_routine)(void*) = &wrapper<ParamT>;

      Pthread_create(&thread, NULL, wrapper_routine, (void*)(args));
    }

    void join() {
      Pthread_join(thread, NULL);
    }

  private:
    pthread_t thread;
};

