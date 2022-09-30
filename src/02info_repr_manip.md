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

The range of values that can be represented of signed integers vs unsigned is not
symmetrical. This is due to the nature of having one bit being the sign bit. It is
more of a sign weight, this one bit represents a negative weight. And zero itself
has to represented, so there is one greater positive value as opposed to negative
value.

```text
# here word size is 16
-1 = 0xffff = 1111111111111111
 0 = 0x000  = 0000000000000000
```

Two's complement is not required but nearly all C implementations use it. A good
assumption to make is assuming that the ranges in values for the different data types
different between implementations and plan around this in order to maximize portability
between architectures. C has some macros that contain different ranges of values.

```c
#include <limits.h>
```

### Conversions between Signed and Unsigned

Conversions between data types can different based on the implementation in C.
Most what usually happens is that C takes the bits of a data type and reads them
as another type. This only happens in conversions from between signed and unsigned
data.

Function for converting from two's complement to unsigned is defined as

$$
T2U_w (x) = \text{if }x < 0, x + w^2 ,  \text{else if }   x \ge 0, x
$$

function for unsigned to two's complement

$$
U2T_w(u) = \text{if } u \le TMax_w, u, \text{else if } u >TMax_w, u - 2^w
$$

### Signed versus Unsigned in C

By default, we're specifying an integer literal, the compiler assumes that it is
a signed integer unless formatted otherwise. C standard defines what conversions
between data types should result in but not how. Conversion can be explicit or implicit.
`Printf` format specifiers are also capable of calling conversion for data types.
When operations between signed and unsigned data is done, the signed data type is
cast to unsigned before anything happens.

### Expanding Bit Representation of Number

One of the most common operations done on integers in converting them from 32 bit
to 64 bit or any word size. Doing so can either increase the number of possible
values that can be represented, or it can decrease it.

Expanding unsigned integers is easy as adding leading zeroes.

```text
0001 -> 00000001
```

Expanding two's complement signed integer requires sign extension. Thing is the
same when dealing with positive number but when dealing with negative numbers, the
sign bit remains turned on however other bits must also be turned on in order to
compensate. One interesting thing that I have seen is that two's complement a bit
of expansion adds leading ones, if the value being represented is close to 0.

### Truncating Numbers

Reducing the number of bits of a value reduces the range of value that a set of
bits can represent. Truncating a number from a position that cannot be represented
in a form with fewer bits results in a form of overflow.

### Advice on Signed vs Unsigned

Overlooking casting behavior of the compiler and spec can lead to difficulty in
finding some nasty bugs. Due to this some languages do not implement unsigned
integers and Java enforces the two's complement implementation of integers.

### 2.2 Exercises

```text
2.17
0xA 1010 (2^3 + 2^1 = 10) (-2^3 + 2^1 = -6)
0x1 0001 (2^0 = 1) (2^0 = 1)
0x2 0010 (2^1 = 2) (2^1 = 2)
0x7 0111 (2^2 + 2^1 + 2^0 = 7) (2^2 + 2^1 + 2^0 = 7)
0xC 1100 (2^3 + 2^2 = 12) (-2^3 + 2^2 = -4)

2.18
0010 1110 0000 = 736
0101 1000, 8 + 16 + 64 = -88
0010 1000 = 40
0011 0000 = 48
0111 1000 = 120
1000 1000 = 136
0001 1111 1000 = 504
1100 0000 = -64
- 0100 1000

2.19
-1 -> 1111 -> 15
-5 -> 1011 -> 11
-6 -> 1010 -> 10
-4 -> 1100 -> 12
1  -> 0001 -> 1
8  -> 1000 -> 8

2.20

I used by converting the hex to binary and then back to unsigned values, ignoring
the signe bit by adding the correct value for each bit.

2.21 # This is most likely wrong, it is wrong

0
1
1
1
1
```

Check my code at

```c
{{#include ../code/02ch/bit32.c}}
```

```text
2.22
10101010110101010010101010101010
00101010000000000000000000000000
00000000000000000000000000101010

it drops the leading 24 bits
```

Here is code fore 2.23 A

```c
{{#include ../code/02ch/expanding_bit.c:25:69 }}
```

It prints this out

