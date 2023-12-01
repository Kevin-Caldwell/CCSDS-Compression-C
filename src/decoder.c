#include "decompressor/decoder.h"

#include <inttypes.h>
#include <stdio.h>
#include "stream_encoder.h"
#include "math_functions.h"

int K = 0; // CLIP(ACCUMULATOR_INITIALIZATION_CONSTANT, 0, MIN(D-2, 14));
uint U_max = CLIP(UNARY_LENGTH_LIMIT, 8, 32);
int Gamma1 = 1;

void increment_xyz(int *x, int *y, int *z, DIM Nx, DIM Ny, DIM Nz) {
    if (x < Nx - 1) 
    {
        (*x)++;
        return;
    } 
    else if (y < Ny - 1) 
    {
        *x = 0;
        (*y)++;
        return;
    }
    else if (z < Nz - 1) 
    {
        *x = 0;
        *y = 0;
        (*z)++;
        return
    }
    return
}


void Decoder_DecodeBody(image* predicted_samples, const char* file_name){
    int K_ZPRIME = 0;
    if (K <= 30 - D)
    {
        K_ZPRIME = K;
    }
    else
    {
        K_ZPRIME = 2 * K + D - 30;
    }
    dim3 sz = predicted_samples->size;

    uint32_t gamma;
    uint32_t epsilon_z;
    uint32_t sample;
    uint32_t k_z;

    FILE *log = fopen("../data/logs/c-decoder-debug.LOG", "w");
    /* Need to Load bitstream */
    VIFS stream;

    time_t start = time(NULL);
    while (/*stream not empty*/) {
        if (x == 0 && y == 0) {
            gamma = BPOW(Gamma1);
            epsilon_z = ((3 * (uint)BPOW(K_ZPRIME + 6) - 49) * gamma) / BPOW(7);
            // Then read the first code word, which has len D
            ReadStreamVarInteger(&stream, &sample, D);
            SetPixel(predicted_samples, x, y, z, sample);
            increment_xyz(&x, &y, &z, sz.x, sz.y, sz.z)
            continue;
        }

        if (2 * gamma > epsilon_z + (int)(((float)49 * gamma) / BPOW(7))) {
            k_z = 0;
        } else {
            for (int i = D; i >= 0; i--)
            {
                if ((gamma * BPOW(i)) <= (epsilon_z + ((49u * gamma) >> 7)))
                {
                    k_z = i;
                    break;
                }
            }
        }

        // Inverse GolombPowerTwo
        int bit;
        uint32_t j;
        uint32_t q = 0;
        while (/* Stream not empty && */) {
            ReadStreamVarInteger(&stream, &bit, 1);
            if (bit == 1) 
                break;

            q++;
            if (q == U_max) 
                break;
        }

        if (q == U_max) {
            ReadStreamVarInteger(&stream, &sample, D);
        }
        else {
            if (k_z == 0) {
                sample = 0;
            } else {
                ReadStreamVarInteger(&stream, &sample, k_z)
            }
            sample += q * BPOW(k_z);
        }

        SetPixel(predicted_samples, x, y, z, sample);

        if (!(x == sz.x - 1 && y == sz.y - 1 && z == sz.z - 1)) {
            increment_xyz(&x, &y, &z, sz.x, sz.y, sz.z)
        } 


        if (gamma < BPOW(GAMMA_STAR) - 1) {
            epsilon_z += data;
            gamma++;
        }
        else if (gamma == BPOW(GAMMA_STAR) - 1) {
            epsilon_z = (epsilon_z + data + 1) / 2;
            gamma = (gamma + 1) / 2;
        }
    }

    CloseVarIntegerStream(&stream);
    time_t end = time(NULL);
}

void TestDecoder(char* filename) {
    printf("Testing Decoder...\n");
    /* TODO */
}
