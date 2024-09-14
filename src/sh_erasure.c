#include "../include/sh_erasure.h"

int8_t sh_check_memory_type(struct sh_segment_descriptor * segment)
{
    // TODO: Parse /proc/<pid>/maps for following information items: address range of our library
    // TODO: Then correlate to the storage device address range

    // <from><dash><to><space>

    // ? How to find virtual address mapping of each drive
}


void sh_erase(struct sh_segment_descriptor * segment);