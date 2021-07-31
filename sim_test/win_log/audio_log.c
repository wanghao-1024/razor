/*-
* Copyright (c) 2017-2018 Razor, Inc.
*   All rights reserved.
*
* See the file LICENSE for redistribution information.
*/

#if WIN32
#include <direct.h>
#pragma warning(disable: 4996)
#endif

#include "cf_platform.h"
#include <time.h>
#include "audio_log.h"
#include "gettimeofday.h"

#define PATH_MAX_SIZE 1024

typedef struct log_file_s
{
    FILE*                           fp;
    char                            filename[PATH_MAX_SIZE];
    su_mutex                        mutex;
} log_file_t;

static log_file_t* log_file = NULL;

#define WT_SPIN_COUNT 4000

const char* get_time_str(char* date_str)
{
    struct tm tm_now;
    struct timeval tv;
    gettimeofday(&tv, NULL);

    time_t now = tv.tv_sec;
    localtime_s(&tm_now, &now);


    sprintf(date_str, "%04d-%02d-%02d %02d:%02d:%02d.%3ld", tm_now.tm_year + 1900, tm_now.tm_mon + 1, tm_now.tm_mday,
            tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec, tv.tv_usec / 1000);

    return date_str;
}

static char* get_fullexepath()
{
    static char buffer[MAX_PATH] = { 0 };
    return _getcwd(buffer, MAX_PATH);
}

int open_win_log(const char* filename)
{
    if (log_file != NULL || filename == NULL)
        return -1;

    log_file = (log_file_t*)calloc(1, sizeof(log_file_t));

    char* path = get_fullexepath();
    if (path == NULL)
        return -1;

    sprintf(log_file->filename, "%s\\%s", path, filename);

    log_file->fp = fopen(log_file->filename, "w");
    if (log_file->fp == NULL)
    {
        printf("open %s failed!\r\n", log_file->filename);
        return -1;
    }

    /*��ʼ��spin mutex��*/
    log_file->mutex = su_create_mutex();
    return 0;
}

void close_win_log()
{
    if (log_file != NULL && log_file->fp != NULL)
    {
        fflush(log_file->fp);
        fclose(log_file->fp);
        log_file->fp = NULL;

        if (log_file->mutex != NULL)
        {
            su_destroy_mutex(log_file->mutex);
            log_file->mutex = NULL;
        }

        free(log_file);
        log_file = NULL;
    }
}

static const char* get_file_name(const char* pathname)
{
    if (pathname == NULL)
        return pathname;

    int32_t size = strlen(pathname);

    char* pos = (char*)pathname + size;
    while (*pos != '\\' && pos != pathname)
        pos--;

    if (pos == pathname)
        return pathname;
    else
        return pos + 1;
}

#define DATE_STR_SIZE 64
int log_win_write(int level, const char* file, int line, const char* fmt, va_list vl)
{
    char date_str[DATE_STR_SIZE];
    if (log_file != NULL && log_file->fp != NULL)
    {
        su_mutex_lock(log_file->mutex);
        fprintf(log_file->fp, "%s %s:%d ", get_time_str(date_str), get_file_name(file), line);
        vfprintf(log_file->fp, fmt, vl);
        su_mutex_unlock(log_file->mutex);
        fflush(log_file->fp);
    }

    return 0;
}



