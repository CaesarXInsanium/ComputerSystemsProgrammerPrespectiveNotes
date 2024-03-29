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

Flow control is implemented in assembly by either testing values and choosing
different instructions based on the results of the test.

### 3.6.1 Condition Codes

These are certain bit flags that exist inside a CPU that determined by the results
of certain instructions that test the values provided to them in registers. These
can include

- CF: carry flag, turns on if most significant bit had been carried, overflowed
- ZF: zero flag, returns if last instruction resulted in a zero
- SF: sign flag, if the last numbers were positive or negative.
- OF: overflow flag

`LEAQ` is an instruction that does not alter condition codes. Logical instruction
CF/OF set the zero flag and shifting instructions set the CF that same as the last
bit and OF is set to zero.

`CMP` instruction alters the corresponding conditions flags on based on the result
of comparing two numbers, signed, unsigned or floats

### 3.6.2 Accessing Condition Codes

The condition codes are used for doing conditional code execution, branching and
jumping.
`SET` instruction are used to set values of registers based on what the values of
the condition codes are.

Machine code has no differentiation between data types, it is all bytes. A set of
bit can only be something like an integer if we choose to interpret as an integer.
And so any instruction can be done on any bit of data.

### 3.6.2 Jump Instructions

In text representation of assembly code, `JMP` instructions move to a defined label.
In the binary format it jumps to a defined address in the bytes of the instructions.
It is the job of the assembler to determine the correct addresses for jump labels.
Different jump instructions will jump if and only if certain condition codes/flags
are set.

There are two types of jumps.

- `Direct Jump`: target is encoded in instruction, binary format
- `Indirect Jump`: target must be computed or read from register and/or memory
  location

### 3.6.4 Jump Instruction Encodings

Linking can be done by assembler or specialized linker in order to find the memory
addresses of the instructions that must be executed. They can be used either absolute
or relative addresses.

In order to find addresses, we use and offset of zero from the start of program loaded
in memory and denote of address of target location from there. Labels become addresses
in binary executables. As such the value of program counter is the address of
instructions being executed.

### 3.6.5 Implementing Condition Branches with Conditional Control

In order to implement branching in assembly, a combination of conditional and unconditional
jumps are used. `Goto` statements are the most obvious representation of this
behavior in C. The compiler generates separate blocks of code for if-else statements.

### 3.6.6 Implementing Conditional Branches with Conditional Moves

Conditional branching is an expensive endeavor in modern processors due to the
nature of predictive instruction execution. C control flow statements are all
implemented using essentially `GOTO` statements to different sections of code.

Another strategy is to use conditional transfer of data. Values are computed and
moved conditionally according to value of condition. This can involve computing
as many as there are paths and using the correct one. This is done with the
`CMOVGE` instruction, sometimes.

Other times data transfer is not feasible due to predictive nature of modern
processors. Instructions are queued up and executed in batches whatever possible,
speeding them up. This is only possible with linear control flow. With branching
control flow, the path to take is not known until the condition is known. So
sometimes one branch is queued up, and then the condition is known, and an entire
batch must be thrown out since it does not match the condition code.

In short, not all conditional expressions be made into conditional moves

### 3.6.7 Loops

While, for and do loops from C are implemented using conditional jumps and tests.

Do while loops are loops where the body is executed at least once and the tail
determines if the body is executed again. This if done with a conditional jump
in assembly at the end of the body following a test expression.

In reverse engineering it can be possible in certain instances to easily identify
loops the assembly by looking for easily identifiable markers of conditional jumps
and tests.

While loops are similarly to do-while except before executing the body
expression, the there is an unconditional jump to test expression and then a conditional
jump to the body. This is a 'jump to Middle' translation of a while loop.

Another strategy for implementing loops with the 'Guarded Do' in which a test is
done before executing the body, it is fails then a jump is done to past the related
loop code and into new code that follows.

Both strategies can be used to implement for loops

### 3.6.8 Switch Statements

Switch statements are the most powerful statement in C which allows for efficient
multipath branching. This is done using a branch table, which is an array holding
addresses to code that is to be executed based on certain conditions. In order
to determine execution, first and index to the jump table must be calculated and
then the address of the next instructions to be executed are retrieved and execution
begins. This is
more efficient than chained if-else statements.

This allows for a very nice O(1) time complexity of determining the code branching.

