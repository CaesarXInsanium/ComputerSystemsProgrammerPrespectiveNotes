#include "lib/useful.h"
#include <stdio.h>
#include <stdlib.h>

void print_bytes(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void print_array(int a[], int cnt) {
  for (int i = 0; i < cnt; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int *random_sized_array(int size) {
  int *a = (int *)malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    a[i] = rand();
  }
  return a;
}

int *sorted_num_array(int size) {
  int *a = (int *)malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    a[i] = i;
  }
  return a;
}
