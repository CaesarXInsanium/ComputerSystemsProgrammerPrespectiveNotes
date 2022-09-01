#include <stdio.h>
#include <stdlib.h>
#include "useful.h"

void inplace_swap(int *x, int *y) {
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
}

void reverse_array(int a[], int cnt) {
  int first, last;
  for (first = 0, last = cnt - 1; first < last; first++, last--) {
    inplace_swap(&a[first], &a[last]);
  }
}


void print_array(int a[], int cnt);

int main(void) {
  int x = 8;
  int y = 10;
  printf("x: %d\ty: %d\n", x, y);
  inplace_swap(&x, &y);
  printf("x: %d\ty: %d\n", x, y);

  for (int i = 0; i < 10; i++) {
    int size = i;
    int *a = sorted_num_array(size);
    print_array(a, size);
    reverse_array(a, size);
    print_array(a, size);
    printf("\n");
    free(a);
  }
}
