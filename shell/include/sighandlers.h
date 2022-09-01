#pragma once

#ifndef __SIGHNDL_H__
#define __SIGHNDL_H__

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void register_handlers(void);

#endif // __SIGHNDL_H__