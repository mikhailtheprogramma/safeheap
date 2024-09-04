/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#ifndef __SH_CRYPTO_H__
#define __SH_CRYPTO_H__
#include "sh_core.h"
#include "sh_protect.h"

// Key mngmt
void sh_get_key(struct sh_protected_entry_t * entry, char * key);

// Encrypt
void sh_encrypt_segment(struct sh_segment_descriptor segment);

// Decrypt

// Keygen
size_t sh_get_key_size(enum sh_protection_grade protection);
void sh_generate_key(char * key, enum sh_protection_grade protection);

#endif
