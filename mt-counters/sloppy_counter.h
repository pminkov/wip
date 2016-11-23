#ifndef SLOPPY_COUNTER_H
#define SLOPPY_COUNTER_H

#include <string.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

const uint64_t SLOTS_COUNT = 101;

struct sloppy_counter_t {
  int value;

  struct counter_t gcounter;

  // A hash table for per-thread counters. Since we're unlikely to run too many threads at the same time,
  // chances for collision are low. If that's not the case, we can always use a per-counter mutex.
  int lcounters[SLOTS_COUNT];
};

static struct sloppy_counter_t sloppy_counter;

void sloppy_init(struct sloppy_counter_t *c) {
  for (int i = 0; i < SLOTS_COUNT; i++) {
    c->lcounters[i] = 0;
  }

  init(&c->gcounter);
}

int slot_id(pthread_t thread_id) {
  uint64_t ptid = 0;
  memcpy(&ptid, &thread_id, min(sizeof(thread_id), sizeof(ptid)));
  
  int sid = ptid % SLOTS_COUNT;
  return sid;
}

void sloppy_increment(struct sloppy_counter_t *c, pthread_t thread_id) {
  int sid = slot_id(thread_id);

  c->lcounters[sid]++;
  if (c->lcounters[sid] > 128) {
    increment_by(&c->gcounter, c->lcounters[sid]);
    c->lcounters[sid] = 0;
  }
}

void sloppy_flush(struct sloppy_counter_t *c, pthread_t thread_id) {
  int sid = slot_id(thread_id);
  if (c->lcounters[sid] > 0) {
    increment_by(&c->gcounter, c->lcounters[sid]);
  }
}


int sloppy_get(struct sloppy_counter_t *counter) {
  return get(&counter->gcounter);
}

#endif
