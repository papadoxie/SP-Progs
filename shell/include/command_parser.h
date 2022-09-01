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
#define PIPE "|"
#define PIPE_DELIMITERS "|"
#define REDIRECT_DELIMITERS "<>"

#define BG "&"

#define REDIRECT_IN "<"
#define REDIRECT_OUT ">"
#define REDIRECT_APPEND ">>"
#define REDIRECT_ERR "2>"

#define READ "r"
#define WRITE "w"
#define APPEND "a"

#define ARG_INDEX command->argc - 1

// Holds one command and data required to execute it
typedef struct __command_t
{
    char *command;   // Command string
    int argc;        // Number of arguments
    char **argv;     // Array of arguments
    char *instream;  // Input stream
    char *outstream; // Output stream
    char *errstream; // Error stream
    bool append;     // Append to output stream
    bool piped_out;  // Whether this command has output redirected
    bool piped_in;   // Whether this command has input redirected
    bool is_bg;      // Whether this command is to be run in the background
} command_t;

// Holds all commands in a single string
typedef struct __commands
{
    uint32_t num_commands;  // Number of commands
    command_t **commands;   // Array of commands
} commands_t;

// This returns a malloc'd string. Must be freed by caller
char *read_commandline(FILE *stream);

// This returns a malloc'd struct. Must be freed by caller
commands_t *parse_commandline(const char *command_line);

// Free the commands struct
void free_commands(commands_t *commands);

#endif