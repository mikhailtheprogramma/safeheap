/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#ifndef __SH_TPM_H__
#define __SH_TPM_H__
#include <tss2/tss2-fapi/fapi_types.h>
#include "sh_error.h"
#include "sh_core.h"
#include <stdint.h>

bool sh_tpm_available();
void sh_tpm_get_randbyte(size_t num_bytes, uint8_t ** dst);
char * sh_tpm_get_key(struct sh_protected_entry_t * entry, char * key);

// Handles TSS2 subroutine calls with endgoal to store crypto key in TPM
void sh_tpm_store_key(char * key);

#endif
