# A Tour of Computer Systems

A computer system composts of hardware and software working together to do useful
work for humans. We will be learning how exactly software interacts with hardware
using the C programming language. I will be following this book as closely as I
can without getting too bored.

## Information is Bits

All programs begin life as a source file. And all source files are bits.
Compilation is simply converting this set of bits from one format to another. From
the bits representing text to the bits representing data and instructions for the
computer to follow.

There can only be so many numbers that can be represented using bits, since
bits are inherently a discrete form of values. Not knowing how this works will
hamper programmer's ability to write the best programs.

## Programs are Translated by Other Programs into Different Forms

C compiler works in several stages.

1. Preprocessor: turns all header and source files into one massive file. Uses
  directives to copy and paste code
2. Compiler: parses source file and translate into assembly.
3. Assembler: translate assembly code into object files.
4. Linker: resolves and find function pointers and produces final executable

## Reasons to Understand Compilation

- easy program optimization: best take advantage compiler optimizations to increase
  performance
- understanding link time errors: resolve errors related to different declarations
  and definitions of objects and functions
- understanding security errors:

## Processors Read and Interpret Instructions

The only real interpreters are CPU since they fetch instructions from memory and
execute them in order.

A shell is a command-line interpreter that executes commands and returns output
in the standard out. It can also execute programs.

## Hardware Organization

- Buses: electrical connections between system components. Can carry bits one word
  at a time. But very fast
- I/O: connects to external world, keyboard, mouse, display, speaker.  CPU communicates
  with I/O using controller and adapters
- Main Memory: Where most data used by CPU is stored. In theory everything here
  can be accessed at any point. System calls are required to look into data store
  in dark disk
- Processor: main engine that executes instructions and fetches data from memory,
  IO and hard disk. Works according its *instruction architecture*.
  Has 4 basic instructions
  - Load: copy word from main memory into register
  - Store: copy word from register into memory
  - operate: transfer data to ALU and perform operation, overwrite register with
      results
  - jump: extract word from instruction and copy into program counter

### Running *hello_world* Program

Program binary is copied into memory and then loaded into registers. And then CPU
executes the instructions stored in program.

## Caches Matter

Information can be stored temporary in faster form of memory called cached in CPU
in to more quickly access it, especially if such data is accessed frequently. Data
is almost always stored in the hard disk first. And then this data is moved to the
main memory. Main memory is always better the hard storage simply because larger
memory devices are slower than smaller one due to physics. This difference increase
exponentially in some cases.

Registers are only capable of storing a couple of hundred bytes but are so much
faster than main memory.

**Static Random Access Memory** is the name given to caches

For programmers this copying of data slows down the real work of program and to
make it faster, solutions need to be found.

## Storage Devices Form a Hierarchy

The concept to understand is that data can be stored in different storage mediums
before it is sent to CPU. There is an order in which specific data is searched for
to fastest to slowest

1. Registers
2. L1 Cache
3. L2 Cache
4. L3 Cache
5. Main Memory(RAM)
6. Local disk
7. External network devices, distributed file systems

## Operating System Manages the Hardware

The kernel is what's interfaces between the shell and the hardware in Linux. Sometimes
device driver act as the translation between hardware and kernel, but this is the
model right now.

But the operating system as a whole is the main abstraction that allows the user
or rather user programs to interface with the hardware to do what the user tells
it to do.

By my own definition an operating system is a system, or a collection programs that
allow user to execute commands and complete tasks.

The big idea with computer systems is that generally they are layers of abstraction
upon abstraction.

An instruction set is an abstraction over true machine code, which is binary. Process
are abstractions over processors' execution, main memory, and I/O devices working
in conjunction to execute instructions. Operating systems are abstractions of all
of this to present a workable interface for humans.

Some operating systems include

- Windows Family: 98, 96, XP, Vista, 7, 8, 10, 11
- Linux: GNU + Linux distributions, Clear Linux, Alpine Linux, Busy Box
- Temple OS
- macOS
- BSD Unix Implementation
- Original Unix
- POSIX Compliant Systems
- many more

### Processes

Whenever a program runs on an operating system, the OS gives it the illusion that
is the only program running on the system and that it gets a monopoly on all resources.
That cannot truly be the case, but it is done for security and convenience. Memory
is allocated specifically for exclusive use by the program and if it needs more
it must request from the operating system via a system call.

All process are run *concurrently*, which means they all get equal and shared access
to CPU time in order for their own individual instructions to be executed. This
is done since most of the time, there are more programs/threads to run than there
are cores.

CPUs solve part of this problem via hyper-threading, where one core acts as multiple
cores, generally 2 cores. This is called *context switching* in which CPUs switch
from running one process to another. There is a constant switching between user
code and kernel code. Everything is managed by the kernel.

