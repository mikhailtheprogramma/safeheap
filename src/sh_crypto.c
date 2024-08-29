#include "../include/sh_crypto.h"
#include <gcrypt.h>
#include <errno.h>
#include <stdio.h>

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
    key = _sh_realloc(key, key_size);

    FILE * urandom_file = fopen(URANDOM, "r");
    if(fread(key, key_size, 1, urandom_file) < key_size)
        {
            fclose(urandom_file);
            sh_error(errno);
        }
    fclose(urandom_file);
}
