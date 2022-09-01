#include "useful.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int x = 0x87654321;
unsigned int w = 32;

int main(void) {
  size_t size = sizeof(unsigned int);
  print_bytes((byte_pointer)&x, size);
  int result = (x & 0xff);
  printf("a: int-> %d\t\tbytes-> ", result);
  print_bytes((byte_pointer)&result, size);
  result = ~0xff ^ x;
  printf("b: int-> %d\tbytes-> ", result);
  print_bytes((byte_pointer)&result, size);
  result = 0xff | x;
  printf("c: int-> %d\tbytes-> ", result);
  print_bytes((byte_pointer)&result, size);
}
