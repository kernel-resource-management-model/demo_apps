//
//  logger.c
//  disk_demo
//
//  Created by Stasia on 27.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include "logger.h"

int log_set_parameters(unsigned int cur_log_level, char *log_filename) {
    if (cur_log_level >= __MAX_LEVEL) {
        perror("Forbidden log level");
        return ERROR;
    }
    if (file != -1)
        close(file);
    CUR_LOG_LEVEL = cur_log_level;
    if ((file = open(log_filename, O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0) {
       	perror("Can't open file");
        return errno;
    }
    return 0;
}

#define log_exit(str) { perror(str); if (message) free(message); if(log) free(log); close(file); return errno; }
int log_add(unsigned int prior, const char * format, ...) {
    
    if (file < 0)
        if ((file = open(log_filename, O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0) {
            perror("Can't open log file");
            return errno;
        }
    if (prior > CUR_LOG_LEVEL)
        return 0;
    
    unsigned long int tm_size, lvl_size, mess_size;
    time_t *tp;
    va_list marker;
    char *tm;
    char *message = NULL;
    char *log = NULL;
    
    if ((tp = (time_t *)malloc(sizeof(time_t))) == NULL)
        log_exit("Not enough memory");
    
    
    time(tp);
    tm = ctime(tp);
    free(tp);
    tm_size = strlen(tm);
    tm[tm_size-1] = '\t';
    
    
#define PRINT_LOG_LEVEL(lvl) #lvl
    char *PrintLogLevel[__MAX_LEVEL] = {
        PRINT_LOG_LEVEL(FATAL:\t),
        PRINT_LOG_LEVEL(ERROR:\t),
        PRINT_LOG_LEVEL(WARNING:\t),
        PRINT_LOG_LEVEL(DEBUG:\t),
        PRINT_LOG_LEVEL(INFO:\t)
    };
    
    lvl_size = strlen(PrintLogLevel[prior]);
    
    if ((message = (char *)malloc(sizeof(char)*strlen(format))) == NULL)
        log_exit("Not enough memory");
    
    va_start(marker, format);
    vasprintf(&message, format, marker);
    va_end(marker);
    mess_size = strlen(message);
    
    if ((log = (char *)malloc(sizeof(char)*(mess_size+tm_size+lvl_size))) == NULL)
        log_exit("Not enough memory");
    strcat(log, tm);
    strcat(log, PrintLogLevel[prior]);
    strcat(log, message);
    free(message);
    message = NULL;
#undef PRINT_LOG_LEVEL
    
    if (write(file, log, strlen(log)) < 0)
        log_exit("Writing failed");
    free(log);
    return 0;
}
#undef log_exit