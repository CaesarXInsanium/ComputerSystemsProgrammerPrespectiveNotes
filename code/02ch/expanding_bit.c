#include "useful.h"
#include <stdio.h>

int fun1(unsigned word) { return (int)((word << 24) >> 24); }
int fun2(unsigned word) { return ((int)word << 24) >> 24; }

int main(void) {
  short sx = -12345;
  unsigned uy = sx;
  unsigned short usx = sx;
  int x = sx;
  unsigned ux = usx;

  printf("sx = %d:\t", sx);
  show_bytes((byte_pointer)&sx, sizeof(short));
  printf("usx = %u:\t", usx);
  show_bytes((byte_pointer)&usx, sizeof(unsigned short));
  printf("x = %d:\t", x);
  show_bytes((byte_pointer)&x, sizeof(int));
  printf("ux = %u:\t", ux);
  show_bytes((byte_pointer)&ux, sizeof(unsigned int));
  printf("uy = %u:\t", uy);
  show_bytes((byte_pointer)&uy, sizeof(unsigned int));

  puts("Exercise 2.23");
  unsigned a = 0x00000076;
  unsigned b = 0x87654321;
  unsigned c = 0x000000c9;
  unsigned d = 0xedcba987;

  printf("a = %u:\t", a);
  show_bytes((byte_pointer)&a, sizeof(unsigned int));
  int a1 = fun1(a);
  int a2 = fun2(a);
  printf("fun1: %d\t", a1);
  show_bytes((byte_pointer)&a1, sizeof(int));
  printf("fun2: %d\t", a2);
  show_bytes((byte_pointer)&a2, sizeof(int));
  printf("\n");

  printf("b = %u:\t", b);
  show_bytes((byte_pointer)&b, sizeof(unsigned int));
  int b1 = fun1(b);
  int b2 = fun2(b);
  printf("fun1: %d\t", b1);
  show_bytes((byte_pointer)&b1, sizeof(int));
  printf("fun2: %d\t", b2);
  show_bytes((byte_pointer)&b2, sizeof(int));
  printf("\n");

  printf("c = %u:\t", c);
  show_bytes((byte_pointer)&c, sizeof(unsigned int));
  int c1 = fun1(c);
  int c2 = fun2(c);
  printf("fun1: %d\t", c1);
  show_bytes((byte_pointer)&c1, sizeof(int));
  printf("fun2: %d\t", c2);
  show_bytes((byte_pointer)&c2, sizeof(int));
  printf("\n");

  printf("d = %u:\t", d);
  show_bytes((byte_pointer)&d, sizeof(unsigned int));
  int d1 = fun1(d);
  int d2 = fun2(d);
  printf("fun1: %d\t", d1);
  show_bytes((byte_pointer)&d1, sizeof(int));
  printf("fun2: %d\t", d2);
  show_bytes((byte_pointer)&d2, sizeof(int));
  printf("\n");
}
