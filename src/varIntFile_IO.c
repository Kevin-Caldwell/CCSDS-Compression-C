#include "files/varIntFile_IO.h"

// #ifndef L_SHIFT
// #define L_SHIFT(x, s) (s == 32 ? 0 : (s < 0 ? (unsigned) x >> -s : (unsigned) x << s))
// #endif

char *file_modes_arguments[] = {"rb", "wb"};

void _VUF_Clean(VUF *stream, char full)
{
    int start = !full;
    for(; start < BUFFER_LENGTH; start++)
    {
        stream->rw_buffer[start] = 0;
    }
}

error_t VUF_initialize(VUF *stream, const char *file_name, file_modes io_mode)
{
    // File IO Constants
    stream->io_mode = io_mode;
    stream->fs = F_OPEN(file_name, io_mode);

#if LOG
    if (!stream->fs)
    {
        Log_error("Unable to open File");
        return FILE_NON_EXISTENT;
    }
#endif
    // printf("stream opening: %x, %d, %s.\n", (unsigned int) stream->fs, (unsigned) stream->io_mode, file_modes_arguments[stream->io_mode]);

    if (io_mode == WRITE_BINARY)
    {
        // Initialize Empty Buffer for write requests
        stream->bit_index = 0;
        stream->byte_index = 0;
        _VUF_Clean(stream, 1);
    }
    else if (io_mode == READ_BINARY)
    {
        // Initialize Full Buffer for faster read requests
        F_READ(stream->rw_buffer, BUFFER_SIZE, BUFFER_LENGTH, stream->fs);
        stream->bit_index = 0;
        stream->byte_index = 0;
    }

    return RES_OK;
}

error_t VUF_append(VUF *stream, uint32_t data, uint32_t length)
{
    stream->bit_index += length; // Shift Bit Pointer
    uint32_t clean = (data
                      << (BUFFER_SIZE - length)) >>
                     (BUFFER_SIZE - length);

    stream->rw_buffer[stream->byte_index] |=
        L_SHIFT(clean, (BUFFER_SIZE - stream->bit_index));

    // Variable Bit Encoding
    if ((stream->bit_index >= BUFFER_SIZE))
    {
        uint32_t shift_index = 2 * BUFFER_SIZE - stream->bit_index;
        stream->rw_buffer[++stream->byte_index] |= L_SHIFT(data, shift_index);
        stream->bit_index -= BUFFER_SIZE;
    }

    // Fill Check
    if (stream->byte_index == BUFFER_LENGTH - 1)
    {
        // Write entire filled buffer to File
        F_WRITE(stream->rw_buffer, BUFFER_SIZE, BUFFER_LENGTH - 1, stream->fs);

        // Pull remaining data from Tail to Head
        stream->rw_buffer[0] = stream->rw_buffer[stream->byte_index];
        stream->byte_index = 0;

        _VUF_Clean(stream, 0);
    }

    return RES_OK;
}

uint32_t VUF_read_stack(VUF *stream, uint32_t length)
{
    uint32_t varInt = stream->rw_buffer[stream->byte_index] << stream->bit_index;
    stream->bit_index += length;
    varInt >>= (BUFFER_SIZE - length);
    
    #ifdef ARM_COMPILE
    printf("Reading, %08lX\n", varInt);
    #else 
    printf("Reading, %08X\n", varInt);
    #endif

    if (stream->bit_index >= BUFFER_SIZE)
    {
        stream->bit_index -= BUFFER_SIZE;
        stream->byte_index++;

        varInt += stream->rw_buffer[stream->byte_index] >> ((2 * BUFFER_SIZE - length) % BUFFER_SIZE);
    }

    if (stream->byte_index >= BUFFER_LENGTH - 1)
    {
        stream->rw_buffer[0] = stream->rw_buffer[BUFFER_LENGTH - 1];
        stream->byte_index = 0;
        F_READ(stream->rw_buffer + 1, BUFFER_SIZE, BUFFER_LENGTH, stream->fs);
    }

    #ifdef ARM_COMPILE
    printf("%08lX\n", varInt >> (BUFFER_SIZE - length));
    #else
    printf("%08X\n", varInt >> (BUFFER_SIZE - length));
    #endif

    return varInt;
}

error_t VUF_close(VUF *stream)
{
    stream->bit_index = 0;
    stream->byte_index = 0;
    F_CLOSE(stream->fs);

    return RES_OK;
}