/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "include/safeheap.h"
#include "include/sh_core.h"
#include "include/sh_malloc.h"
#include "include/sh_protect.h"
#include "include/sh_io.h"

// Tests
int main()
{
    // Initiate the protection subsystem
    sh_init_protection(true);

    struct test_struct_t
    {
        char name[100];
        bool stupidOrNot;
        int bits;
    };

    // Allocate
    char * test1 = (char*)sh_malloc(sizeof(char) * 5, SH_PROTECT_HIGH);
    uint8_t * test2 = (uint8_t*)sh_malloc(sizeof(char) * 100, SH_PROTECT_MEDIUM);
    struct test_struct_t * test3 = (struct test_struct_t*)sh_malloc(sizeof(struct test_struct_t), SH_PROTECT_LOW);

    // Write
    test3 = (struct test_struct_t*)sh_read((void*)test3);

    // Read
    // Free
}
