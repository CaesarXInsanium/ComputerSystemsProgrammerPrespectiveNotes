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

int main(void) {
  printf("Does %u + %u cause no overflow? %d\n", 2, 4, uadd_ok(2, 4));
  printf("Does %u + %u cause no overflow? %d\n", 255, 4, uadd_ok(255, 4));
  printf("Does %u + %u cause no overflow? %d\n", UINT32_MAX, 4,
         uadd_ok(UINT32_MAX, 4));
  printf("Does %u + %u cause no overflow? %d\n", UINT32_MAX, 1,
         uadd_ok(UINT32_MAX, 1));
  printf("Does %u + %u cause no overflow? %d\n", UINT32_MAX, 0,
         uadd_ok(UINT32_MAX, 0));
}
