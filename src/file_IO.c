#include "files/file_IO.h"
#include "files/logs.h"

const char *file_modes_str[] = {"r", "w", "a", "r+", "w+", "a+"};

int Initialized()
{
    return 0;
}

/*@null@*/
file_t *F_OPEN(const char *file_name, FileMode open_mode)
{
    return (file_t *) /*@access FILE@*/ fopen(file_name, file_modes_str[open_mode]);
}

size_t F_WRITE(const void *write_ptr, size_t member_size, size_t member_count, file_t *file_ptr)
{
    return fwrite(write_ptr, member_size, member_count, (FILE *)file_ptr);
}

size_t F_READ(void *destination, size_t size, size_t arr_length, file_t *file_stream)
{
    return fread(destination, size, arr_length, (FILE *)file_stream);
}

int F_CLOSE(file_t *stream)
{
    return fclose((FILE *)stream);
}

int F_EMPTY(/*@unused@*/ file_t *stream)
{
    return 0;
}

int F_SEEK(
    file_t *stream,
    long int offset)
{
    return fseek((FILE *)stream, offset, SEEK_SET);
}