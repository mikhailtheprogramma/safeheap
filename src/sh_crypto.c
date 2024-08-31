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
    char key[sh_get_key_size(policy->protection_grade)];

    // Check key store location
    switch(policy->cipher_policy.key_store_type)
    {
        case TPM_STORE:
            key = sh_tmp_get_key(entry);
        case MEMORY_STORE:

        case HIGHLY_EXPERIMENTAL_INTERNET_STORE:
            // buddy, i have no fucking clue
            return NULL;
    }

    return key;
}

void sh_encrypt_segment(struct sh_segment_descriptor * segment, char * key)
{
}

// Replace with issue 12 solution
size_t sh_get_key_size(enum sh_protection_grade protection)
{
    // Identify algorithm and appropriate key size
    size_t key_size;
    struct sh_protection_policy_t * protection_policy = sh_get_protection_policy(protection);

    switch(protection_policy->cipher_policy.algorithm)
    {
        // ! Sizes are in bytes
        case GCRY_CIPHER_AES128 || GCRY_CIPHER_AES:   // Key size: 128 bits
            key_size = 16;
        case GCRY_CIPHER_AES192:    // Key size: 192 bits
            key_size = 24;
        case GCRY_CIPHER_AES256:    // Key size: 256 bits
            key_size = 32;
        case GCRY_CIPHER_3DES:      // Key size: 168 bits (using three 56-bit keys)
            key_size = 21;
        case GCRY_CIPHER_TWOFISH:   // Key sizes: 128, 192, 256 bits
            // Depending on encryption grade, the size varies from low:128 through high:256
            switch(protection)
            {
                case SH_PROTECT_HIGH:
                    key_size = 32;
                case SH_PROTECT_MEDIUM:
                    key_size = 24;
                case SH_PROTECT_LOW:
                    key_size = 16;
                case SH_PROTECT_NONE:
                    key_size = 0;
                    errno = EINVAL;
            }
        case GCRY_CIPHER_BLOWFISH:  // Key sizes: 32 to 448 bits
            switch(protection)
            {
                case SH_PROTECT_HIGH:
                    key_size = 4;
                case SH_PROTECT_MEDIUM:
                    key_size = 25;
                case SH_PROTECT_LOW:
                    key_size = 56;
                case SH_PROTECT_NONE:
                    key_size = 0;
                    errno = EINVAL;
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
