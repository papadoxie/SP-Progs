#pragma once

#ifndef __WINCH_H__
#define __WINCH_H__

#include <signal.h>
#include <terminal.h>
#include <sys/ioctl.h>

#define STDOUT 1

void handle_sigwinch(int sig);

#endif // __WINCH_H__