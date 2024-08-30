/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#ifndef __SH_CRYPTO_H__
#define __SH_CRYPTO_H__
#include "sh_core.h"
#include "sh_protect.h"

size_t sh_get_key_size(enum sh_protection_grade protection);
void sh_generate_key(char * key, enum sh_protection_grade protection);

#endif
