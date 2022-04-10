#pragma once

#ifndef __ARGUMENT_PARSER_H__
#define __ARGUMENT_PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <argp.h>

// Unused fields in argp struct
#define ARGP_CHILDREN NULL
#define HELP_FILTER NULL
#define ARGP_DOMAIN NULL

// Functions needed for argp
error_t parse_opt(int key, char *arg, struct argp_state *state);

// Variables used for argp
const char *argp_program_version = "more 0.1.0";
const char *argp_program_bug_address = "nofilqasim@gmail.com";
const char doc[] = "more -- a program to display a file one screenful at a time";
char args_doc[] = "FILE";
struct argp_option options[] =
    {
        {0, 0, 0, 0, "Output options:", 1},
        {"filename", 777, "FILENAME", 0, "The name of the file to display", 1},
        {"version", 'v', 0, 0, "output version information", 1},
        {0, 0, 0, 0, 0, 0}};

struct arguments
{
    char filename[255];
};

#endif // __ARGUMENT_PARSER_H__