#pragma once

#ifndef __WINCH_H__
#define __WINCH_H__

#include <sys/ioctl.h>

#define STDOUT 1
#define SIGWINCH 28

void handle_sigwinch(int sig);

extern struct window window;

struct window
{
    unsigned int rows;
    unsigned int cols;
};

#endif // __WINCH_H__