GCC also provides extensions that allow for creation of code and function pointer
and arbitrary jumping.

## 3.7 Procedures

A procedure is a set of computations or instructions that are to be used repeatedly
in code with guarantees that it will always repeat the same set of steps. When a
procedure is called the `program counter` will be updated with the address of
the procedure that is being currently executed. Data also has to flow from the
caller to the callee in the form of specially prepared register values and
also return values from the procedure in the form of a register.

x86_64 assembly contains instructions for calling procedures and returning from
procedure calls

### 3.7.1 The Runtime Stack

When a procedure is called, the program counter is updated and the memory required
for a procedure to do its computations is allocated on the stack. Such data can be
stored in the registers or in memory.

A stack counter is a pointer to the stack memory. When a procedure is called, the
pointer the higher end of the address space. In order to allocate memory for a new
procedure's call stack the pointer is decremented to the correct amount. Upon
terminating the pointer is again incremented to previous value.

The memory allocated for a procedure's local variable is known as a `stack frame`.

Allocating space on the stack is only required if the amount of space to hold the
values is more than what the registers can hold. `Lead procedures` are those that
only required the space provided by registers.

When a procedure is about to be called, by another procedure, the caller most
have previously allocated sufficient space on its stack in order to store all
the arguments that are going to be passed to the callee.

### 3.7.2 Control Transfer

When a procedure is called, the stack allocated for it must contain the return
address on where to resume execution. The `CALL` instruction is used to do this
in assembling with the label of the procedure being called. The linker is responsible
for finding the address of procedure being called. The `RET` will reverse it and
update the stack pointer and resume instructions at the correct location in
memory.

### 3.7.3 Data Transfer

When calling procedures there must exist methods for passing data to and from
procedure being called. This is done via placing the correct arguments in the correct
registers and location in stack memory. The registers allow for 16 different machine
words to be passed to procedure and if that is not enough then arguments
are passed inside the memory build area.

In order for a procedure to make the correct computation the correct arguments
must be placed in the correct locations.

### 3.7.4 Local Storage on the Stack

Memory space is required for when the 16 registers are enough to represent the
required data such as

- more than 6 machine word sized variables
- addresses of values are required
- more complicated data structures are used

Space is allocated on the stack to represent these values on the stack.

### 3.7.5 Local Storage in Registers

Registers are a shards common resource in which different registers must be
able to use. Data integrity is important, so a set of conventions must be followed
so that data is not corrupted when calling and returning from procedures

- RBX, RBP, R12-R15 are callee saved registers, their values must be preserved
  or restored when a procedure terminates execution
- RSP is the stack pointer registers and must be maintained when calling and
  returning from procedures
- all other registers are caller saved registers, which means they can be modified
  and overwritten as please in order to do computations

### 3.7.6 Recursive Procedures

If such convention is upheld, then recursive procedures are possible, this
can early be achieved with a compiler for a high level language and proper
adhesion to the conventions.

The values at registers are properly maintained, and stack space can always
be allocated again for a procedure to call itself.

## 3.7 Array Allocation and Access

Arrays are continuous regions of memory in which a homogenous set of data is stored
and represented. Individual elements can be accessed using and index which can then
be used to calculate the address of using pointer arithmetic.

### 3.8.1 Basic Principles

When an array is instantiated, memory space must be allocated in sufficient
room for elements that are to be stored. This can be done in the allocation of
stack or explicitly with heap memory. Unique element addresses are to be calculated
using the start address, the size of each element and alignment, and the index of
element that is to be read.

### 3.8.2 Pointer Arithmetic

To dereference a pointer can mean to copy its values to registers or to write to
the memory specified by a pointer. Pointer arithmetic is using in order to manage
pointer to elements in the arrays.

### 3.8.3 Nested Arrays

In C99 it is possible to define arrays of arrays, multidimensional vectors or matrices.

```c
// declare array with 5 elements, each element is an array of 3 integers
int a[3][5];
```

The address of the individual elements can be calculated by taking the size of
each element, whether it is an integer or an array of 3 integers and multiplying
by the relevant index plus the starting position of the entire thing and boom.

### 3.8.4 Fixed Sized Arrays

The compiler is capable of generating optimizations for fixed sized arrays.
This is done by recognizing common patterns and then replacing those
patterns with more optimized things.

