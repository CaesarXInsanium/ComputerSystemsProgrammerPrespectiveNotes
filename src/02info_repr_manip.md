# Representing and Manipulating Information

Computers represent all values as binary. This is because it is simpler and easier
to handle as opposed to using continuous values. True power comes when we give
meaning to certain patterns of zeroes and ones. These `interpretations` can encode
values such as naive unsigned integers that can represent natural numbers greater
than zero, `two's complement` signed integers that can represent integers and
`floating point` that can approximate decimal values. However, due to the discrete
nature of binary, there is a finite number of values that can be represented.

As the nature of reprinting an infinite number line with a finite set of bits
inaccuracies and errors are bound to occur. Take floating point, we can represent
the value PI only to a certain extent before running out of bits. Arithmetic with
floating point values may yield mathematically incorrect results.

Understanding these concepts can reduce bugs and security vulnerabilities that can
occur.

## Information Storage

Most computers view memory as blocks of 8 bits. `Virtual Memory` is the memory that
is presented to a program to be used. `Addresses` are unique locations to
`machine words` located in the `virtual address space`.

The C compiler looks at the type of each value in order to determine what sort of
machine code to generate for each instruction. Actual machine code has no types
for everything are just bits and bytes.

### Hexadecimal Notation

All bytes are 8 bits. Decimal notation is inappropriate for representing binary data
so usually hexadecimal notation is used instead. Each digit in hex can represent
16 different values. Converting between hexadecimal and binary is trivial since
each hex digit has a unique 4 digit binary representation. And each 4 bits can
be easily converted to hex.

Make a convention chart.

#### Practice Problem 2.1

A. 0x25b9d2

```text
0010 0101 1011 1001 1101 0010
```

B. 1010 1110 0100 1001

```text
0xAE4
```

C. 0xa8b3d

```text
1010 1000 1011 0011 1101
```

D. 0110 0100 0101 1011 0001 0110

```text
0x645b16
```

#### Practice Problems 2.2

|n | 2^n | 2^n hex |
|--|-----|---------|
| 5| 32 | 0x20 |
|23|8388608| 0x800000|
|15 | 32768 | 0x8000 |
| 17 | 131072 | 0x2000 |
| 16 | 65536 | 0x1000 |
| 6 | 64 | 0x40 |
| 3 | 4096 | 0x100 |

#### Practice Problem 2.3

| Decimal | Binary | Hexadecimal |
|---------|--------|-------------|
| 0    |0b00000000 | 0x00        |
| 148 | 10011110     | 0x9e    |
| 76 | 10011000   | 0x4c   |
| 145 | 10010001 | 0x91 |
| 174 | 1010 1110 | 0xae |
| 60 | 0011 1100 | 0x3c |
| 241 | 1111 0001 | 0xf1 |
| 117| 0111 0101 | 0x75 |
| 189 | 1011 1101 | 0xbd |
| 245 | 1111 0101 | 0xf5 |

#### Practice 2.4

```text
A. 0x6061
B. 0x603c
C. 0x608c
D. 0x009e
```

### Data Sizes

All computers have a word size, the size of a single memory address/pointer.
Word size is determining the size of the virtual address space. The shift in machines
using 32 bits addresses to 64 bits allow for an extreme increase in the amount
of memory that can be addresses with each word size pointer to 16 exabytes.

We can compile programs in GCC to 32 and 64 bit using flags

```bash
gcc -m32 prog.c
gcc -m64 prog.c
```

A 64 bit machine would be able to run both results, but a 32 bit machine can only
run the 32 bit version.

Different data types supported by compilers take up different amounts of bytes
and are determined by the C implementation and programmer definition. In C some
data types are fixed regardless of implementation.

### Addressing and Byte Ordering

Items are stored in continuous chunks of memory. Each individual byte can be addressed
and resolved by taking the size of an object and calculating from the address.

Little Indian is when least significant bit is stored first in memory while big
Indian is when the most significant bit is stored first.

```text
0b1000 = 1 in little endian
0b1000 = 8 in big endian
```

This concept can also be applied to bytes, as some machines implement things this
way. Intel machines use little endian mode while big endian is used by IBM. Ordering
can also depend on the operating system and hardware support. There is generally
no difference between them except when machine communicate over network. However,
network protocols establish rules on byte ordering.

Byte ordering can be important when using assembly to deal directly with binary
and addresses.

Here is code that shows byte representation of things.

```c
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  int i;
  for (i = 0; i < len; i++) {
    printf(" %.2x\n", start[i]);
  }
}
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
  return 0;
}
```

Here are my results

```text
 64
 00
 00
 00
 00
 00
 c8
 42
 c8
 c3
 b1
 a3
 fe
 7f
 00
 00
```

The story changes yet again with floating point numbers. Floats are a standard that
is kept the same all across the world, usually.

#### Practice Problem 2.5

```text
A. 78 12
B. 7856 1234
C. 785634 123456
```

#### Practice Problem 2.6


```text
int = 0x0027c8f8
float = 0x4a1f23e0
A. 
int   = 00000000 00100111 11001000 11111000
float = 01001010 00011111 00100011 11100000

B. they basically do not match. 18 bits match
C. 32 - 18 = 14, 14 bits do not match
```

### Representing Strings

Strings are simply arrays of characters ending in null character. These characters
follow a standard for which each byte or sequence of bytes represent a character
in a language.

#### Practice Problem 2.7

```text
 6d 6e 6f 70 71 72
```

## Integer Representation

## Integer Arithmetic

## Floating Point
