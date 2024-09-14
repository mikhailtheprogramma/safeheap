/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

/*
    sh_error.h
    Error handling
 */

#ifndef __SH_ERROR_H__
#define __SH_ERROR_H__

#include "gcrypt.h"
void sh_error(int error);
void sh_error_gcry(gcry_error_t error);

#endif
