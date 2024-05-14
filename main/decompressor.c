
#include "decompressor/reconstructor.h"
#include "decompressor/decoder.h"
#include <string.h>

char DEBUG = 0;

int main(int argInt, char **argS)
{
    if (argInt > 1)
    {
        if (!strcmp(argS[1], "reconstruct"))
        {
            TestReconstructor(argS[2]);
        }
        else if (!strcmp(argS[1], "decode"))
        {
            TestDecoder(argS[2]);
        }
    }
    else
    {
        TestReconstructor("../data/test-images/TEST_100x100x100_0.csv");
    }
    return 0;
}