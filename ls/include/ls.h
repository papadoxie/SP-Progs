#pragma once

#ifndef __LS_H__
#define __LS_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirmanager.h>
#include <argumentParser.h>
#include <output.h>
#include <helpers.h>

#define ERROR_MSG_LEN 512

int ls(const void *args);

#endif // __LS_H__