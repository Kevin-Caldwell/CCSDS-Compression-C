#include "files/varIntFile_IO.h"

void VUF_initialize(VUF* stream, const char* file_name, char io_mode){
    stream->io_mode = io_mode;
    stream->bit_index = 0;
    stream->byte_index = 0;
    stream->fs = fopen(file_name, )
}

void VUF_append(VUF* stream, uint32_t* data, uint32_t length){

}

void VUF_rpop(VUF* stream, uint32_t dump, uint32_t length){

}

void VUF_close(VUF* stream){

}

void FILL_BUFFER(VUF* stream){

}