/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

/*
    sh_crypto.h
    Contains cryptography-related functions
 */

#ifndef __SH_CRYPTO_H__
#define __SH_CRYPTO_H__
#include "sh_core.h"
#include "sh_protect.h"

size_t sh_get_cipher_outsize_diff(int algorithm, int mode);
void sh_get_key(struct sh_protected_entry_t * entry, char * key);
void sh_encrypt_segment(struct sh_segment_descriptor * segment, struct sh_protected_entry_t * entry);
size_t sh_get_key_size(enum sh_protection_grade protection);
size_t sh_generate_key(char * key, enum sh_protection_grade protection);

#endif
