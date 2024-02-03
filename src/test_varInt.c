#include "testing/test_varInt.h"
#include "files/logs.h"
#include "constants/global_constants.h"

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf("|");
    }
}

void print_buffer(VUF* f){

    for(int i = 0; i < BUFFER_LENGTH; i++){
        printf("%d:\t", i);
        printBits(4, f->rw_buffer + i);
        printf("\n");
    }
    // for(int i = BUFFER_LENGTH - 1; i >= 0; i--){
    //     printf("%#10x :%d\n", f->rw_buffer[i], i);
    // }
    printf("BIT INDEX: %d\n", f->bit_index);
    printf("BYTE INDEX: %d\n", f->byte_index);
    printf("\n");
}

int testVUF_Write() {

    #if LOG
    Log_add("Testing VUF File Write");
    #endif

    int array[] = {4, 4, 1, 23, 32, 32, 32, 5, 5, 25};
    int count = 10;

    VUF stream;
    const char* filename = "data/test-images/test.vuf";
    VUF_initialize(&stream, filename, WRITE_BINARY);
    print_buffer(&stream);
    printf("Opened File.\n");

    uint32_t bounce = -1;

    for(int i = 0; i < count; i++){
        printf("Writing %d Digits of %d\n", array[i], bounce);
        VUF_append(&stream, bounce, array[i]);
        print_buffer(&stream);
        bounce = bounce ? 0 : -1;
        
    }

    VUF_close(&stream);
    return 0;
}

int testVUF_Read(){
    int array[] = {4, 4, 1, 23, 32, 32, 32, 5, 5, 25};
    int count = 10;

    VUF stream;
    const char* filename = "data/test-images/test.vuf";
    VUF_initialize(&stream, filename, READ_BINARY);
    print_buffer(&stream);
    printf("Opened File.\n");

    uint32_t bounce = 0;

    for(int i = 0; i < count; i++){
        printf("IDNEEEX %d\n", i);
        printf("INDEX: %d\n", array[i]);
        printf("POPPPED: %x\n", VUF_read_stack(&stream, array[i]));
        print_buffer(&stream);
    }

    VUF_close(&stream);
    return 0;
}