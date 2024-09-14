/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

/*
    sh_io.h
    Input/output to the protected memory. User interface.
 */

#ifndef __SH_IO_H__
#define __SH_IO_H__
#include "sh_core.h"
#include "sh_malloc.h"

void sh_reset(shared_buffer * buffer);
shared_buffer * sh_read(shared_buffer * buffer);
void sh_write(shared_buffer * buffer);

#endif
