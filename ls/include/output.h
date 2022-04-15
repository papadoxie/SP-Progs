#pragma once

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// Generic caller for entry print functions
#define PRINT_ENTS(ENTRIES) _Generic ((ENTRIES), \
                struct dirent **: print_direntries, \
                struct stat **: print_stats \
                )(ENTRIES)


void print_direntries(struct dirent **entries);
void print_stats(struct stat **entries);

#endif