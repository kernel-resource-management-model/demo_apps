//
//  logger.h
//  disk_demo
//
//  Created by Stasia on 27.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>

#ifndef __logger_h_
#define __logger_h_
enum LOG_LEVEL {
    FATAL = 0,
    ERROR,
    WARNING,
    DEBUGGING,
    INFO,
    
    __MAX_LEVEL
};

static unsigned int CUR_LOG_LEVEL = __MAX_LEVEL;
static int file = -1;
char *log_filename = "log.txt";

int log_set_parameters(unsigned int cur_log_level, char *log_filename);
int log_add(unsigned int prior, const char * format, ...);
#endif /* logger_h */