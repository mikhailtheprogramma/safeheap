/* SPDX-License-Identifier: BSD-2-Clause */
/***********************************************************************;
 * Copyright (c) 2020, Intel Corporation
 * All rights reserved.
 ***********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h" // IWYU pragma: keep
#endif

#include "sysapi_util.h"      // for _TSS2_SYS_CONTEXT_BLOB, syscontext_cast
#include "tss2_common.h"      // for TSS2_RC, TSS2_SYS_RC_BAD_REFERENCE, UINT32
#include "tss2_mu.h"          // for Tss2_MU_UINT32_Marshal
#include "tss2_sys.h"         // for TSS2_SYS_CONTEXT, TSS2L_SYS_AUTH_COMMAND
#include "tss2_tpm2_types.h"  // for TPMI_RH_ACT, TPM2_CC_ACT_SetTimeout

TSS2_RC Tss2_Sys_ACT_SetTimeout_Prepare(
    TSS2_SYS_CONTEXT *sysContext,
    TPMI_RH_ACT actHandle,
	UINT32 startTimeout)
{
    TSS2_SYS_CONTEXT_BLOB *ctx = syscontext_cast(sysContext);
    TSS2_RC rval;

    if (!ctx)
        return TSS2_SYS_RC_BAD_REFERENCE;

    rval = CommonPreparePrologue(ctx, TPM2_CC_ACT_SetTimeout);
    if (rval)
        return rval;

    rval = Tss2_MU_UINT32_Marshal(actHandle, ctx->cmdBuffer,
                                  ctx->maxCmdSize, &ctx->nextData);
    if (rval)
        return rval;

    rval = Tss2_MU_UINT32_Marshal(startTimeout, ctx->cmdBuffer,
                                  ctx->maxCmdSize, &ctx->nextData);
    if (rval)
        return rval;

    ctx->decryptAllowed = 0;
    ctx->encryptAllowed = 0;
    ctx->authAllowed = 1;

    return CommonPrepareEpilogue(ctx);
}

TSS2_RC Tss2_Sys_ACT_SetTimeout_Complete(TSS2_SYS_CONTEXT *sysContext)
{
    TSS2_SYS_CONTEXT_BLOB *ctx = syscontext_cast(sysContext);

    if (!ctx)
        return TSS2_SYS_RC_BAD_REFERENCE;

    return CommonComplete(ctx);
}

TSS2_RC Tss2_Sys_ACT_SetTimeout(
    TSS2_SYS_CONTEXT *sysContext,
    TPMI_RH_ACT actHandle,
    TSS2L_SYS_AUTH_COMMAND const *cmdAuthsArray,
    UINT32 startTimeout,
    TSS2L_SYS_AUTH_RESPONSE *rspAuthsArray)
{
    TSS2_SYS_CONTEXT_BLOB *ctx = syscontext_cast(sysContext);
    TSS2_RC rval;

    rval = Tss2_Sys_ACT_SetTimeout_Prepare(sysContext, actHandle, startTimeout);
    if (rval)
        return rval;

    rval = CommonOneCall(ctx, cmdAuthsArray, rspAuthsArray);
    if (rval)
        return rval;

    return Tss2_Sys_ACT_SetTimeout_Complete(sysContext);
}
