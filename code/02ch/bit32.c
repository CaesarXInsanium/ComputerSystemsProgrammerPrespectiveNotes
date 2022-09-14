#include <stdint.h>
#include <stdio.h>

int main(void) {
  int32_t a = -2147483647;
  int32_t b = 2147483647;

  printf("%d\n", a - 1 == b);
  printf("%d\n", a - 1 < b);
  printf("%d\n", (int32_t)(a - (uint32_t)1) < b);
  printf("%d\n", a - 1 < a);
  printf("%d\n", (int32_t)(a - (uint32_t)1) < a);
}
