#include "useful.h"
#include <stdio.h>

float sum_elements(const float a[], unsigned length) {
  int i;
  float result = 0;
  for (i = 0; i <= (int)length - 1; i++) {
    result += a[i];
    printf("i = %d\n", i);
  }
  return result;
}

int main(void) {
  float a[] = {0, 1, 2, 3, 4};
  float result = sum_elements(a, 0);
  printf("Result: %f\n", result);
  puts("Exe 2.25");
}
