#pragma once

#ifndef __ARGUMENT_PARSER_H__
#define __ARGUMENT_PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <more.h> // To jump into more functionality 😁

// Unused fields in argp struct
#define ARGP_CHILDREN NULL
#define HELP_FILTER NULL
#define ARGP_DOMAIN NULL

// Functions needed for argp
error_t parse_opt(int key, char *arg, struct argp_state *state);

// Variables used for argp
extern const char doc[60];
extern char args_doc[5];
extern struct argp_option options[4];

struct arguments
{
    char filename[255];
};

#endif // __ARGUMENT_PARSER_H__