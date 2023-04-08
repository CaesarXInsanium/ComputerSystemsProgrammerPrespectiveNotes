# Machine Level Representation of programs

We see a review on what computers do. Computer work by executing machine code
instructions and applying them on data. Machine code is data and is generated
from a source file using a compiler. In C this process goes as follows

1. Text file, source
2. Preprocessor: generates a single C source and change file according to
  directives
3. Compiler: will generate assembly from source
4. Assembler: will generate object files, missing some function definition
5. Linker: will find and give locations of function pointer to generate executable

Problems written in assembly are faster but are more prone to mistakes and catastrophic
memory safety issues. Programming in high level languages like C allows for
more easy management of the risks, thus it is more productive to write in
high level languages as opposed to direct assembly.

Learning assembly is required in order to truly understand the computer system
that code runs on. In order to understand security concerns and optimize programs
to reach maximum utilization of the CPU. The book will be focusing on x86_64 assembly
by Intel and with some AMD contributions.

We will be learning about assembly representations of C constructs such as for loops
while loops, if statements, structs and arrays. We will see just how wacked C
is and how it is easier that programming straight assembly.

In order to understand some x86_64 features first some history must be learned
in order to understand some of the most interesting design features.

## 3.1 Historical Perspective

Intel first began making processors with their revolutionary x86 microprocessor
and each subsequent model was more advanced from the last. Some notable models
include

- 8086: 16-bit, 1978, used in IBM PC, MS-DOS
- i386: 32-bit, 1985, flat addressing, used in Unix
- Pentium: 32-bit, 1993
- Pentium 4: 32-bit, 2000, had SSE2 floating point extensions for double precision
- Pentium 4E: 32-bit, 2004 first with hyper-threading
- Core 2: 64-bit, 2006, first multicore
- Core i7: 64-bit, 2007, had both hyper-threading and multicore

Each successive model design features and designs for maximum backwards compatibility.
This led to some odd legacy features being supported in the most modern
CPUs. Thought most of these features are hidden behind the abstraction of a compiler.

There exists other Intel competitors, but the most notable is AMD, with a long history
with a long history of being behind them in technology and focused solely on
budget segment.

## 3.2 Program Encoding

Generally C code is simply an abstraction over the concept of using human-readable
text that can also be used to generate machine code for machines to understand.
GCC stands for GNU Compiler Collection, but it used to stand for GNU C Compiler.
Generally a C compiler is comprised several stages.

The preprocessor first goes over the source code, makes some changes to source
according to the directives and will also if passed multiple source files
join all the source files into one big source file before being passed to
the compiler.

The compiler will take the source code and generate assembly code. The generated
assembly is code is still in somewhat human-readable format but depending on the
optimization level it may or may not be a 1 to 1 translation from C code to
assembly code. This can also be dependent on which architecture of the compiler
is set to target.

As there are different architectures of CPU, C code was designed to be an abstraction
over the different architecture and meant to allow writing portable code that can
be executed on any of them. The translation to different architectures was done using
the C compiler.

GCC has some flags that allow for C compiler stages to run up to assembly
stage.

```sh
gcc -Og -o hello hello.c
# -O : telling GCC to forgoe all optimizations and generate assembly that is close
# to natie C code
# g : tell GCC to generate assembly only
```

The assembly code generate is passed to an assembler which produce a byte code
representation of the actual assembly code. I say byte code because the different
bytes are used to represent the different instructions and data that a compiler
can be used to represent and also because some symbols/functions have missing
definitions and so the address of the function must be filled in. This is referred
to as object code.

The object code needs to be linked and the missing function definitions filled in
either with other object files or by finding the library that contains the function
definition and passing the address to the binary. With this it is possible to finally
generate binary executable file. If everything when well then the executable runs
your shitty code.

### 3.2.1 Machine Level Code

There are several levels of abstractions when executing code. The binary executable
contains encoded instructions that are read by the CPU and executed on provided data.
These encoding and instructions are defined by the ISA which is the Instruction Set
Architecture. These define what sort of CPU states can be reached, instruction format
and effect on instructions on data.

The assembly code that is generated by the compiler is what the compiler abstracts
and by extension the language abstract away from. In assembly all data, integers,
floats, structs and unions are just sequences of bytes and words. Bytes are only
any of these object simply because we choose to interpret them as such.

In assembly, we deal with features that are hidden by the C compiler.

- Program Counter: address of next instruction
- Register File: there are 16 different location where we can store words, pointers,
  function arguments and return values
- condition code: deals with status information for conditional statements, branch
  execution and repeated execution
- long streams of instructions for executing complex tasks

In C code we have stack and heap memory, but in assembly everything is on the stack
until we make a system call that asks the operating system for more memory.

User mode programs do not write nor read data from real physical memory addresses
but rather from a virtual memory address space, which is controlled by the kernel.
This abstraction allows the program to run under the pretense that it is the only
program running on the computer.

### 3.2.2 Code Examples

We know how to generate assembly code from C with no optimizations using GCC

```bash
gcc -Og -S hello.c
```

Now get ready to generating object code.

```bash
gcc -Og -C hello.c
```

Dissembler like `objdump` can be used in order to reverse the assembler stage
and get assembly code.

```bash
objdump -d hello.o
```

