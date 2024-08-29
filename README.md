# SafeHeap Library Documentation

## 1. Project
<hr>
- <i>The </i><i>project </i><i>is </i><i>maintained </i><i>by </i><i>Mikhailuwu </i><i>(https://github.com/mikhailuwu) </i>at https://github.com/mikhailuwu/safeheap.
- If you have any bugs or feature requests then please do create an issue at the project site.

## 1.1 Purpose
<hr>
- SafeHeap (safeheap.h) is a C/C++ library made primarily for Linux kernel systems, providing a framework of security implementations for the user developer to use for a more secure memory handling.

## Content
<hr>
- 1. Project
-    1.1 Purpose
- 2. Protection
-    2.1 Segmentation
-    2.2 Cryptography
-        2.2.1 Key storage
-              2.2.1.1 TPM
-              2.2.1.2 Memory
-              2.2.1.3 Internet (experimental)
-        2.2.2 Algorithms
-    2.3 Randomization
-        2.3.1 Address Space Layout Randomization
-        2.3.2 Side-Channel Noise
-    2.4 Erasure
-        2.4.1 Volatile Memory Wiping
-        2.4.2 Hard Disk Memory Wiping
- 3. External
-    3.1 Functions
-        3.1.1 sh\_malloc
-        3.1.2 sh\_free
-        3.1.3 sh\_read
-        3.1.4 sh\_write
-    3.2 Types
-        3.2.1 shared\_buffer
- 4. Internal
-     4.1 Types
-         4.1.1 sh\_protected\_memory\_table\_t
-         4.1.2 sh\_protected\_entry\_t
-         4.1.3 sh\_segment\_descriptor\_t
-         4.1.4 sh\_protection\_policy\_t
-         4.1.5 sh\_cipher\_policy\_t
-     4.2 Functions

## 2. Protection
<hr>
For a dynamic variable to become protected, the user must first call the sh\_malloc (external) function. This function will allocate heap memory either as a single block or in segments depending on user parameters. Thereafter an entry is created internally in the Protection Memory Table (PMT) with this information, including a protection grade passed by the user. The protection grade indicates what protection policy should be employed when handling the allocated memory, including encryption, segmentation, aslr, side-channel noise, and erasure. After the sh\_malloc finishes, it returns an identifier pointer used to reference the protected memory through the sh\_free, sh\_read, and sh\_write functions.

To read the memory the user must call the sh\_read function that internally transforms the protected memory into a single buffer which is then provided to the user as a pointer, whether the identifier pointer is changed or not depends on the memory address space layout just as with malloc family functions.

To write to memory the user must first call the 
