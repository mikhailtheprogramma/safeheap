/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "include/safeheap.h"
#include "include/sh_core.h"
#include "include/sh_malloc.h"
#include "include/sh_protect.h"

// Tests
int main()
{
    // Initiate the protection subsystem
    sh_init_protection(true);

    // Allocate
    char * test = (char*)sh_malloc(sizeof(char) * 5, SH_PROTECT_HIGH);

    // Write
    // Read
    // Free
}
