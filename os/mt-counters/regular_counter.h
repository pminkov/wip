#ifndef REGULAR_COUNTER_H
#define REGULAR_COUNTER_H

#include "mythreads.h"

struct counter_t {
  int value;
  pthread_mutex_t lock;
};

static struct counter_t counter;

void init(struct counter_t *c) {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

void increment_by(struct counter_t *c, int by) {
  Pthread_mutex_lock(&c->lock);
  c->value += by;
  Pthread_mutex_unlock(&c->lock);
}

void increment(struct counter_t *c) {
  increment_by(c, 1);
}

int get(struct counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  int rc = c->value;
  Pthread_mutex_unlock(&c->lock);
  return rc;
}


#endif
