/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "include/safeheap.h"
#include "include/sh_core.h"
#include "include/sh_malloc.h"
#include "include/sh_protect.h"

int main()
{
    sh_init_protection();
}
