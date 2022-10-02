#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int uadd_ok(unsigned x, unsigned y) {
  unsigned s = x + y;
  if (s < x || s < y) {
    return 0;
  } else {
    return 1;
  }
}

int tadd_ok(int x, int y) {
  int s = x + y;
  if (x > 0 && y > 0) {
    if (s < 0) {
      return 0;
    } else {
      return 1;
    }
  } else if (y < 0 && x < 0) {
    if (s > 0) {
      return 0;
    } else {
      return 1;
    }
  } else if (y == 0 || x == 0) {
    return 1;
  } else {
    return 1;
  }
}

int main(void) {
  puts("Exercise 2.29");
  printf("Does %u + %u cause no overflow? %d\n", 2, 4, uadd_ok(2, 4));
  printf("Does %u + %u cause no overflow? %d\n", 255, 4, uadd_ok(255, 4));
  printf("Does %u + %u cause no overflow? %d\n", UINT32_MAX, 4,
         uadd_ok(UINT32_MAX, 4));
  printf("Does %u + %u cause no overflow? %d\n", UINT32_MAX, 1,
         uadd_ok(UINT32_MAX, 1));
  printf("Does %u + %u cause no overflow? %d\n", UINT32_MAX, 0,
         uadd_ok(UINT32_MAX, 0));

  printf("Other exercise 2.31\n");

  printf("Does %d + %d cause no overflow? %d\n", INT32_MAX, 0,
         tadd_ok(INT32_MAX, 0));
  printf("Does %d + %d cause no overflow? %d\n", INT32_MAX, 1,
         tadd_ok(INT32_MAX, 1));
}
