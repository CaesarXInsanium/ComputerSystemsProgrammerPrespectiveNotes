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

### Representing Code

When C code is compiled, binary data is always generated. However, this data is special
since is representing instructions for things for the computer to do. Different machines
required different encoding and standards in order for the CPU to understand anything.

### Introduction to Boolean Algebra

Since computer are built on one's and zeroes, binary data it makes sense that all
logic that is run on a computer are built on the foundations of boolean algebra.

Boolean algebra is defined over any two element set with the operations `NOT`, `OR`,
`XOR` and `AND`. I already know most of the basics. Boolean operations can be extended
to boolean vectors or arrays of bits, bytes. Here is an example,

One way to use this to our advantage is to encode information inside individual
bits that are in a byte. This method allows for squeezing as much information
as possible into a little area as possible.

```text
  0110
& 1100
------
  0100
```

### A bit Level Operations in C

In C the data type that is meant to be used for bitwise operations is `char`.

`Bit masking` is when a bit pattern is used to extract and read values from selected
bits inside a machine word. Doing AND operations would allow one to make an interface
where certain flags can be turned on if certain bit values are switched one.

### Logical Operators in C

Logical operators in C `&&`, `||`, `!` Allow for use in logical operations. Any
non-zero argument resolves to TRUE and zero is false. Applying double NOT will return
0x01.

### Shift Operators

Shift bits a certain number of places and replacing lost bits with zeroes.

Logical bit right shift replaces lost bits with zeroes.

Arithmetic bit right shift replaces lost bits with zeroes. This only happens on
signed data and in some C implementations as the standard does not define this behavior.

#### Practice Problems Boolean Algebra

```text
exe 2.8
a  = 0b01001110
b  = 0b11100001
-a = 0b10110001
-b = 0b00011110
a & b = 0b01000000
a | b = 0b11101111
a ^ b = 0b10101111

exe 2,9
white
green
blue

exe 2.10
x = 8  =  0b00001000
y = 10 =  0b00001010

y = x ^ y = 0b00000010
x = x ^ y = 0b00001010
y = x ^ y = 0b00001000

```

Exercise 2.11 my work.

```c
{{#include ../code/02ch/reverse_array.c}}
```

Exercise 2.12

```c
{{#include ../code/02ch/reverse_array.c}}
```

I cheated on 2.13

Exercise 2.14

```text
a = 0x55 = 01010101
b = 0x46 = 01000110
a & b = 01000100
a | b = 01010111
~a | ~b = 10110011
a & !b = 00000000
a && b = 00000001
a || b = 00000001
!a || !b = 00000000
a && ~b = 00000001
```

 Exercise 2.16

| Hex | Binary | Bin | Hex | Bin  | Hex | Bin | Hex |
|-----|--------|-----|-----|------|-----|-----|-----|
| 0xd4 | 11010100 | 01010000 | 0x50 | 00011110 | 0x16 | 11110110 | 0xf6 |  
| 0x64 | 01100100 | 10010000 | 0x90 | 00001100 | 0x0c | 11101100 | 0xec |
| 0x72 | 01110010 | 11001000 | 0xc8 | 00001110 | 0x0e | 11101110 | 0xee |
| 0x44 | 01000100 | 00010000 | 0x10 | 00001000 | 0x08 | 11101000 | 0xe8 |

> Note: first row is all wrong!!

## Integer Representation

There are two major ways to represent integers. Both of which have properties that
allow for easy manipulation using discrete mathematics and hardware encoding. There
are a variety of different function that can be applied to integers. Here are some
examples,

- binary two's complement
- binary to unsigned
- minimum two's complement

### Integral Data Types

C standard allows for the different basic data types to be represented in whichever
which way best suits a particular target and implementation. Programmer will be
able to choose from a variety of simple data types that can be signed or unsigned.

Signed integers can represent negative numbers and unsigned integers cannot represent
negative values. The range of a signed integer equal to unsigned but is only half
in one direction.

- char: -128 127
- unsigned char: 0 255

The implementation allows for differences in behaviors between 32 bit and 64 bit
machines. One such important difference is the value range of signed and unsigned
values.

### Unsigned Encoding

If we consider a set of *w* bits, we can denote them in a mathematical setting.
Then the Binary to Unsigned function is the sum of the individual bits times 2 to
the power of its corresponding index. This function takes a set of bits and converts
them to its decimal representation. This way only positive numbers are represented.

$$
B2U_w (\overrightarrow{x}) \doteq \sum_{i=0}^{w-1}x_i 2^i
$$

Here the index is counted from the right most position. \\(x_i \\) denotes the
individual bit, which can be 0 or 1. Using this formula conversions are easy.

```text
B2U(0001) = 0 * 2^3 + 0 * 2^1 + 0 * 2^1 + 1 * 2^0 = 0 + 0 + 0 + 1 = 1
B2U(0101) = 0 * 2^3 + 1 * 2^1 + 0 * 2^1 + 1 * 2^0 = 0 + 4 + 0 + 1 = 5
B2U(0001) = 1 * 2^3 + 0 * 2^1 + 1 * 2^1 + 1 * 2^0 = 8 + 0 + 2 + 1 = 11
B2U(0001) = 1 * 2^3 + 1 * 2^1 + 1 * 2^1 + 1 * 2^0 = 8 + 4 + 2 + 1 = 15
```

### Two's Complement Encoding

Sometimes negative numbers are useful. For that we have two's complement encoding.
This is defined as having most significant bit as having negative weight. We have
the definition of two's complement as this for vector
\\(\overrightarrow{v}=\[x_{w-1}, x_{w-2}, ..., x_0\] \\)

$$
B2T_w(\overrightarrow{x}) \doteq -x_{w-1}2^{w-1} + \sum_{i=0}^{w-2}x_i 2^i )
$$

The most significant bit is also called the sign bit. This means that this thing
is multiplied against negative value of its own position that is then added to the
following values represented by the following bits. Here are some examples.

```text
B2T_4([0001]) = -0 * 2^3 + 0 * 2^2 + 0 + 2^1 + 1 * 2^0 = 0 + 0 + 0 + 1 = 1
B2T_4([0101]) = -0 * 2^3 + 1 * 2^2 + 0 + 2^1 + 1 * 2^0 = 0 + 0 + 4 + 1 = 5
B2T_4([1011]) = -1 * 2^3 + 0 * 2^2 + 1 + 2^1 + 1 * 2^0 = -8 + 0 + 2 + 1 = -5
B2T_4([1111]) = -1 * 2^3 + 1 * 2^2 + 1 + 2^1 + 1 * 2^0 = -8 + 4 + 0 + 1 = -1
```

Due to some unique properties of math with binary numbers, these two function
are the inverse of each other.

#### 2.2 Exercises

## Integer Arithmetic

## Floating Point
