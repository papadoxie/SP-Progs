#pragma once

#ifndef __COMMAND_PARSER_H__
#define __COMMAND_PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define COMMAND_DELIMITERS ";\n"
#define ARG_DELIMITERS " "
#define PIPE '|'
#define PIPE_DELIMITERS "|"
#define REDIRECT_DELIMITERS "<>"

#define REDIRECT_IN "<"
#define REDIRECT_OUT ">"
#define REDIRECT_APPEND ">>"
#define REDIRECT_ERR "2>"

#define NO_PIPE 0
#define PIPE_OUT 1
#define PIPE_IN 2
#define PIPE_BOTH 3

typedef struct __command_t
{
    char *command;
    int argc;
    char **argv;
    FILE *instream;
    FILE *outstream;
    FILE *errstream;
    bool piped_out;
    bool piped_in;
} command_t;

typedef struct __commands
{
    uint32_t num_commands;
    command_t **commands;
} commands_t;

// This returns a malloc'd string. Must be freed by caller
char *read_commandline(FILE *stream);

// This returns a malloc'd struct. Must be freed by caller
commands_t *parse_commandline(const char *command_line);

// Free the commands struct
void free_commands(commands_t *commands);

#endif