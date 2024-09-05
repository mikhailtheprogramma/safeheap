# Safeheap library

## Legal
SPDX-License-Identifier: GPL-3.0 WITH bison-exception
<br>Copyright © 2024 Mikhailuwu

## Purpose
This readme does NOT document the library functions and types. For usage documentation, please check the doc/safeheap-documentation.pdf file.

## Project
The safeheap library project is maintained by mikhailuwu (https://github.com/mikhailuwu) at https://github.com/mikhailuwu/safeheap.

## Bugs and features
If you do experience any bugs or feature requests, please do create an Issue at the project site.

## Safeheap
Safeheap is a C/C++ POSIX compliant library with the focus on memory security implementations. The library utilizes four categories of protection:

- Segmentation
- Cryptography
- Randomization
- Erasure

### Segmentation
Upon a dynamic allocation of memory, the user may specify they want to segment the memory variable. Meaning dividing it into separate chunks spread across the memory heap.

### Cryptography
The user may also specify they want to encrypt the allocated memory. This is done internally when the user writes/reads the memory. The encryption algorithms used are symmetrical meaning there is only one key involved for encrypting and decrypting said memory. The key is stored and handled internally by the library and not made accessible to the user. The key may be stored either in memory in the protected memory table (PMT) or in a TPM module if available.

### Randomization
Various randomization techniques may be used if specified by user upon allocation. Randomization aims to 'randomize' various signatures that may reveal secret information, such as side-channel information (e.g. power analysis, accoustic analysis, cache monitoring, etc.) by deploying techniques to create "noise" on all the vulnerable channels such as performing irrelevant random calculations before, after, or during a memory read/write. Address Space Layout Randomization (ASLR) is also used, moving the memory segments across the heap at random to avoid an attacker from analyzing the data while handled in memory.

## Erasure
Once the data under protection is no longer used, in the event of program termination or freed by user, the library internally may use erasure techniques to ensure the data is no longer accessible. This involves overwriting the data with random data a certain amount of cycles depending on storage medium. 