When working with arrays in assembly it can be helpful to set marker variables
keep track of where on the array the control flow is currently focusing on.

### 3.8.5 Variable Sized Arrays

C code can either allocate sufficient memory for an array on the stack or on
the heap. Stack memory is allocated on procedure startup and is sufficient to
fold the values of variables that the programmer declares. Heap allocated stuff
are memory that a program and request from OS if stack memory is not enough or
memory required can only be known at runtime.

Some calls to `malloc` can be optimized if the value passed to the function are
constant values known at compile time. It is all about patterns that the compiler
can be programmed to recognize.

## 3.9 Heterogeneous Data Structures

C allows for different data types to express different groupings of data in a struct.
However, a union allows for a set region of memory to be *interpreted* in the set
manner of different ways, IE a block of memory can be both a float, an int and
a set of for bits.

```c
typedef union {
  int32_t integer;
  float floating_point;
  struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
  };
} UnsafeUnion;
```

### 3.1.1 Structures

Grouping data into logical groupings that can be referenced by name and address offset
is an ability that allows for complex operations to be more easily expressed.
Access to individual members of a structure can be done the same way as an array,
the compiler calculates the size of the structure and generate offsets for accessing
the different parts of the structure. If arrays are embedded inside a structure
the whole array is a part of the structure.

C allows for embedding pointers, arrays and other structures inside one structure.
Recursive data structures can only be achieved with pointers.

### 3.9.2 Unions

Unions allow for a single block of memory to be interpreted in different ways and
split into different sections.

Size of union will always be the same as the largest member of union. This is to
ensure that the memory block is large enough to represent all the members.

Great care must be taken if we are to use this to store numbers, as thing such
endianness can matter when running and compiling code for different platforms.
Byte and bit ordering can matter in such circumstance unless we are explicitly
not using the bytes as integers, floats and such.

### 3.9.3 Data Alignment

Alignment restriction refer to the performance requirement of structures and data
to fit in memory blocks that are multiples of 8 bytes. This is done in order to allow
easy access of byte blocks in memory. Each address point to a specific byte of memory
however it is more efficient for an entire machine word to be copied over from memory
and then used.

Using a none multiple address would require multiple assembly instructions with
the machine word retrieval and then bit manipulation in coax desire value out of
the machine word is an inefficient method of retrieving data.

A general rule of thumb is that objects of size K bytes must be stored in addresses
that are themselves multiples of K.

Alignment is enforced at compile time with the correct memory management allocations
and alignment directives. As such some structures may include a gap of useless memory
embedded inside the structure. For performance reasons, a compiler will waste memory
as opposed to be unaligned.

## 3.10 Combining Control and Data in Machine Level Programs

This chapter relates to the implementation of the C language construct of the pointer.
It examines what constitutes a buffer overflow and a few mitigations.

### 3.10.1 Understanding Pointers

Pointers point to specific bytes in memory locations. Can index arrays, structures
and elementary types. A void pointer type is a raw memory address that can point
to anything and the compiler will not complain about it. Even a zero address,
more known as the null pointer. Casting pointer types will not change the underlying
value.

Pointers to functions can be generated and used to call said functions.

### 3.10.2 Life In the Real World: Using GDB Debugger

GDB debugger allows for looking at program state as it executes. It can set and
stop execution at breakpoints. Inspect the values of variables, show values at
addresses, and change variable values. CLI and GUI version are available.

The book contains a table detailing the different commands and how to use them in
detail.

### 3.10.3 Out of Bound Memory References and Buffer Overflow

The C language specification does not include bounds checking and so C implementation
can have this. It is undefined behaviour. Buffer overflow occurs when data is written
to array or buffer past the point of where the memory is allocated to buffer. Going
over the bounds may overwrite other variables or important stack data. Such problems
can only be identified by looking at the compiled instructions directly.

The main malicious use of buffer flow is injection of malicious arbitrary instructions
to be executed. The only thing needed is the correct return address.

### 3.10.4 Twarting Buffer Overflow Attacks

Compiles and operating systems have devised methods for mitigating buffer overflow
overflow attacks. Several techniques are created to mitigate buffer overflow.

While they do not complete prevent buffer overflow attack they do a good job at
mitigating them.

#### Stack Randomization

