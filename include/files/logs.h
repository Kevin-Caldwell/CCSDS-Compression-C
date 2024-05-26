#ifndef LOGS_H
#define LOGS_H

#include "file_IO.h"

#include "constants/global_constants.h"
#include <time.h>
#include <string.h>


void Log_init();

void Log_close();

void Log_add(const char *text);

void Log_error(char *text);

#endif /* LOGS_H */
