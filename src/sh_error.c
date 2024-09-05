/* SPDX-License-Identifier: GPL-3.0 WITH bison-exception */
/* Copyright © 2024 Mikhailuwu */

#include <string.h>
#include <stdio.h>
#include <errno.h>

void sh_error(int error)
{
    printf("Error occured from %p: %s \n", __FUNCTION_NAME__, (char*)strerror(error));
}

void sh_error_gcry(struct gcry_error_t * error)
{
    printf("Error occured from %p: %s \n", __FUNCTION_NAME__, gcry_strerror(error));
}
