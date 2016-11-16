#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int read_int(FILE *fptr) {
  int num;
  fread(&num, sizeof(int), 1, fptr);
  return num;
}

void write_int(FILE *fptr, int num) {
  size_t br = fwrite(&num, sizeof(int), 1, fptr);
  assert(br == 1);
}

void print_file() {
  FILE *fptr = fopen("numbers.bin", "rb");

  while (1) {
    int r = read_int(fptr);
    if (feof(fptr)) break;
    printf("%d ", r);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  srand(314);

  int N = 10;
  if (argc == 2) {
    N = atoi(argv[1]);
  }

  FILE *fptr = fopen("numbers.bin", "wb+");
  
  if (fptr == NULL) {
    printf("Error in opening file");
    exit(1);
  }

  for (int i = 0; i < N; i++) {
    int r = rand() % 30; 
    write_int(fptr, r);
  }

  fclose(fptr);
  printf("Starting sort.\n");

  print_file();

  int swapped;
  int swaps = 0;
  int scans = 0;
  do {
    swapped = 0;

    fptr = fopen("numbers.bin", "r+");
    scans++;

    int last;
    for (int i = 0; i < N; i++) {
      int cur = read_int(fptr);
      size_t cpos = ftell(fptr);
      assert(cpos == sizeof(int) * (i + 1));

      if (i > 0 && last > cur) {
        fseek(fptr, -2 * sizeof(int), SEEK_CUR);
        write_int(fptr, cur);
        write_int(fptr, last);
        assert(cpos == ftell(fptr));
        swapped = 1;
        swaps++;
      } else {
        last = cur;
      }
    }

    fclose(fptr);
  } while (swapped);

  print_file();

  printf("N: %d\n"
    "Swaps: %d\n"
    "Scans: %d\n", N, swaps, scans);
}
