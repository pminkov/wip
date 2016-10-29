#include <stdlib.h>
#include <stdio.h>

struct Vector {
  int *arr;
  int size;
  int capacity;
};

void init_vector(struct Vector *v) {
  v->arr = NULL;
  v->size = 0;
  v->capacity = 0;
}

void add_value(struct Vector *v, int value) {
  if (v->size == 0) {
    v->arr = malloc(sizeof(int));
    v->arr[0] = value;
    v->size = 1;
    v->capacity = 1;
  } else {
    if (v->size >= v->capacity) {
      v->capacity *= 2;
      v->arr = realloc(v->arr, sizeof(int) * v->capacity);
    }

    v->arr[ v->size++] = value;
  }
}

void print_vector(struct Vector *v) {
  printf("cap = %2d | ", v->capacity);
  for (int i = 0; i < v->size; i++) {
    printf("%d ", v->arr[i]);
  }
  printf("\n");
}

int main() {
  struct Vector v;
  init_vector(&v);

  print_vector(&v);

  for (int i = 1; i <= 20; i++) {
    add_value(&v, i + 5);
    print_vector(&v);
  }
}
