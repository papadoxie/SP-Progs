#pragma once

#ifndef __WINCH_H__
#define __WINCH_H__

#include <sys/ioctl.h>
#include <pthread.h>
#include <winchInterface.h>

#define STDOUT 1
#define SIGWINCH 28

// For some reason ioctl gives 10 columns less than actual
#define TERM_MAGIC_SIZE 10

void init_sigwinch_handler(void);
void handle_sigwinch(int sig);

extern struct window window;

struct window
{
    unsigned int rows;
    unsigned int cols;
};

#endif // __WINCH_H__