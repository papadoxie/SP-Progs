#pragma once

#ifndef __BUILTINS_H__
#define __BUILTINS_H__

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

typedef struct __builtin_func_t
{
    char *function_index;
    int (*function)(int, char **);
} builtin_func_t;

// Array of builtin functions and their names
extern builtin_func_t builtin_funcs[];

#endif // __BUILTINS_H__