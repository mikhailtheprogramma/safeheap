/* SPDX-License-Identifier: BSD-2-Clause */
/***********************************************************************;
 * Copyright (c) 2015 - 2017, Intel Corporation
 * All rights reserved.
 ***********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h" // IWYU pragma: keep
#endif

#include "sysapi_util.h"      // for _TSS2_SYS_CONTEXT_BLOB, syscontext_cast
#include "tss2_common.h"      // for TSS2_RC, TSS2_SYS_RC_BAD_REFERENCE, TSS...
#include "tss2_mu.h"          // for Tss2_MU_UINT16_Marshal, Tss2_MU_TPM2B_A...
#include "tss2_sys.h"         // for TSS2_SYS_CONTEXT, TSS2L_SYS_AUTH_COMMAND
#include "tss2_tpm2_types.h"  // for TPMI_DH_OBJECT, TPM2B_AUTH, TPMI_ALG_MA...

TSS2_RC Tss2_Sys_MAC_Start_Prepare(
    TSS2_SYS_CONTEXT *sysContext,
    TPMI_DH_OBJECT handle,
    const TPM2B_AUTH *auth,
    TPMI_ALG_MAC_SCHEME inScheme)
{
    TSS2_SYS_CONTEXT_BLOB *ctx = syscontext_cast(sysContext);
    TSS2_RC rval;

    if (!ctx)
        return TSS2_SYS_RC_BAD_REFERENCE;

    if (IsAlgorithmWeak(hashAlg, 0))
        return TSS2_SYS_RC_BAD_VALUE;

    rval = CommonPreparePrologue(ctx, TPM2_CC_MAC_Start);
    if (rval)
        return rval;

    rval = Tss2_MU_UINT32_Marshal(handle, ctx->cmdBuffer,
                                  ctx->maxCmdSize,
                                  &ctx->nextData);
    if (rval)
        return rval;

    if (!auth) {
        ctx->decryptNull = 1;

        rval = Tss2_MU_UINT16_Marshal(0, ctx->cmdBuffer,
                                      ctx->maxCmdSize,
                                      &ctx->nextData);
    } else {

        rval = Tss2_MU_TPM2B_AUTH_Marshal(auth, ctx->cmdBuffer,
                                          ctx->maxCmdSize,
                                          &ctx->nextData);
    }

    if (rval)
        return rval;

    rval = Tss2_MU_UINT16_Marshal(inScheme, ctx->cmdBuffer,
                                  ctx->maxCmdSize,
                                  &ctx->nextData);
    if (rval)
        return rval;

    ctx->decryptAllowed = 1;
    ctx->encryptAllowed = 0;
    ctx->authAllowed = 1;

    return CommonPrepareEpilogue(ctx);
}

TSS2_RC Tss2_Sys_MAC_Start_Complete(
    TSS2_SYS_CONTEXT *sysContext,
    TPMI_DH_OBJECT *sequenceHandle)
{
    TSS2_SYS_CONTEXT_BLOB *ctx = syscontext_cast(sysContext);
    TSS2_RC rval;

    if (!ctx)
        return TSS2_SYS_RC_BAD_REFERENCE;

    rval = Tss2_MU_UINT32_Unmarshal(ctx->cmdBuffer,
                                    ctx->maxCmdSize,
                                    &ctx->nextData,
                                    sequenceHandle);
    if (rval)
        return rval;

    return CommonComplete(ctx);
}

TSS2_RC Tss2_Sys_MAC_Start(
    TSS2_SYS_CONTEXT *sysContext,
    TPMI_DH_OBJECT handle,
    const TSS2L_SYS_AUTH_COMMAND *cmdAuthsArray,
    const TPM2B_AUTH *auth,
    TPMI_ALG_MAC_SCHEME inScheme,
    TPMI_DH_OBJECT *sequenceHandle,
    TSS2L_SYS_AUTH_RESPONSE *rspAuthsArray)
{
    TSS2_SYS_CONTEXT_BLOB *ctx = syscontext_cast(sysContext);
    TSS2_RC rval;

    rval = Tss2_Sys_MAC_Start_Prepare(sysContext, handle, auth, inScheme);
    if (rval)
        return rval;

    rval = CommonOneCall(ctx, cmdAuthsArray, rspAuthsArray);
    if (rval)
        return rval;

     return Tss2_Sys_MAC_Start_Complete(sysContext, sequenceHandle);
}
