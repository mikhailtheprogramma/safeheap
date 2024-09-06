/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "../include/sh_crypto.h"
#include "../include/sh_core.h"
#include "../include/sh_tpm.h"
#include <complex.h>
#include <gcrypt.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>

size_t sh_get_cipher_outsize_diff(int algorithm, int mode)
{
    for(int x = 0; x < sizeof(sh_ciphertext_sz_diff_table); x++)
        {
            // How do we determine the specific sz?
            return sh_ciphertext_sz_diff_table[x].de_inc_;
        }
}

void sh_get_key(struct sh_protected_entry_t * entry, char * key)
{
    struct sh_protection_policy_t * policy = sh_get_protection_policy(entry->protection);

    // Safeguard, check if encryption enabled
    if(!policy->encryption_enabled)
        {
            errno = EINVAL; // Invalid parameter
        }

    // Check key store location
    switch(policy->cipher_policy.key_store_type)
    {
        case TPM_STORE:
            sh_tpm_get_key(entry, key);
        case MEMORY_STORE:
            strcpy(key, policy->cipher_policy.unsecure_key);
    }
}

void sh_init_gcrypt()
{
    if(!gcry_check_version(NEED_LIBGCRYPT_VERSION))
        {
            printf("libgcrypt is too old (need %s, have %s)\n", NEED_LIBGCRYPT_VERSION, gcry_check_version(NULL));
        }
}

void sh_encrypt_segment(struct sh_segment_descriptor * segment, struct sh_protected_entry_t * entry)
{
    // Retrieve key
    char key[sh_get_key_size(entry->protection)];
    sh_get_key(entry, key);

    // TODO: Implement TPM supported encryption
    if(!gcry_control(GCRYCTL_INITIALIZATION_FINISHED_P))
        {
            printf("Libgcrypt has not been initialized, attempting initialization by library ... \n", stderr);
            sh_init_gcrypt();
        }

    struct sh_protection_policy_t * policy = sh_get_protection_policy(entry->protection);
    gcry_cipher_hd_t cipher_handle;
    gcry_handler_error_t retcode;
    gcry_cipher_open(&cipher_handle, policy->cipher_policy.algorithm, policy->cipher_policy.mode, policy->cipher_policy.flag);
    gcry_cipher_setkey(cipher_handle, key, sh_get_key_size(entry->protection));
    gcry_cipher_setiv(cipher_handle, );

    char * out[segment->size]; // most algorithms do not extend the size by padding methods etc.

    if((retcode = gcry_cipher_encrypt(cipher_handle, out, segment->size, segment->address, segment->size)) == 0)
        {
            sh_error_gcry(retcode);
        }

    gcry_cipher_close(cipher_handle);
}

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

// TODO: issue 11
size_t sh_generate_key(char * key, enum sh_protection_grade protection)
{
    size_t key_size = sh_get_key_size(protection);
    key = sh_internal_realloc(key, key_size);

    // Use TPM or normal keygen
    struct sh_protection_policy_t * policy = sh_get_protection_policy(protection);
    switch(policy->cipher_policy.key_store_type)
    {
        case TPM_STORE:
            if(TPM_ENABLED && sh_tpm_available())
                {
                    sh_
                }
        case MEMORY_STORE:
            FILE * urandom_file = fopen(URANDOM, "r");
            if(fread(key, key_size, 1, urandom_file) < key_size)
                {
                    fclose(urandom_file);
                    sh_error(errno);
                }
            fclose(urandom_file);
    }

    return key_size;
}
