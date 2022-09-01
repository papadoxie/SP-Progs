#pragma once

#ifndef __BUILTINS_H__
#define __BUILTINS_H__

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

#include <execute.h>
#include <command_parser.h>

#define MAX_BG_PROC 256

typedef struct __builtin_func_t
{
    char *function_index;
    int (*function)(int, char **);
} builtin_func_t;

typedef struct __job_t
{
    pid_t pid;
    int status;
    char *command;
} job_t;

// Array of builtin functions and their names
extern builtin_func_t builtin_funcs[];

// Create a new background task
void create_job(command_t *command, pid_t pid);

#endif // __BUILTINS_H__