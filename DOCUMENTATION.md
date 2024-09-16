![SafeHeap Emblem](https://github.com/mikhailuwu/safeheap/blob/latest/doc/safeheap.png?raw=true)

![Static Badge](https://img.shields.io/badge/License-GPL--3.0-yellow)
![Static Badge](https://img.shields.io/badge/Language-ISO/POSIX_C-blue)
![Static Badge](https://img.shields.io/badge/Status-Not--ready-red)


# Safeheap documentation

> [!Warning]
> Software released under the GNU General Publishing License (GPL) 3.0. I cannot be held liable for any damages from using/distributing/modifying this software.

This [readme file](DOCUMENTATION.md) provides extensive documentation to the use of [this library](https://github.com/mikhailuwu/safeheap) for user developers.

> [!Note]
> If you do have any sections in need of correction by editor then please create an [issue](https://github.com/mikhailuwu/safeheap/issues) with the label <span style="color:lightblue;">documentation</span>.

## Contents

1. Purpose
2. Terminology
3. Protection
    <br>3.1 Protection grades
    <br>3.1 Segmentation
    <br>3.2 Encryption
    <br>3.3 Erasure
    <br>3.4 Randomization
4. External

## 2. Terminology

If a function or data type is a part of the <span style="color:orange;">user interface</span> then they are denoted as <span style="color:orange;">[+UI]</span>.

## 3. Protection
The safeheap library provides a framework of protection implementations to secure user memory. The library does not operate on a kernel level, but instead employs various protection techniques to secure heap memory data.

Such techniques can be divided into four categories:

- Segmentation
- Encryption
- Erasure
- Randomization

### 3.1 Protection grades
On heap allocation request through an user interface function provided by the safeheap library, the user may specify a protection grade which specifies to the sub-systems how to handle the protected data (see figure 1).

| Grade     | Segmentation | Encryption | Erasure | ASLR | SC Noise |
|-----------|--------------|------------|---------|------|----------|
| <span style="color:green">HIGH</span>      | <span style="color:green;">Yes</span>          | <span style="color:green;">Yes</span>        | <span style="color:green;">Yes</span>     | <span style="color:green;">Yes</span>  | <span style="color:green;">Yes</span>      |
| <span style="color:orange">MED</span>    | <span style="color:green;">Yes</span>          | <span style="color:green;">Yes</span>        | <span style="color:green;">Yes</span>     | No   | No       |
| <span style="color:red">LOW</span>       | <span style="color:green;">Yes</span>          | No         | <span style="color:green;">Yes</span>     | No   | No       |
| <span style="color:red">NONE</span>      | No           | No         | <span style="color:green;">Yes</span>     | No   | No       |

**Figure 2:** Protection specifiers

> [!Warning]
> If you expect protection of passwords and sensitive information then it is recommended to use protection MEDIUM to HIGH and not LOW or NONE due to lacking encryption.

Encryption is only enabled from MEDIUM through HIGH but the cipher algorithm and modes vary (see figure 2).

| Grade  | Algorithm  | Mode |
|--------|------------|------|
| <span style="color:red">HIGH</span>   | AES256     | GCM  |
| <span style="color:orange">MEDIUM</span> | AES192     | GCM  |

**Figure 2:** Algorithms and modes according to protection specifier

### 3.2 Segmentation
If user specifies they want a heap variable to be *segmented*, then on request through [sh_malloc](###sh_malloc), the variable will be divided into chunks or *segments* spread across the heap. The subsystems handle the read/write/*alloc automatically for the user.

### 3.3 Encryption
If specified, the protected memory may also be encrypted with various ciphers. This is handled by the internal subsystems in read/write operations and requires no user (programmatic) oversight.

### 3.4 Erasure
On request or if no longer needed, a variable's data may be wiped by overwriting the bits with random bits a certain amounts of times depending on the storage medium. For example, if stored in volatile memory then the system will only perform one overwrite, but if stored on a swap device such as a hard drive then multiple cycles of overwriting will be performed on said memory to ensure it may no longer be forensically recoverable.

### 3.5 Randomization
Another memory vulnerability, rare but possible, are side-channel attacks. These are attacks using available information from *side-channels* such as page files, power usage, sound made by the hardware, etc. This information is then used to do a statistical attack to analyze and understand how the data is handled.

To deter and prevent these attacks, side-channel noise may be generated if specified by user.