These are possible due to the strict encoding of machine instruction. Individual
instructions range from 1 to 15 bytes long. For each possible instruction there is
a unique string of bytes to represent it. There are strict length and storage
requirements in the encoding so sometimes `nop` operations are added to pad the file.

Generating the final executable.

```bash
gcc -Og -o hello hello.c
```

### 3.2.3 Notes on Formatting

There are some quirks that assembly code has. Assembly code that is generated by
a compiler is not meant for a human to read and so not meant to be easily
understood. In the book they will use the AT&T format when showing assembly code
but, the alternative is the Intel format which remove some redundancies.
The AT&T is used because it is more explicit and more commonly used.

Here is some C code.

```c
#include <stdio.h>

int main(void){
  puts("Hello World!");
}
```

And here is the resulting assembly code. It is output in the AT&T format. The specifiers
prefixed with a dot are directives meant for the assembler.

```x86asm
 .file "hello.c"
 .text
 .section .rodata.str1.1,"aMS",@progbits,1
.LC0:
 .string "Hello World!"
 .text
 .globl main
 .type main, @function
main:
.LFB11:
 .cfi_startproc
 subq $8, %rsp
 .cfi_def_cfa_offset 16
 leaq .LC0(%rip), %rdi
 call puts@PLT
 movl $0, %eax
 addq $8, %rsp
 .cfi_def_cfa_offset 8
 ret
 .cfi_endproc
.LFE11:
 .size main, .-main
 .ident "GCC: (GNU) 12.2.1 20230201"
 .section .note.GNU-stack,"",@progbits
```

## 3.3 Data Formats

Different machine architectures can have different word sizes. Intel specifies
that words are 16 bit values. Machine words correspond to the architecture
of a CPU, 32 bit machines have machine words that are 32 bits long and vice
versa for 64 bit machines. Pointers themselves are the size of machine
words on their corresponding architecture.

Intel assembly can have operand size qualifiers on instructions that relate
to word size, of which there are words, double word and quad word for some
reason.

Floating point values can be single or double precision and relate to the machine
word.

## 3.4 Accessing Information

x86_64 processors contain 16 registers that can contains quad words. In those
registers smaller subsections can be indexed like double words, words and bytes.
Using Intel terminology a word is a 16 bit value, and as such those indexed values
are individual registers that are embedded inside the largest register. Conventions
and the way that procedures are called dictate how the registers should be used and
how the procedure expect the data in the registers to be laid out.

These registers contain function parameters, local variables, return values, a stack
pointer, and temporary values.

### 3.4.1 Operand Specifiers

Instructions that are passed with registers contain relevant data that is to be worked
with. Targets can be other registers, memory. Immediate values are constants inside
the assembly code that are used when computing the memory address of certain values
or for arithmetic. Memory is seen by the CPU as a very large array of bytes, and
it is up to the compiler to generate correct assembly that interprets that memory
as correct data for computing and doing stuff. In order to access items in memory
the correct address must be computed and accessed.

Registers can be accessed wholly or just smaller section of them.

### 3.4.2 Data Movement Instructions

The most common assembly instruction is the `mov` command that moves values between
different locations. Between register and to and from memory. There are different
classes of the
`mov` command that moves to different location and moves different sized values
to different size locations.

If the value is smaller than destination there are commands that will pad out the
wasted with zeroes or will pad with other values. While some movement commands
have dedicated instructions, others can be accomplished with multiple instructions.

In C code, the act of dereferencing to and from pointers are actions that deal
with moving the values store in the registers and writing values to addresses
that were stored in the registers. Pointers in C are all just memory addresses.

### 3.4.4 Pushing and Popping Stack Data

In assembly the program stack is just an array of bytes that hold the address that
represent the data stack. First the values are the end are filled up until we reach
the beginning of the stack.

Dedicated instructions are used for the program stack, a command that will do the
work of two very specific instructions.

Pushing a value will decrement the program stack pointer by 8 and write function
pointer to stack. Popping will write the top of the stack to specified register
and increment the stack pointer by 8.

This implies that the memory that is held by the program itself can be accessed
in assembly using the stack pointer.

## 3.5 Arithmetic and Logical Operators

There are many assembly instructions that are of different classes but
each class sort of does the same sort of thing but with different word input and
output sizes. Within this we have binary operations that work on two operands and
there are unary operations which work on one operand.

### 3.5.1 Load Effective Address

`leaq` instruction is a form of `movq` like instruction that will read a value
from a memory address and stick it inside a register. Essentially store the
address in target register. Used in simple arithmetic.

### 3.5.2 Unary and Binary Operations

Unary operations store a single operand and perform changes to it. The result will
be written back into the provided register.

Binary operations will perform action using the value of the first provided register
and the value of the second register and store the result in the second register.

### 3.5.3 Shift Operators

Will shift the bits of value in register by the amount provided. Includes logical
and arithmetic options. Different versions of the shift the bits a different number
of times.

### 3.5.4 Discussion

Right shifting behaviors sometimes need to use the two's complement for representing
integer values. Round instructions are sometimes used for arithmetic in assembly.

### 3.5.5 Special Arithmetic Operations

Special arithmetic operations must be used when multiplying integer values since
result can be a value greater than what the bits can represent. `IMUL` instruction
will take two 64 bit operands truncate the result. `MULQ` will do the same with but
using 128 bits for the result. However, such behavior is not expected by C standard
and certain flags must be used when compiling programs that do this.

## 3.6 Control
