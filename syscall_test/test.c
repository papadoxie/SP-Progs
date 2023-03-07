// Testing custom syscall
#include "sys/helloworld.h"
#include <stdlib.h>

int main(void)
{
    long ret = sys_helloworld();

    if(ret == -1)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}