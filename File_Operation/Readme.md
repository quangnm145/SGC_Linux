# Linux Day 3 #

## File with holes (Sparse files) ##

### Regular File ###

When a file is created, a name referencing an inode is also created. This inode stores attributes such as:

- File size
- Permissions
- Time (last modified, last accessed, etc.)
- File ownership
- Type

You can use commands like `ls` or `stat` to check these details.

The inode contains pointers to data blocks in the system (data is stored block by block). Data is only synchronized to physical memory when using `sync()` or `fsync()`.

---

### Sparse File ###

A sparse file has a large logical size but occupies less physical storage.

#### Benefits of Sparse File ####

1. **Storage Efficiency:**
   - Only stores the portions of data that are actually used.

2. **Higher Performance:**
   - Reduces the overhead of writing unnecessary data to the disk.

3. **Applications:**
   - Used in virtual file systems, disk images, databases, and backups.

---

### Sparse File Handling ###

#### Tools and Functions ####

1. **lseek()**
   - Moves the file pointer to a desired position without writing data.
   - Example:
     ```c
     off_t lseek(int fd, off_t offset, int whence);
     ```
     Here, `fd` is the file descriptor, `offset` is the desired position, and `whence` specifies how to calculate the position (e.g., `SEEK_SET`, `SEEK_CUR`, `SEEK_END`).

2. **fallocate()**
   - Allocates space for a file without writing actual data.
   - Example:
     ```c
     int fallocate(int fd, int mode, off_t offset, off_t len);
     ```
     This function allows faster and more efficient allocation compared to manual writes.

---

### Checking Sparse Files ###

- Use `ls -ls` to check the logical and physical size of a file:
  - The first column (blocks): number of physical blocks used.
  - The second column (size): logical size of the file.

- Example:
  ```bash
  ls -ls sourc_file
  ```

- Use `du` to check the actual physical size of a file:
  ```bash
  du -h sourc_file
  ```

---

### Creating Sparse Files ###

1. **Using `truncate`:**
   - Create a file with a large logical size without writing data:
     ```bash
     truncate -s 1M sourc_file
     ```

---

## Task ##
Write a program like cp that, when used to copy a regular file that contains holes (sequences of null bytes), also creates corresponding holes in the target file. 

### Steps:

#### 1. Create a new C file:
  - Open a terminal and navigate to main project directory.
  - Create a new file called `ex1.c`:
    ```bash
    touch ex1.c
    ```
  - Open the file in the `nano` text editor:
    ```bash
    nano ex1.c
    ```
#### 2. Write the program:
  - In the `nano` editor, write the C code.
  - Using `main()` function with arguments.
  - Open source file with argument index 1 and destination file with index 2.
  - Read each byte of the source file in turn and write to the destination file. If a hole is encountered, increase the hole number by 1. Until a different value is encountered, the hole will move the pointer position in the file and add the hole value by using `lseek()` to shift hole value from current position.
    ```bash
    lseek(output_fd, holes, SEEK_CUR);
    ```
  - Save the file by pressing `Ctrl + O` and then hit `Enter` to confirm.
  - Exit the editor by pressing `Ctrl + X`.
  ![Nano](./src/Day1_Task1_Nano.png)

#### 3. Compile the Program with `gcc`:
  - Compile your C program using the `gcc` compiler:
    ```bash
    gcc ex1.c -o ex1
    ```
  - This will create an executable file named `ex1`.

#### 4. Run the Program:
  - Run the compiled program using the following command:
    ```bash
    ./ex1 sourc_file dest_file
    ```
