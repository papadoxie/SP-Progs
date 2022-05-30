#pragma once

#ifndef __EXECUTE_H__
#define __EXECUTE_H__

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <command_parser.h>

int execute(commands_t *commands);

typedef struct __process_t
{
    pid_t pid;
    int status;
    command_t *command;
} process_t;

#endif // __EXECUTE_H__