/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#ifndef __SH_MALLOC_H__
#define __SH_MALLOC_H__
#include "sh_core.h"

void * sh_malloc(size_t size, enum sh_protection_grade protection);
void * sh_free(void * shared_buffer);

// Internal malloc wrappers with error handling
void * _sh_malloc(size_t size);
void * _sh_realloc(void * address, size_t size);

#endif
