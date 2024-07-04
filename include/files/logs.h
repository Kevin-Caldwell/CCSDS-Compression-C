/**
 * @file logs.h
 * @brief Logging Execution and Errors in Code.
 * @details
 * Stores logs in the file specified by log_file in global_constants.h
 * Logs the start, end of the program and task, 
 * Logs the success/failure of various checkpoints in the code.
 */
#ifndef LOGS_H
#define LOGS_H

#include "file_IO.h"

#include <time.h>
#include <string.h>

#define log_global_error_handle \
    if(res) {\
    snprintf(log_write_buffer, 100, "Error Code %d was Registered.", res);\
    Log_error(log_write_buffer);\
    return res;\
    }

extern char log_write_buffer[100];

/**
 * @brief
 * Iniitialize the global log object.
 */
void Log_init();

/**
 * @brief
 * Close File logging.
 */
void Log_close();

/**
 * @details
 * Append to the current log. The format of each log line is:
 * [(date) time] UPDATE: {text}
 */
void Log_add(const char *text);

/**
 * @details
 * Log an error, similar to Log_add. Format of Log Line is:
 * [(date) time] ERROR: {text}
 */
void Log_error(char *text);

#endif /* LOGS_H */
