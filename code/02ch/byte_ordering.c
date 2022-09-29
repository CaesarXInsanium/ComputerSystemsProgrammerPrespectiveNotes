#include "useful.h"
#include <stdio.h>
#include <string.h>

void show_int(int x) { show_bytes((byte_pointer)(void *)&x, sizeof(int)); }
void show_float(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }
void show_pointer(void *x) { show_bytes((byte_pointer)&x, sizeof(void *)); }

void text_show_bytes(int val) {
  int ival = val;
  float fval = (float)ival;
  int *pval = &ival;
  show_int(ival);
  show_float(fval);
  show_pointer(pval);
}

int main(void) {
  text_show_bytes(100);

  printf("\n2.5\n");
  int a = 0x12345678;
  byte_pointer ap = (byte_pointer)&a;
  show_bytes(ap, 1);
  show_bytes(ap, 2);
  show_bytes(ap, 3);

  printf("\n2.7\n");
  const char *m = "mnopqr";
  show_bytes((byte_pointer)m, strlen(m));

  return 0;
}
