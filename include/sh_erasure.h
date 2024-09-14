/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

/*
    sh_erasure.h
    Contains definitions of functions and data types regarding data erasure
 */

#ifndef __SH_ERASURE_H__
#define __SH_ERASURE_H__

#include "sh_core.h"

#define MEM_ID_NVME 1
#define MEM_ID_HDD  2
#define MEM_ID_RAM  3

// Returns MEM_ID_*
int8_t sh_check_memory_type(struct sh_segment_descriptor * segment);
void sh_erase(struct sh_segment_descriptor * segment);

#endif