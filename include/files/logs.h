#ifndef LOGS_H
#define LOGS_H

#include "file_IO.h"

void Log_init();

void Log_close();

void Log_add(const char* text);

void Log_error(char* text);

#endif /* LOGS_H */
