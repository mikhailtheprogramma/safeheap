/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include "../include/sh_tpm.h"
#include <stdio.h>
#include <stdint.h>

void sh_tpm_fapi_init(FAPI_CONTEXT * context)
{
    if((context = Fapi_Initialize(NULL) != TSS2_RC_SUCCESS)
        {
            sh_error(context);
        }
}

void sh_tpm_get_randbyte(size_t num_bytes, uint8_t ** dst)
{
    // TODO: ISSUE 10, consider removing, replacing with one-time init
    FAPI_CONTEXT * context;
    sh_tpm_fapi_init(context);
    Fapi_GetRandom(context, num_bytes, dst);
}

void sh_tpm_store_key(char * key)
{
    // TODO: ISSUE 10, consider removing, replacing with one-time init
    FAPI_CONTEXT * context;
    sh_tpm_fapi_init(context);

    if((TSS2_RC retcode = Fapi_CreateKey(context, )) != TSS2_RC_SUCCESS)
    {
        sh_error(retcode);
    }
}
