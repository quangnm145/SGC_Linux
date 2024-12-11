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
  ls -ls sparse_file
  ```

- Use `du` to check the actual physical size of a file:
  ```bash
  du -h sparse_file
  ```

---

### Creating Sparse Files ###

1. **Using `truncate`:**
   - Create a file with a large logical size without writing data:
     ```bash
     truncate -s 1G sparse_file
     ```

2. **Using `dd` with lseek:**
   - Write a portion of data into a large file:
     ```bash
     dd if=/dev/zero of=sparse_file bs=1 count=0 seek=1G
     ```