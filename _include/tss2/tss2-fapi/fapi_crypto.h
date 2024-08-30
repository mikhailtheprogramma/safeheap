/* SPDX-License-Identifier: BSD-2-Clause */
/*******************************************************************************
 * Copyright 2018-2019, Fraunhofer SIT sponsored by Infineon Technologies AG
 * All rights reserved.
 ******************************************************************************/
#ifndef FAPI_CRYPTO_H
#define FAPI_CRYPTO_H

#include <stddef.h>           // for size_t
#include <stdint.h>           // for uint8_t, uint16_t

#include "ifapi_keystore.h"   // for IFAPI_OBJECT
#include "ifapi_profiles.h"   // for IFAPI_PROFILE
#include "tss2_common.h"      // for TSS2_RC
#include "tss2_tpm2_types.h"  // for TPM2B_PUBLIC, TPM2_ALG_ID, TPMI_ALG_HASH

TSS2_RC
ifapi_get_profile_sig_scheme(
    const IFAPI_PROFILE     *profile,
    const TPMT_PUBLIC           *tpmPublic,
    TPMT_SIG_SCHEME             *signatureScheme);

TSS2_RC
ifapi_der_sig_to_tpm(
    const TPMT_PUBLIC           *tpmPublic,
    const unsigned char         *signature,
    size_t                      signatureSize,
    TPMI_ALG_HASH               hashAlgorithm,
    TPMT_SIGNATURE              *tpmSignature);

TSS2_RC
ifapi_tpm_ecc_sig_to_der(
    const TPMT_SIGNATURE        *tpmSignature,
    uint8_t                     **signature,
    size_t                      *signatureSize);

TSS2_RC
ifapi_pub_pem_key_from_tpm(
    const TPM2B_PUBLIC          *tpmPublicKey,
    char                        **pemKey,
    int                         *pemKeySize);

TSS2_RC
ifapi_verify_signature(
    const IFAPI_OBJECT          *keyObject,
    const uint8_t               *signature,
    size_t                      signatureSize,
    const uint8_t               *digest,
    size_t                      digestSize);

TSS2_RC
ifapi_verify_signature_quote(
    const IFAPI_OBJECT          *keyObject,
    const uint8_t               *signature,
    size_t                      signatureSize,
    const uint8_t               *digest,
    size_t                      digestSize,
    const TPMT_SIG_SCHEME       *signatureScheme);


typedef struct IFAPI_CRYPTO_CONTEXT IFAPI_CRYPTO_CONTEXT_BLOB;

TSS2_RC
ifapi_crypto_hash_start(
    IFAPI_CRYPTO_CONTEXT_BLOB   **context,
    TPM2_ALG_ID                 hashAlgorithm);

TSS2_RC
ifapi_crypto_hash_update(
    IFAPI_CRYPTO_CONTEXT_BLOB   *context,
    const uint8_t               *buffer,
    size_t                      size);

TSS2_RC
ifapi_crypto_hash_finish(
    IFAPI_CRYPTO_CONTEXT_BLOB   **context,
    uint8_t                     *digest,
    size_t                      *digestSize);

void
ifapi_crypto_hash_abort(
    IFAPI_CRYPTO_CONTEXT_BLOB   **context);

TSS2_RC
ifapi_cert_to_pem(
    const uint8_t               *certBuffer,
    size_t                      certBufferSize,
    char                        **pemCert,
    TPM2_ALG_ID                 *certAlgorithmId,
    TPM2B_PUBLIC                *tpmPublic);

size_t
ifapi_hash_get_digest_size(
    TPM2_ALG_ID                 hashAlgorithm);

TSS2_RC
ifapi_get_tpm2b_public_from_pem(
    const char                  *pemKey,
    TPM2B_PUBLIC                *tpmPublic);

TSS2_RC
ifapi_get_hash_alg_for_size(
    uint16_t                    size,
    TPMI_ALG_HASH               *hashAlgorithm);

TSS2_RC
ifapi_get_public_from_pem_cert(
    const char*                 pem_cert,
    TPM2B_PUBLIC *tpm_public);

TSS2_RC
ifapi_initialize_sign_public(
    TPM2_ALG_ID                 signatureAlgorithm,
    TPM2B_PUBLIC                *template);

TPM2_ALG_ID
ifapi_get_signature_algorithm_from_pem(
    const char                  *pemKey);

TSS2_RC
ifapi_get_tpm_key_fingerprint(
    const TPM2B_PUBLIC *tpmPublicKey,
    TPMI_ALG_HASH hashAlg,
    TPM2B_DIGEST *fingerprint);

TSS2_RC
ifapi_base64encode(
    uint8_t *buffer,
    size_t buffer_size,
    char** b64_data);

TSS2_RC
ifapi_rsa_encrypt(
    const char *pem_key,
    const TPMT_RSA_DECRYPT *rsa_decrypt_scheme,
    const uint8_t *plainText,
    size_t plainTextSize,
    uint8_t  **cipherText,
    size_t *cipherTextSize);

TSS2_RC
ifapi_openssl_load_private(
    const char *pem_key,
    const char *passin,
    const char *object_auth,
    TPM2B_PUBLIC *template,
    TPM2B_PUBLIC *pub,
    TPM2B_SENSITIVE *priv);

#endif /* FAPI_CRYPTO_H */
