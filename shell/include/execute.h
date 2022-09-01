#pragma once

#ifndef __EXECUTE_H__
#define __EXECUTE_H__

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <setjmp.h>

#include <command_parser.h>
#include <builtins.h>

#define BUILTIN_NO_EXEC -124

#define PIPE_READ 0
#define PIPE_WRITE 1

int execute(commands_t *commands);

typedef struct __process_t
{
    pid_t pid;
    int status;
    int *pipe_fd;
    command_t *command;
} process_t;

#endif // __EXECUTE_H__