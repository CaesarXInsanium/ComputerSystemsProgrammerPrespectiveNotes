// generate assembly with
// gcc -Og -S mstore.c
long mult2(long t, long y);

void multstore(long x, long y, long *dest) {
  long t = mult2(x, y);
  *dest = t;
}
