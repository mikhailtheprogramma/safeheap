/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "../include/sh_protect.h"
#include <errno.h>

void sh_init_protection()
{
    sh_protected_table = sh_internal_malloc(sizeof(struct sh_protected_memory_table_t));
}

struct sh_protection_policy_t * sh_get_protection_policy(enum sh_protection_grade protection)
{
    for(int p = 0; p < sizeof(sh_protection_policies); p++)
    {
        if(sh_protection_policies[p].protection_grade)
        {
            return &sh_protection_policies[p];
        }
    }

    return NULL;
}

// If ret null then fail
// ret will be forwarded to sh_malloc and then user
shared_buffer ** sh_add_protection_entry(struct sh_segment_descriptor ** segments, size_t amount, enum sh_protection_grade protection)
{
    // Allocate an entry struct
    struct sh_protected_entry_t * entry = sh_internal_malloc(sizeof(struct sh_protected_entry_t));

    entry->segment_amount = amount;
    entry->protection = protection;
    entry->segments_table = segments;
    entry->shared_buffer = NULL;

    // Add to protection table
    sh_protected_table->entries = sh_internal_realloc(sh_protected_table->entries, sizeof(struct sh_protected_entry_t) * (sh_protected_table->amount + 1));

    return &entry->shared_buffer;
}

struct sh_protected_entry_t * sh_get_protected_entry(shared_buffer * buffer)
{
    for(int e = 0; e < sh_protected_table->amount; e++)
        {
            if(sh_protected_table->entries[e])
                {
                    return sh_protected_table->entries[e];
                }
        }
}
