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

### Representing Strings

Strings are simply arrays of characters ending in null character. These characters
follow a standard for which each byte or sequence of bytes represent a character
in a language.

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

One useful thing that it does is it allows use to get a value stored only in the
first 24 bits of a data type. Ignoring everything else for the first function. For
the second function.

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
rather not instead I will write it in scheme.

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

Due to some wacky properties of signed integer addition, the bit representations
of signed numbers can be added by simply interpreting them as unsigned integers
and applying unsigned addition. Addition can also be done by using normal binary
addition and truncating bits.

An interesting property is that there are more cases with negative overflow than
positive overflow with signed integer addition.

### Two's Complement Negation

Each signed and unsigned integer number has an additive inverse that when added
will overflow and result in zero. For signed integers it is simply the negative
versions of them and if it is equal to the minimum value possible then it is itself.
As can be seen with this function.

```scheme
(define (tneg x)
  (cond ((= x tmin) x)
        ((> x tmin) (- 0 x))))
```

An easy way to do it on the bit level is to do bitwise NOT on the bits and then
increment by one.

```text
0101 5 1010 -6 10011 -5
```

### Unsigned Multiplication

Some say that multiplication is simply repeated addition. Unsigned multiplication
is defined as,

```scheme
(define (unsigned_mul x y)
  (mod (* x y) (pow 2 w)))
```

This is because the multiplication ranges even greater than addition and would require
twice as many bits each time to represent them.

### Two's Complement Multiplication

Signed integer multiplication requires as many bits as unsigned. It basically only
is first interpreting the signed integers are unsigned, applying unsigned multiplication
and then reinterpreting the bits as signed. At all times not using more bits than
what the original types used.

### Multiplying by Constants

Normal multiplication instructions on a CPU where slow because the implementation
required multiple clock cycles whereas addition and subtraction was fast since
it only required one clock cycle. So attempts where made to speed up multiplication
using a combination of addition and bit shifts.

Bit shift operations where the bits move by value *k* are equivalent to multiplication
and division by powers of 2 to the *k*. This only works if k is greater than zero
and less than the number of bit used to represent the integers.

```c
#include <math.h>
#include <assert.h>

int main(){
  unsigned k = 1;
  unsigned a = x * pow(2,k);
  unsigned b = x << k;
  assert(a == b); // two expression are equivalent
  
}
```

Compilers will try to replace normal multiplication instruction calls to bit shifting
call when it is trying to optimize the machine code.

Of course one must be careful because multiplication is an operation very easily
causes overflow if dealing with big enough numbers. C compiler developers must know
math and can recognize some patterns.

```text
14 * x is the same as  x * (2^3 + 2^2 + 2^1)
it can be rewritten as (x * 2^3 + x * 2^2 + x * 2^1)
the compiler will then optimize to
(x << 3) + (x << 2) + (x << 1)
```

However, this is a decision that is very architecture and compiler dependent.

### Dividing by Powers of Two

Basically the same as multiplication by powers of 2 except we are bit shifting to
the right instead of left. However, this time the result is the ceiling of the true
mathematical operation. It cuts of the fractional part and returns only an integer.

Compilers optimize this fact away and is fun. With unsigned integers' division is
performed with logical bit shifts and with signed integers it is performed arithmetically.

## Floating Point

Floating points numbers are used for encoding very large or very accurate numbers.
However, it can lose precision in doing so. Before IEEE standards floating point
numbers implemented by every computer manufacturer differently with emphasis on
speed and simplicity over accuracy. Now with the IEEE standard ruling everything
programmer can be sure that any computer that support IEEE standards can have
code that treats decimal numbers evenly.

There are many problems with floating point numbers including rounding and mathematical
inconsistency.

### Fractional Binary Numbers

In order to understand fractional binary number one must understand fractional decimal
numbers. Each place in a decimal numbers represent a base value multiplied by 10
to some power. Going left we raised to positive numbers. However, going right
with raise 10 to negative numbers. The same be applied with fractional binary numbers.

$$
d = \sum_{i=-n}^m (10^i * d_i)
$$

Here this is a sum given a set of digits \\( d_1, d_2, d_2, ... , d_i \\) where
each digit represents a number from 0 to 9. Each is multiplied against a corresponding
power to 10. This can in the negative.

Here is the binary equivalent.

$$
b = \sum_{i=-n}^m (2^i * b_i)
$$

Another limitation of floating point numbers is that they can only represent a small
subset of the real number line. All other are approximations.

### IEEE Floating-Point Representation

IEEE standard denotes floating point number in of form

```scheme
(define (float s m e)
  (* (pow -1 s)
     m
     (pow 2 e)))
```

Where s is the bit sign denoting positive or negative, m is the fractional binary
number between zero and 1 minus epsilon. Exponent e denotes the weight. These are
packed into a 32 or 64 bit a bit of data that have different sections based on what
information they contain.

In cases where the exponent section of the floating point number is neither all zeroes
nor all ones, then it is used to represent the signed value of the exponent. The
fractional sections represent values from 0 to 1, exclusive to 1. If the exponent
part is all ones it represents infinity if the fractional part of all zeroes.
NaN occurs when the exponent part is all ones and fractional part is not all
zeroes.

```text
s1111111100000000000000000000000 # infinity
s1111111100001010100101001010001 # NaN
```

Denormalized values occur when exponent field is all zeroes. These values are used
either represent zero or numbers that are very close to zero.

Not a number of values are resulted when finding the square root of negative one
and adding and subtracting infinity.
