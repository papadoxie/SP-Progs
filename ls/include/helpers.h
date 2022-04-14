#pragma once

#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

unsigned int num_entries(struct dirent **entries);

// In place sorting
void sort_entries(struct dirent **entries, unsigned int count);

// In place reversing
void reverse_entries(struct dirent **entries, unsigned int count);

#endif