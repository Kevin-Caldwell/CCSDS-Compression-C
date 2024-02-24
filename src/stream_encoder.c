#include "encoder/stream_encoder.h"

void InitializeVarIntStream(VIFS *stream, const char *file_name, uint32_t buffer_size)
{

    stream->bit_ptr = 0;
    stream->byte_ptr = 0;

    stream->fs = F_OPEN(file_name, WRITE);
}

void StreamVarInteger(VIFS *stream, uint32_t data, uint32_t length)
{
    stream->bit_ptr += length;

    stream->buffer[stream->byte_ptr] |= L_SHIFT(data, (BUFFER_REG_SIZE - stream->bit_ptr));

    uint32_t a = (2 * BUFFER_REG_SIZE - stream->bit_ptr);
    if (a < BUFFER_REG_SIZE)
    {
        stream->buffer[stream->byte_ptr + 1] |= (data << a);
    }

    stream->byte_ptr += (stream->bit_ptr >= BUFFER_REG_SIZE);
    stream->bit_ptr %= BUFFER_REG_SIZE;

    if(!(stream->byte_ptr < BUFFER_LENGTH - 1)){
        F_WRITE(stream->buffer, sizeof(uint32_t), BUFFER_LENGTH-1, stream->fs);
        stream->buffer[0] = stream->buffer[stream->byte_ptr];
        for(int i = 1; i < BUFFER_LENGTH; i++){
            stream->buffer[i] = 0;
        }
        stream->byte_ptr = 0;
    }

}

void CloseVarIntegerStream(VIFS* stream){
    F_CLOSE(stream->fs);
}