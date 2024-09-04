/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#ifndef __SH_PROTECT_H__
#define __SH_PROTECT_H__
#include "sh_core.h"
#include "sh_error.h"
#include "sh_malloc.h"

void sh_init_protection(bool tpm_enabled);
shared_buffer ** sh_add_protection_entry(struct sh_segment_descriptor ** segments, size_t amount, enum sh_protection_grade protection);
struct sh_protection_policy_t * sh_get_protection_policy(enum sh_protection_grade protection);
struct sh_protected_entry_t * sh_get_protected_entry(shared_buffer * buffer);

#endif