### Threads

Threads run in the context of a singer process. Threads allow a process to have
multiple execution units. This is done since sharing data between threads is easier
than sharing between processes.

### Virtual Memory

This is an abstraction provided by the operating system of real physical memory.
Regions of real memory is reallocated for used by the process, and it is only allowed
to view that specific block of memory as if it where the entire amount of memory
that the operating system has. This virtual memory contains some important data
such as

- Stack
  - program code/instructions
  - program variables
- heap: dynamically allocated memory for when we do not know the size of the relevant
  data at compile time.
- Shared libraries: address space where shared libraries pretend to live in virtual
  memory
- stack: implements function calls and their data
- kernel virtual memory: reserved for use by kernel

In order for virtual memory to work, there needs to be coordination between the
hardware and operating system, where each virtual memory address corresponds to
a real hardware memory address.

### Files

Files are nothing more than an organized sequence of bytes. They have a defined
sized and encoding. In Unix based operating systems all I/O devices are represented
as files. The kernel is what provides systems call that allow for them to be used.
This abstraction allows it to be easy to write code for a variety of different I/O
devices

### Communication over Networks

More often than not, computers are connected to a network. A network is generally
just another I/O device. In Linux, the driver for specific network device resides
in the kernel, but application use the system calls provided by the kernel in order
to communicate information.

Networks allow for computers to send data to other computers and receive data. This
is does use common protocols just as IP, TCP, UDP, and Ethernet.

Data that can be sent over a network is limited only by the speed, throughput and
reliability of the connection.

## Important Themes

A computer is a system, it contains operating system, hardware systems and networks.
It is important for programmer to take the inner workings of a computer in mind
when developing software.

### Amdahl's Law

The idea is that in order to improve the overall performance of a system by certain
threshold, then a specific part would have to be improved by greater percentage
as described by formula.

$$
T_{new} = ( 1 - \alpha )T_{old} + (\alpha * T_{old}) / k
= T_{old} [(1 - \alpha) + \alpha / k]
$$

Here the value *a* denotes the significance of the smaller component in the system.
And *k* denotes the thing.
The amount that the smaller component would have be improved by is,

$$
S = \frac{1}{(1-\alpha) + \alpha/k}
$$

#### Example: Truck Driver

Carry Load A to B distance 2500 km, average 100 kmph

- speed limit abolishment

$$
a = 0.6
$$

$$
k = 1.5
$$

$$
S = \frac{1}{(1-0.6)+\frac{0.06}{1.5}} = 1.25
$$

- figure out the speed

```text
167 = 1 / ((1-a) + (a / k))
167 = 1 / ((1-0.6) + (0.6 / k))
1/167 = 0.4 + (0.6)/k
329/835 = 0.6/k
k = 1.5
```

#### Practice Problem: Car Manufacturer

$$
a = 0.90
k = ?
S = 4
$$

How much improvement to reach target S?

```text
4 = 1 / ((1 - a) + (a/k))
4((1 - a) + (a/k)) = 1
((1 - a) + (a/k)) = 1/4
0.1 + (0.1)/k = 1/4
0.1/k = 0.15
0.666666 = 1/k
1.5 = k

```

### Concurrency and Parallelism

It is a proven fact that a computer is capable of doing more things if is allowed
to do more than one thing at a time. `Concurrency` is the act of having CPU
wait out a process in order to given CPU time to another process and given the
illusion that both are running at the same time. `Parallelism` is use concurrency
in order to make system faster.

Early versions of concurrency was single threaded and as such CPU had to bounce
back and forth between different processes. Now modern computer have real multiple
cores where tasks are executed at the same time.

`Hyperthreading` is technology that allows a single CPU core to act upon multiple
flow controls on a per-cycle basis. This takes advantage of waiting times when fetching
data and advance on another process. It allows execution of many applications
or one powerful application at once.

`Instruction Level Parallelism` allows processor to execute multiple instructions
at the same time. Sometimes from 2 to 10 instructions are executed when spread out
across the CPU hardware.

`SIMD` stands for single instruction Multiple data Parallelism. This technology
allows for Instruction Level Parallelism. This allows for 8 pairs of floats to
be added at once, for example.

### Importance of Abstraction in Modern Computer Systems

Abstractions are important because it allows for formulation of a single solution
to a problem to be applied over and over without worrying about correctness to
other problems to solve.

The way abstractions are applied varies between different programming languages.
Such as Java classes and C function prototypes. Instruction set allow for abstraction
over actual hardware binary. Files are an abstraction over I/O, virtual memory is
an abstraction for real memory.

## Summary

Computer Systems are composed of hardware and systems software the work together
to execute user programs.
\pagebreak
