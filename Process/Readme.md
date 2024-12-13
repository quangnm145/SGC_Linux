# Process

## Processes and Programs

- A **program** is a file containing a range of information that describes how to construct a process at runtime.
- A **process** is an instance of an executing program and is managed by the kernel.

### Relationship Between Programs and Processes

- A single program can spawn multiple processes.
- Processes share the same program code but maintain separate execution states and resources.

## Process ID and Parent Process ID

- Each process has a process ID (**PID**), a positive integer that uniquely identifies the process on the system.
- The `getpid()` system call returns the process ID of the calling process.
- The Linux kernel limits process IDs to being less than or equal to 32,767. When the PID counter reaches 32,767, it is reset to 300 instead of starting back at 1. Low-numbered PIDs (1–299) are often reserved for system processes and daemons that run continuously. These include critical components of the operating system, such as the init system (PID 1).
- This limit is adjustable via the value in the Linux-specific `/proc/sys/kernel/pid_max` file (which is one greater than the maximum process ID) and depends on whether the system is 32-bit or 64-bit.
- Each process has a parent—the process that created it. A process can find out the process ID of its parent using the `getppid()` system call.
- In effect, the parent process ID attribute of each process represents the tree-like relationship of all processes on the system. The parent of each process has its own parent, and so on, going all the way back to process 1, `init`, the ancestor of all processes. (This “family tree” can be viewed using the `pstree` command.)
- If a child process becomes orphaned because its “birth” parent terminates, then the child is adopted by the init process, and subsequent calls to `getppid()` in the child return 1.
- The parent of any process can be found by looking at the `Ppid` field provided in the Linux-specific `/proc/PID/status` file.

## Memory Layout of a Process

The memory allocated to each process is composed of a number of parts, usually referred to as **segments**:

1. **Text segment**
2. **Initialized data segment**
3. **Uninitialized data segment**
4. **Stack**
5. **Heap**

## Virtual Memory Management

Virtual memory solves three main problems:

1. **Not Enough Memory**
2. **Memory Fragmentation**
3. **Security**

### Key Idea

- The main idea is that not all parts of a program's address space need to be maintained in RAM simultaneously.
- At any given time, only a small portion of a program’s data or instructions are typically accessed, so only that portion needs to be kept in RAM.
- Each program is provided with its own private, non-overlapping address space called **virtual memory**.
- The virtual memory of each program is mapped into physical memory. This mapping is unique for each program.

### Pages

- **Pages:** The program’s address space is divided into fixed-size units called pages.
- **Page frames in RAM:** Physical memory (RAM) is divided into page frames corresponding to the size of pages.
- **Resident set:** Only the necessary pages of a program are kept in RAM at any given time, forming the **resident set**.
- **Swap space:** Pages not currently in use are stored in swap space (disk) and loaded into RAM only when needed.

### Handling Page Faults

- A **page fault** occurs when a program accesses a page that is not in RAM.
- The kernel pauses the program's execution and loads the required page from disk into RAM.
- This process is time-consuming as disk access is much slower than RAM access.
- On x86-32 architectures, page size is 4096 bytes (4 KB). Other architectures may have different page sizes, e.g., Alpha: 8192 bytes (8 KB), IA-64: 16,384 bytes (16 KB). Programs can use `sysconf(_SC_PAGESIZE)` to check the system’s current page size.

## The Stack and Stack Frames

- The **stack** is used for managing function calls and their local variables.
- Each function call creates a **stack frame**, which contains information such as return addresses and local variables.
- The stack grows and shrinks dynamically as functions are called and return.

## Command-line Arguments

- Command-line arguments allow users to pass data to programs at runtime.
- In C programs, the `main()` function accepts two arguments:
  - `int argc`: The number of command-line arguments.
  - `char *argv[]`: An array of strings representing the arguments.
- Example:
  ```c
  int main(int argc, char *argv[]) {
      for (int i = 0; i < argc; i++) {
          printf("Argument %d: %s\n", i, argv[i]);
      }
      return 0;
  }
  ```

## Environment List

- The **environment list** is a collection of environment variables available to a program.
- These variables are strings in the format `KEY=VALUE`.
- The `main()` function can access the environment list via the `char *envp[]` parameter.
- Example:
  ```c
  int main(int argc, char *argv[], char *envp[]) {
      for (char **env = envp; *env != NULL; env++) {
          printf("%s\n", *env);
      }
      return 0;
  }
  ```

## Accessing and Modifying Environment Variables

### Accessing Environment Variables

- The `getenv()` function is used to retrieve the value of an environment variable by name.
- Example:
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main() {
      char *path = getenv("PATH");
      if (path != NULL) {
          printf("PATH: %s\n", path);
      } else {
          printf("PATH variable is not set.\n");
      }
      return 0;
  }
  ```

### Modifying Environment Variables

- The `setenv()` and `unsetenv()` functions are used to add, update, or remove environment variables.
- Example of setting an environment variable:
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main() {
      if (setenv("MY_VAR", "HelloWorld", 1) == 0) {
          printf("MY_VAR set to: %s\n", getenv("MY_VAR"));
      } else {
          perror("setenv");
      }
      return 0;
  }
  ```
- Example of unsetting an environment variable:
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main() {
      if (unsetenv("MY_VAR") == 0) {
          printf("MY_VAR removed.\n");
      } else {
          perror("unsetenv");
      }
      return 0;
  }
  ```

