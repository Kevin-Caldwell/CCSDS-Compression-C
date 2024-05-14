#include "files/logs.h"
#include "constants/global_constants.h"
#include <time.h>
#include <string.h>

char log_file[] = "../data/logs/compressor.logs";
char _time_str[100];

char *_GET_PRINT_TIME()
{
    time_t rt = time((time_t *)NULL);
    strftime(_time_str, 100, "(%x) %X", localtime(&rt));
    return _time_str;
}

file_t *log_fptr;

void Log_init()
{
    if (!log_file)
    {
        return;
    }

    log_fptr = (file_t *)F_OPEN(log_file, APPEND);
    if (log_fptr)
        fprintf(log_fptr, "[%s] Opened Log\n", _GET_PRINT_TIME());
    else
        printf("[%s] Failed to Open Log\n", _GET_PRINT_TIME());
}

void Log_close()
{
    Log_add("Stopped Logging\n");
    F_CLOSE(log_fptr);
}

void Log_add(const char *text)
{
    fprintf(log_fptr, "[%s] UPDATE: %s\n", _GET_PRINT_TIME(), text);
}

void Log_error(char *text)
{
    fprintf(log_fptr, "[%s] ERROR: %s\n", _GET_PRINT_TIME(), text);
}
