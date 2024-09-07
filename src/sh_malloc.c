/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "../include/sh_malloc.h"
#include "../include/sh_protect.h"
#include <errno.h>

void * sh_internal_malloc(size_t size)
{
    void * tmp = malloc(size);
    if(tmp == NULL)
        {
            sh_error(errno);
        }
    return tmp;
}

void * sh_internal_realloc(void * address, size_t size)
{
    void * tmp = realloc(address, size);
    if(tmp == NULL)
        {
            sh_error(errno);
            return address;
        }
    return tmp;
}

void * sh_malloc(size_t size, enum sh_protection_grade protection)
{
    struct sh_protection_policy_t * protection_policy = sh_get_protection_policy(protection);
    struct sh_segment_descriptor ** segments_table;
    struct sh_segment_descriptor ** tmp_segments;
    size_t amount;

    size_t cipher_changes = sh_get_cipher_outsize_diff(protection_policy->cipher_policy.algorithm, protection_policy->cipher_policy.mode);

    if(protection_policy->segmentation_enabled)
        {
            size_t segment_index = 0;
            for(int remaining = size; remaining > 0; remaining-=protection_policy->segment_size)
                {
                    // Allocate a segment descriptor pointer in table
                    segments_table = sh_internal_realloc(segments_table, sizeof(struct sh_segment_descriptor **) * (segment_index + 1));

                    // Allocate an actual descriptor struct
                    segments_table[segment_index] = sh_internal_malloc(sizeof(struct sh_segment_descriptor));

                    // Does remainder fill a block
                    if(remaining < protection_policy->segment_size)
                        {
                            // If not, then use remainder
                            segments_table[segment_index]->address = sh_internal_malloc(remaining + cipher_changes);
                            segments_table[segment_index]->size = remaining + cipher_changes;
                        }
                    // Otherwise, use full block
                    segments_table[segment_index]->address = sh_internal_malloc(protection_policy->segment_size + cipher_changes);
                    segments_table[segment_index]->size = protection_policy->segment_size + cipher_changes;

                    segment_index++;
                }

            amount = segment_index;
        }
    else // No segmentation
        {
            // Allocate a segment descriptor pointer in table
            segments_table = sh_internal_malloc(sizeof(struct sh_segment_descriptor **));
            // Allocate an actual descriptor struct
            segments_table[0] = sh_internal_malloc(sizeof(struct sh_segment_descriptor));

            // Allocate actual data + authentication tag depending on mode (retr by func)
            size += cipher_changes
            segments_table[0]->address = sh_internal_malloc(size);
            segments_table[0]->size = size;
            amount = 1;
        }

    // Add entry to table
    shared_buffer ** identifier_buffer = sh_add_protection_entry(segments_table, amount, protection); // TODO: Is this correct
    return (void *)identifier_buffer;
}

void * sh_free(void * shared_buffer);
