#pragma once

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <format.h>
#include <argumentParser.h>
#include <helpers.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>

#define PERMISSIONS_LEN 11
#define USERNAME_LEN 10
#define GROUP_LEN 10
#define DATE_LEN 32
#define TIME_LEN 13
#define FILENAME_LEN 255
#define SIZE_LEN 7

void print_normal(struct dirent **entries);
void print_longlisting(struct dirent **entries, const void *args);

#endif