#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int uadd_ok(unsigned x, unsigned y) {
  unsigned s = x + y;
  printf("%u + %u = %u\n", x, y, s);
  if (s < x || s < y) {
    return 0;
  } else {
    return 1;
  }
}

int tadd_ok(int x, int y) {
  int s = x + y;
  printf("%d + %d = %d\n", x, y, s);
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

int tsadd_ok(int x, int y) {
  int sum = x + y;
  printf("%d + %d = %d\n", x, y, sum);
  return (sum - x == y) && (sum - y == x);
}

int tsub_ok(int x, int y) { return tadd_ok(x, -y); }

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

  printf("Exercise 2.30\n");

  printf("Does %d + %d cause no overflow? %d\n", INT32_MAX, 0,
         tadd_ok(INT32_MAX, 0));
  printf("Does %d + %d cause no overflow? %d\n", INT32_MAX, 1,
         tadd_ok(INT32_MAX, 1));

  printf("Exercise 2.31\n");

  printf("Does %d + %d cause no overflow? %d\n", INT32_MAX, 0,
         tsadd_ok(INT32_MAX, 0));
  printf("Does %d + %d cause no overflow? %d\n", INT32_MAX, 1,
         tsadd_ok(INT32_MAX, 1));

  printf("Exercise 2.32\n");

  printf("Does %d - %d cause no overflow? %d\n", INT32_MIN, 0,
         tsadd_ok(INT32_MIN, 0));
  printf("Does %d - %d cause no overflow? %d\n", INT32_MIN, 1,
         tsadd_ok(INT32_MIN, 1));
  printf("Does %d - %d cause no overflow? %d\n", INT32_MAX, INT32_MIN,
         tsadd_ok(INT32_MAX, INT32_MIN));
}
