#ifndef __SH_CORE_SH__
#define __SH_CORE_SH__
#include <stdlib.h>
#include <stdbool.h>
#include <gcrypt.h>
#include <stdint.h>

// TPM
#include <tss2/tss2_sys.h>
#define TPM2_RC_SUCCESS 0x000

#define URANDOM "/dev/urandom"

typedef uint8_t shared_buffer;
typedef uint8_t _default_size;

struct sh_cipher_policy_t
{
    // Symmetric
    int algorithm;
    int mode;
    unsigned int flag;
    char * key;
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
struct sh_protected_memory_table_t * sh_protected_table; // Use sh_init_protection

#endif
