#pragma once

#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/ioctl.h>

#define STDOUT 1

unsigned int num_entries(struct dirent **entries);

// Remove hidden files
void filter_hidden(struct dirent **entries, unsigned int count);

// In place sorting
void sort_entries(struct dirent **entries, unsigned int count);

// In place reversing
void reverse_entries(struct dirent **entries, unsigned int count);

// Get number of columns in terminal
unsigned int get_term_width();

// Get max length of a directory name in entries
unsigned int get_max_dirname_length(struct dirent **entries);

#endif