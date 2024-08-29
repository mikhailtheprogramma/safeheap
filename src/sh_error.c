#include <string.h>
#include <stdio.h>
#include <errno.h>

void sh_error(int error)
{
    printf("Error occured from %p: %s \n", __FUNCTION_NAME__, (char*)strerror(error));
}