```text
a = 118:         76 00 00 00
fun1:  76 00 00 00
fun2:  76 00 00 00

b = 2271560481:  21 43 65 87
fun1:  21 00 00 00
fun2:  21 00 00 00

c = 201:         c9 00 00 00
fun1:  c9 00 00 00
fun2:  c9 ff ff ff

d = 3989547399:  87 a9 cb ed
fun1:  87 00 00 00
fun2:  87 ff ff ff
```

One useful thing that it does is it allows use to get a value stored only in the
first 24 bits of a data type. Ignoring everything else for the first function. For
the second function.

In exercise 2.25 the error occurs because we are using a signed value that can
represent negative values. It crashes because it is accessing memory that does not
belong to the float array and my operating system detects that.

Exercise 2.26: In one case the former string could actually be less than the latter
string. The function return unsigned values negative lies cannot be represented
and an overflow occurs. It may be fixed with this code.

```c
#include <stdint.h>


size_t strlen(const char *s);
int strlonger(char *s, char *t) {
  return strlen(s) >
         strlen(t); // I will just let the implementation fix it for me.
}
```

## Integer Arithmetic

Due to the way computers work adding two numbers does not lead to the mathematically
correct answer.

### Unsigned Addition

It is a general rule of thumb that if two integers using *w* number of bits to
represent them require *w + 1* bits in order to fully represent the range of values
that can result from their addition. If we add 2 4 bit unsigned integers it requires
5 bits to represent the result of any addition.

Instead, a form of modular Arithmetic is used in which a modulo operation is used
mathematically instead of normal addition.

For example given integers 8 and 11. Both require minimum 4 bits to represent them.
Due to the way that computers can work the result of adding the two integers
would be the same as this example.

$$
(8 + 11 ) \mod 16 = 3
$$

```text
1000 + 1011 = 10011
drop most significant bit
0011 = 3
this is what integer overflow is
```

Here we take the result of normal addition and drop the most significant bit in
order to get a result.

As such unsigned addition is defined mathematically as

$$
x + y = \text{if } x + y < 2^w \text{ then } x+y
\text{ else } x + y - 2^w
$$

It is important to know that integer overflow is part of the C specification and
as such is not treated as an error. However, many bugs and security vulnerabilities
can result due integer overflow.

One method of checking for overflow is seeing if one the result of an addition
is less than one of the arguments. If so then an overflow as occurred and appropriate
measures can be taken. For example is *x* and *y* are two arguments for addition
and *s* is the result, then overflow as occurred if,

$$
s = x + (y - 2^w) < x
$$

Here *w* denotes the number of bits used to represent the numbers.

In order to get a number that is the additive inverse of a number just subtract
from the integer maximum the number in question. The additive inverse of a number
is simply the number that when added together will result in an integer overflow
to zero.

### Two's Complement Addition

Two's complement addition is very similar to normal unsigned addition except that
now negative overflow exists. Overflow occurs in the positive and negative extremes
of the range that a signed integer has. I would write this out in latex, but I will
rather not instead I will write it in python

```python
def add(x, y):
    w = 8  # number of bits
    if pow(2, w-1) <= x + y:
        return x + y - pow(2, w)
    elif (-pow(2, w-1) <= x + y) and (x + y < pow(2, w-1)):
        return x + y
    elif x + y < -pow(2, w-1):
        return x+y+pow(2, w)
```

Now I write it in scheme because why the fuck not. I did it because python
is boring and scheme is fun.

```scheme
(define (pow a b)
  (cond ((<= b 0) 1)
         ((= b 1) a)
         ((< b 0) 0)
         (else (* a (pow a (- b 1))))))

(define (add x y)
  (define w 8)
  (cond
    ((>= (+ x y)(pow 2 (- w 1))) (+ x (- y (pow 2 w)))) ;; positive overflow
    ((< (+ x y) (- 0 (pow 2 (- w 1)))) (+ x (+ y (pow 2 w)))) ;; negative overflow
    (else (+ x y))))
```

### Integer Arithmetic Practice Problems

2.27

```c
{{#include ../code/02ch/integer_arithmetic.c}}
```

2.28

|Hex | Decimal | Inverse Decimal | Inverse Hex|
|-----|---------|----------------|------------|
| 1   | 1       | 15             | f |

## Floating Point
