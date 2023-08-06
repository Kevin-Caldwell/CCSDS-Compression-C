#ifndef ENCODER_HELPER_FUNCTIONS_H
#define ENCODER_HELPER_FUNCTIONS_H

#include <inttypes.h>

void PrintBinary(uint8_t byte){
    for(int i = 0; i < 8; i++){
        printf("%u", (byte & (1 << 7)) >> 7);
        byte <<= 1;
    }
    printf("|");

}

void Encode(uint8_t* destination, uint8_t index, uint8_t data, uint8_t length){
    *(destination + index) <<= length;
    *(destination + index) |= (data % (1 << length));
    PrintBinary(*(destination + index));
    printf("%d\n", data);
}

#endif /* ENCODER_HELPER_FUNCTIONS_H */
