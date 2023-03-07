#pragma once

#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <sys/syscall.h>
#include <unistd.h>

#define SYS_HELLOWORLD 696
long sys_helloworld(void);

#endif // HELLO_WORLD_H