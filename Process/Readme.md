# Process #

## Procecsses and Programs ##
- A `program` is a file containing a range of information that describes how to con-struct a process at run time.
- A `process` is an instance of an executing program and managed by kernel.

- Relationship Between Programs and Processes
    - A single program can spawn multiple processes.
    - Processes share the same program code but maintain separate execution states and resources.

## Process ID and Parent Process ID ##
- Each process has a process ID (`PID`), a positive integer that uniquely identifies the process on the system.
- The `getpid()` system call returns the process ID of the calling process.
- The Linux kernel limits process IDs to being less than or equal to 32,767. When the PID counter reaches 32,767, it is reset to 300 instead of starting back at 1. Low-numbered PIDs (1–299) are often reserved for system processes and daemons that run continuously. These include critical components of the operating system, such as the init system (PID 1).
- This limit is adjustable via the value in the Linux-specific `/proc/sys/kernel/pid_max` file (which is one greater than the maximum process ID). (Depend on 32-bits or 64-bits).
- Each process has a parent—the process that created it. A process can find out the process ID of its parent using the `getppid()` system call.
- In effect, the parent process ID attribute of each process represents the tree-like relationship of all processes on the system. The parent of each process has its own parent, and so on, going all the way back to process 1, init, the ancestor of all pro-cesses. (This “family tree” can be viewed using the pstree(1) command.)
- If a child process becomes orphaned because its “birth” parent terminates, then the child is adopted by the init process, and subsequent calls to getppid() in the child return 1 (see Section 26.2).
- The parent of any process can be found by looking at the Ppid field provided in the Linux-specific /proc/PID/status file.

## Memory Layout of Process ##
- The memory allocated to each process is composed of a number of parts, usually referred to as segments:
    1. Text segment
    2. Initialized data segment
    3. Uninitialized data segment
    4. Stack
    5. Heap

## Virtual Memory Managemet ##

## The Stack and Stack Frames ##

## Command-line Arguments ##

## Environment List ##


