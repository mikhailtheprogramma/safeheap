/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "../include/sh_crypto.h"
#include "../include/sh_core.h"
#include "../include/sh_tpm.h"
#include <gcrypt.h>
#include <errno.h>
#include <stdio.h>

// TODO: Used by sh_read, sh_write interface functions for transformation of protected memory data
char * sh_get_key(struct sh_protected_entry_t * entry)
{
    struct sh_protection_policy_t * policy = sh_get_protection_policy(entry->protection);

    // Safeguard, check if encryption enabled
    if(!policy->encryption_enabled)
        {
            errno = EINVAL; // Invalid parameter
            return NULL;
        }

    // IMPORTANT!
    // Only store key in stack
    char * key = sh_internal_malloc(sh_get_key_size(policy->protection_grade));

    // Check key store location
    switch(policy->cipher_policy.key_store_type)
    {
        case TPM_STORE:
            strcpy(key, sh_tmp_get_key(entry));
        case MEMORY_STORE:
            strcpy(key, policy->cipher_policy.unsecure_key);
    }

    return key;
}

void sh_encrypt_segment(struct sh_segment_descriptor * segment, struct sh_protected_entry_t * entry)
{
    char * key = sh_get_key(entry);

    free(key);
}

// Replace with issue 12 solution
size_t sh_get_key_size(enum sh_protection_grade protection)
{
    // Identify algorithm and appropriate key size
    size_t key_size;
    struct sh_protection_policy_t * protection_policy = sh_get_protection_policy(protection);

    for(int ksz = 0; ksz < sizeof(key_size_table); ksz++)
        {
            if(protection_policy->cipher_policy.algorithm == key_size_table[ksz].algorithm)
                {
                    return key_size_table[ksz].sz_max;
                }
        }

    return key_size;
}

void sh_generate_key(char * key, enum sh_protection_grade protection)
{
    size_t key_size = sh_get_key_size(protection);
    key = sh_internal_realloc(key, key_size);

    FILE * urandom_file = fopen(URANDOM, "r");
    if(fread(key, key_size, 1, urandom_file) < key_size)
        {
            fclose(urandom_file);
            sh_error(errno);
        }
    fclose(urandom_file);
}
