# Machine Level Representation of programs

We see a review on what computrerts do. Computer work by executing machine code
instructions and applying them on data. Machine code is data and a is generated
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
