#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef union {
  int32_t integer;
  float floating_point;
  struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
  };
} UnsafeUnion;

void print_bytes(uint8_t *bytes, int count) {
  printf("Bytes: ");
  for (int i = 0; i < count; i++) {
    printf("%02X", bytes[i]);
  }
  printf("\n");
}

void print_union(UnsafeUnion unnon) {
  printf("Integer Value: %d\n", unnon.integer);
  printf("Float Value: %f\n", unnon.floating_point);
  print_bytes((uint8_t *)&unnon, sizeof(UnsafeUnion));
}

int main(void) {
  UnsafeUnion unnon;
  printf("Size of Union: %d bytes\n", (int)sizeof(UnsafeUnion));
  unnon.integer = 32;
  print_union(unnon);
  unnon.integer = 0;
  print_union(unnon);
  unnon.floating_point = 3.14159265;
  print_union(unnon);
}
