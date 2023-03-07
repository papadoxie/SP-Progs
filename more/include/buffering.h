#pragma once

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdlib.h>
#include <format.h>
#include <sigwinch.h>
#include <winchInterface.h>
//! Remove after debugging
#include <stdio.h>

#define TEXT_ROWS window.rows - 1
#define TEXT_COLS window.cols - 8

extern unsigned int lineNumber;
extern char **outputBuffer;

#endif