Injection of code requires knowing the return address, location of different stack
variables, and structure.
Stack randomization We add padding to the start, end, and in-between stack
variables. Not enough to waste space but enough to make it difficult to calculate
the stack locations, and it needs to be random each time the program starts and executes.

This is a form of `Address Space Layout Randomization` which is a list of techniques
that twart arbitary code execution via moving different regions of memory around each
time the program executes.

This can be countered by adding `noop` instructions and guessing the correct location
of memory this way, but is is brute force.

#### Stack Corruption detection

Another method is adding a canary value, at the end of each buffer in memory. If
this value is writen over, at the end of the function termination the value is checked.
If the value is changed then it terminates execution of program since the value is
no longer the correct value.

Modern compilers do this automatically.

#### Limiting Executable Code Regions

Another method is to restrict permission of memory regions: write, read and execute.
Setting bit flags for memory regions prevents CPU from interpreting certain memory
regions as code instructions.

Certain JIT compilers must manipulate these bit flags in order to execute generated
code.

`Memory Protection` is forms of access by and for userland programs and kernel
processes.

### 3.10.4 Supporting Variable Stack Frames

Some functions can use and support a variable stack size. When compiler cannot determine
size of stack space on compile time, it requires referance to address of variables

### 3.10.4 Supporting Variable Stack Frames

Some functions can use and support a variable stack size. When compiler cannot determine
size of stack space on compile time, it requires referance to address of variables.

`Frame Pointer` is generally stored in `%rbp`, all local variable address are stored
as ofssets from this address.

`x86` always uses a frame pointer. `x86_64` only uses it for variable size stack
variables. GCC can mix both concept.

## 3.11 Floating Point Code

Floating point architecture refers to how CPU design and operations stores and
processes floating point numbers. Most of the time they deal with IEEE standards
for 32-bit and 64-bit floating point numbers. Functions can include,

- storage and access
- register use and practices
- function argument conventions

Floating point numbers are usually stored in dedicated registers speciallized for
floating point numbers with seperate instructions to peform movement, comparison
and arithmetic.

SIMD: Single instruction Multiple DAta instructrions allow for efficient procesing
of large chunks of data. Easy to chew to arithmetic operations on large swafts of
data.

AVX: Advanced Vertor Instructions. Allows for efficient CPU extensions to be used
in order to deal with large operations.

### 3.11.1 Floating Point Movement and Conversion Operations

XMM registers are responsible for holding floating point data. Byte alignment
is not strictly required but neccesary for optimization. Scalar movement instructions
are used only for transporting between memory and  registers. Data is guranteed
to be aligned when method is used.

Intructions that can convert between representation levels are also available.
Interleaving instructions also available for converting between Floating point
standards.

### 3.11.2 Floating Point Code in Procedures

XMM registers can store and return floating point values from functions. A maximum
of 8 arguments can be passed via registers with the rest to be passed using stack
memory space. By default they are caller saved, but callee can overwrite the data.

### 3.11.3 Floating Point Arithmetic Operations

Unique instruction are used to implement simple arithmetic, with variations of
these instructions available for single and double precision data.

### 3.11.4 Defining and Using Floating Point Constants

Intermediate values in floating point calculations require seperate memory allocation
in the stack by the compiler. It must decide a place to store the value and use
it when neccesary by the program.

### 3.11.5 Using Bitwise Operations on Floating Point Code

Bitwise operations act on XMM registers the same way as other registers, accross
the entire register. They can also taget low order bytes to act upon with speciallized
instructions.

### 3.11.6 Floating Point Comparison Operations

Comparison instructions exist for single and double precision floating point numbers.
For all of them, the second argument must be inside an XMM register. Parity flag
bit is set when NaN is the result of a floating point arithmetic operation. C defines
a NaN result as a failure and it can be detected. NaN values can be checked for
by trying all comparison methods, all would yield false.

### 3.11.7 Observations on Floating Point Code

Collection of registers for holding and operating on datas. There are more complexities
than when dealing with integer data. C extensions exist in GCC that allow for easy
parallizationg of processing scalar code.

## 3.12 Summary

A compiler may generate assembly from high level language. Looking into chapter
12 will show how to locate data for different purposes. There is a minimal distinction
between data types in assembly. Gaps in C spec can generate correct C code but generate
error-prone assembly code.
One way to deal with problems of working with machine code is to generate bytecode
for a virtual machine.
