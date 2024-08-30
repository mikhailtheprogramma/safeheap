/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#ifndef __SH_TPM_H__
#define __SH_TPM_H__
#include "../_include/tss2/tss2-fapi/fapi_int.h"
#include "sh_error.h"
#include "sh_core.h"
#include <stdint.h>

void sh_get_tpm_randbyte(void);

#endif
