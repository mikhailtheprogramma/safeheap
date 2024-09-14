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
| HIGH      | <span style="color:green;">Yes</span>          | <span style="color:green;">Yes</span>        | <span style="color:green;">Yes</span>     | <span style="color:green;">Yes</span>  | <span style="color:green;">Yes</span>      |
|-----------|--------------|------------|---------|------|----------|
| MEDIUM    | <span style="color:green;">Yes</span>          | <span style="color:green;">Yes</span>        | <span style="color:green;">Yes</span>     | No   | No       |
|-----------|--------------|------------|---------|------|----------|
| LOW       | <span style="color:green;">Yes</span>          | No         | <span style="color:green;">Yes</span>     | No   | No       |
|-----------|--------------|------------|---------|------|----------|
| NONE      | No           | No         | <span style="color:green;">Yes</span>     | No   | No       |

Encryption is only enabled from MEDIUM through HIGH but the cipher algorithm and modes vary (see figure below u stupid goober).

| High   | Algorithm  | Mode |
|--------|------------|------|
| HIGH   | AES256     | GCM  |
|--------|------------|------|
| MEDIUM | AES192     | GCM  |
|--------|------------|------|
