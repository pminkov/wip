#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const int N = 100;
struct graph {
  int g[N][N];
};


struct queue_node {
  int value;
  struct queue_node *next;
};

struct queue_node* new_node(int value) {
  struct queue_node *ret = malloc(sizeof(struct queue_node));
  ret->value = value;
  ret->next = NULL;
  return ret;
}

struct queue {
  struct queue_node *head, *tail;
};

void init_queue(struct queue *q) {
  q->head = q->tail = NULL;
}


void enqueue(struct queue *q, int value) {
  if (q->tail == NULL) {
    q->head = q->tail = new_node(value);
  } else {
    struct queue_node *new_tail = new_node(value);
    q->tail->next = new_tail;
    q->tail = new_tail;
  }
}

void print_queue(struct queue *q) {
  if (q->head == NULL) {
    printf("Empty queue\n");
  } else {
    struct queue_node *cur = q->head;

    printf("Q: ");
    while (cur != NULL) {
      printf("%d ", cur->value);
      cur = cur->next;
    }
    printf("\n");
  }
}

int dequeue(struct queue *q) {
  assert(q->head != NULL);
  return 5;
}

int is_queue_empty(struct queue *q) {
  return q->head == NULL;
}


void init(struct graph *graph, int edges) {
  for (int i = 0; i < edges; i++) {
    int from = rand() % N;
    int to = rand() % N;

    if (from != to) {
      graph->g[from][to] = graph->g[to][from] = 1;
    }
  }
}

int main() {
  struct queue q;
  init_queue(&q);

  print_queue(&q);
  enqueue(&q, 5);
  print_queue(&q);
  enqueue(&q, 2);
  enqueue(&q, 16);
  print_queue(&q);
}
