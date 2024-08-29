#include "../include/sh_io.h"
#include "../include/sh_protect.h"
#include "gpg-error.h"
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
        buffer = _sh_realloc(buffer, total);
        // Concat them onto each other
        buffer = (shared_buffer*)gpgrt_strconcat((char*)buffer, *(char*)entry->segments_table[s]->address);
    }

    return buffer;
}

void sh_write(shared_buffer * buffer)
{

}
