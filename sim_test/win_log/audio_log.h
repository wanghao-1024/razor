/*-
* Copyright (c) 2017-2018 Razor, Inc.
*   All rights reserved.
*
* See the file LICENSE for redistribution information.
*/

#ifndef __AUDIO_LOG_H_
#define __AUDIO_LOG_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*windowsϵͳ�¼򵥵�logģ��*/
int         open_win_log(const char* filename);

int         log_win_write(int level, const char* file, int line, const char* fmt, va_list vl);

void        close_win_log();

#ifdef __cplusplus
}
#endif
#endif




