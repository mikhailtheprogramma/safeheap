/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "../include/sh_tpm.h"
#include <stdio.h>
#include <stdint.h>

void sh_tpm_get_randbyte(size_t num_bytes, uint8_t ** dst)
{
    if((FAPI_CONTEXT * context = Fapi_Initialize(NULL) != TSS2_RC_SUCCESS)
        {
            sh_error(context);
        }

    Fapi_GetRandom(context, num_bytes, dst);
}

void sh_tmp_store_key(char * key)
{
    Fapi_CreateKey	(	FAPI_CONTEXT * 	context,
    char const * 	path,
    char const * 	type,
    char const * 	policyPath,
    char const * 	authValue
    )
}
