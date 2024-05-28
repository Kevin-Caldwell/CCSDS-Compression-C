#include "encoder/encoder_helper_functions.h"

void PrintBinary(/*@unused@*/ uint8_t byte)
{
    #ifndef S_SPLINT_S
    for (int i = 0; i < 8; i++)
    {
        printf("%u", (byte & (1 << 7)) >> 7);
        byte <<= 1;
    }
    #endif
    printf("|");
}

void Encode(uint8_t *destination, uint8_t index, uint8_t data, uint8_t length)
{
    *(destination + index) <<= length;
    *(destination + index) |= (data % (1 << length));
    PrintBinary(*(destination + index));
    printf("%d\n", (int) data);
}