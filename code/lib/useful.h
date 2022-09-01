#pragma once
#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;

// print to standard out the binary data in hex
void print_bytes(byte_pointer start, size_t len);
// prints to standard out values in integer array
void print_array(int a[], int cnt);

int *random_sized_array(int size);
int *sorted_num_array(int size);
