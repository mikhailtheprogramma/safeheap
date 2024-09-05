/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#ifndef __SH_CORE_SH__
#define __SH_CORE_SH__
#include <stdlib.h>
#include <stdbool.h>
#include <gcrypt.h>
#include <stdint.h>

bool TPM_ENABLED; // Initialized by sh_init_protection
#define NEED_LIBGCRYPT_VERSION "1.0"

#define URANDOM "/dev/urandom"

typedef uint8_t shared_buffer; // Buffer on-demand
typedef uint8_t _default_size; // Default internal byte handling of protected variable data

/*
 * +----------------------------------------------------+
 * |                 CIPHER KEY SIZES                   |
 * +----------------------------------------------------+
 */

// Key sizes depending on algorithm
struct algo_key_size
{
    int algorithm;
    size_t sz_max;
};

struct algo_key_size key_size_table[] =
{
    // Algorithm            Sz
    {GCRY_CIPHER_AES128,    16  },
    {GCRY_CIPHER_AES192,    24  },
    {GCRY_CIPHER_AES256,    32  },
    {GCRY_CIPHER_3DES,      21  },
    {GCRY_CIPHER_TWOFISH,   32  },
    {GCRY_CIPHER_BLOWFISH,  56  }
};

/*
 * +----------------------------------------------------+
 * |           PROTECTION AND CIPHER POLICY             |
 * +----------------------------------------------------+
 */

enum key_store_type
{
    TPM_STORE,
    MEMORY_STORE
};

struct sh_cipher_policy_t
{
    // Symmetric
    int algorithm;
    int mode;
    unsigned int flag;
    enum key_store_type key_store_type; // Indicates where the key is stored

    char * unsecure_key; // If local key store

    // TPM key access values
    // More research needed into TSS2
};

enum sh_protection_grade
{
    SH_PROTECT_HIGH,
    SH_PROTECT_MEDIUM,
    SH_PROTECT_LOW,
    SH_PROTECT_NONE
};

struct sh_protection_policy_t
{
    enum sh_protection_grade protection_grade;

    bool segmentation_enabled;
    bool encryption_enabled;
    bool erasure_enabled;
    bool aslr_enabled;
    bool noise_enabled;
    size_t segment_size;

    struct sh_cipher_policy_t cipher_policy;
};

struct sh_protection_policy_t sh_protection_policies[4] =
{
    // Grade                Seg     Enc     Eras    ASLR    Noise   SegSize   Ciper algorithm         Mode                    Flag
    { SH_PROTECT_HIGH,      true,   true,   true,   true,   true,   5,        { GCRY_CIPHER_AES256,   GCRY_CIPHER_MODE_GCM,   GCRY_CIPHER_SECURE } },
    { SH_PROTECT_MEDIUM,    true,   true,   true,   false,  true,   10,       { GCRY_CIPHER_AES192,   GCRY_CIPHER_MODE_GCM,   GCRY_CIPHER_SECURE } },
    { SH_PROTECT_LOW,       true,   false,  true,   false,  false,  15,       { GCRY_CIPHER_NONE,     GCRY_CIPHER_MODE_NONE,  GCRY_CIPHER_SECURE } },
    { SH_PROTECT_NONE,      false,  false,  true,   false,  true,   0,        { GCRY_CIPHER_NONE,     GCRY_CIPHER_MODE_NONE,  GCRY_CIPHER_SECURE } },
};

/*
 * +----------------------------------------------------+
 * |              CIPHERTEXT SIZE CHECK                 |
 * +----------------------------------------------------+
 */

// Check table for ciphertext size changes (issue 15)
struct sh_cipher_outsize_algo_t
{
    int algorithm;
    int mode;
    int de_inc_a;
    int de_inc_b;
};

/*
    GCM (Galois/Counter Mode)
        Increases length due to authentication tag (typically 16 bytes).
    CCM (Counter with CBC-MAC)
        Increases length due to authentication tag (8-16 bytes).
*/
struct sh_cipher_outsize_t sh_ciphertext_sz_table[2] =
{
    // TODO: each AES each mode
    {GCRY_CIPHER_AES, GCRY_CIPHER_MODE_GCM, 16, 16},
    {GCRY_CIPHER_AES, GCRY_CIPHER_MODE_CCM, 8, 16}
};

/*
 * +----------------------------------------------------+
 * |             PROTECTED MEMORY TABLE                 |
 * +----------------------------------------------------+
 */

struct sh_segment_descriptor
{
    _default_size * address;
    size_t size;
};

struct sh_protected_entry_t
{
    shared_buffer * shared_buffer; // Shared as pointer & to user after malloc, used as a buffer but also as a reference for internal use
    enum sh_protection_grade protection;
    size_t segment_amount;
    struct sh_segment_descriptor ** segments_table;
};

struct sh_protected_memory_table_t
{
    size_t amount;
    struct sh_protected_entry_t ** entries;
};

// GLOBALS
struct sh_protected_memory_table_t * sh_protected_table; // Use sh_init_protection to initialize along with TPM_ENABLED

#endif
