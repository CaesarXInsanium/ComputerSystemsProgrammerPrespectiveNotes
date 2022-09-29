#include "useful.h"

inline int bis(int x, int m) { return x | m; }
inline int bic(int x, int m) { return x & ~m; }

int bool_or(int x, int y) {
  int result = bis(x, y);
  return result;
}

int bool_xor(int x, int y) {
  int result = bis(bic(x, y), bic(y, x));
  return result;
}
int main() {
  int s = 8;
  int h = 100;
  int g = bool_or(s, h);
  show_bytes((byte_pointer)&g, sizeof(int));
}
