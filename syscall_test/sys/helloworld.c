#include "helloworld.h"

long sys_helloworld(void)
{
    long ret = syscall(SYS_HELLOWORLD);
    return ret;
}