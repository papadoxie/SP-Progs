#pragma once

#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <setjmp.h>

#include <prompt.h>
#include <config.h>
#include <command_parser.h>
#include <execute.h>

int init_shell(void);
int interactive_shell(void);

#endif // __SHELL_H__