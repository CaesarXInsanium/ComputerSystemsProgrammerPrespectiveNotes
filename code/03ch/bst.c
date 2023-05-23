#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { N_LEAF, N_INTERNAL } note_t;

typedef struct {
  note_t type;
  union {
    struct {
      struct Node *left;
      struct Node *right;
    } Node_t;
    double data[2];
  } info;
} Node;
