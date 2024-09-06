/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "../include/sh_io.h"
#include "../include/sh_protect.h"
#include <string.h>
#include <errno.h>

void sh_reset(shared_buffer * buffer)
{
    struct sh_protected_entry_t * entry = sh_get_protected_entry(buffer);

    if(entry->shared_buffer != buffer)
    {
        errno = EINVAL;
    }

    free(buffer);
}

shared_buffer * sh_read(shared_buffer * buffer)
{
    struct sh_protected_entry_t * entry = sh_get_protected_entry(buffer);

    sh_reset(buffer);

    // Allocate size for buffer based on total size of segments
    size_t total = 0;
    for(int s = 0; s < entry->segment_amount; s++)
    {
        // Resize the buffer for each segment
        total += entry->segments_table[s]->size;
        buffer = sh_internal_realloc(buffer, total);
        // Concat them onto each other
        buffer = (shared_buffer*)strcat((char*)buffer, (char*)entry->segments_table[s]->address);
    }

    struct sh_protection_policy_t * policy = sh_get_protection_policy(entry->protection);
    if(policy->encryption_enabled)
        {
            sh_decrypt_buffer(buffer, entry);
        }

    return buffer;
}

void sh_write(shared_buffer * buffer)
{

}
