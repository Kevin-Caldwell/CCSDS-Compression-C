#include "encoder/body.h"
#include <time.h>
#include "encoder/encoder_helper_functions.h"

int K = 0; // CLIP(ACCUMULATOR_INITIALIZATION_CONSTANT, 0, MIN(D-2, 14));
uint U_max = CLIP(UNARY_LENGTH_LIMIT, 8, 32);
int Gamma1 = 1;

GolombInt GolombPowerTwo(uint16_t j, uint16_t k)
{
    uint32_t u;
    uint len = 0;
    uint32_t div = j / (BPOW(k));
    if (div < U_max)
    {

        u <<= div;
        u <<= 1;
        u |= 1;
        u <<= k;
        uint mask = (1 << k) - 1;
        u |= (j & mask);
        len = u ? (div + 1 + k) : 1;
    }
    else
    {

        u <<= UNARY_LENGTH_LIMIT;
        u <<= D;
        uint mask = (1 << k) - 1;
        u |= j;
        len = k + D;
    }

    return (GolombInt){u, len};
}

uint InitAccumulatorValue(uint32_t z)
{
    uint k_prime = (K <= 30 - D) ? K : (2 * K + D - 30);
    return (3 * BPOW(k_prime + 6) - 49) * Gamma1;
}

int EncodeBody(image *hIMG, const char *file_name, const char *write_mode, int buffer_size)
{
    int K_ZPRIME = 0;
    if (K <= 30 - D)
    {
        K_ZPRIME = K;
    }
    else
    {
        K_ZPRIME = 2 * K + D - 30;
    }
    dim3 sz = hIMG->size;

    uint32_t gamma;
    uint32_t epsilon_z;
    uint32_t codeword;
    uint32_t k_z;

    FILE *log = fopen("../data/logs/c-encoder-debug.LOG", "w");

    VIFS stream;
    InitializeVarIntStream(&stream, file_name, buffer_size);
    long int len = 0;

    time_t start = time(NULL);
    for (int z = 0; z < sz.z; z++)
    {
        for (int y = 0; y < sz.y; y++)
        {
            for (int x = 0; x < sz.x; x++)
            {

                uint16_t data = GetPixel(hIMG, x, y, z);
                if (x == 0 && y == 0)
                {
                    gamma = BPOW(Gamma1);
                    epsilon_z = ((3 * (uint)BPOW(K_ZPRIME + 6) - 49) * gamma) / BPOW(7);
                    StreamVarInteger(&stream, data, D);
                    len += D;
                    fprintf(log, "%u:%d,%d\n", data, D, k_z);
                    continue;
                }

                if (2 * gamma > epsilon_z + (int)(((float)49 * gamma) / BPOW(7)))
                {
                    k_z = 0;
                }
                else
                {
                    for (int i = D; i >= 0; i--)
                    {
                        if ((gamma * BPOW(i)) <= (epsilon_z + ((49u * gamma) >> 7)))
                        {
                            k_z = i;
                            break;
                        }
                    }
                }

                GolombInt res = GolombPowerTwo(data, k_z);
                len += res.length;
                fprintf(log, "(%d, %d, %d) %u:%d, %d, %d, %d\n", x, y, z, res.data, res.length, k_z, gamma, epsilon_z);
                StreamVarInteger(&stream, res.data, res.length);

                if (gamma < BPOW(GAMMA_STAR) - 1)
                {
                    epsilon_z += data;
                    gamma++;
                }
                else if (gamma == BPOW(GAMMA_STAR) - 1)
                {
                    epsilon_z = (epsilon_z + data + 1) / 2;
                    gamma = (gamma + 1) / 2;
                }
            }
        }
        time_t time_elapsed = time(NULL) - start;
        time_t time_left = time_elapsed * (Nz - z - 1) / (z + 1);
        printf("\rEncoded %d/%d of Image. (%ld seconds Elapsed, %ld seconds Left)", (int)(z + 1), (int)hIMG->size.x, time_elapsed, time_left);
        fflush(stdout);
    }
    CloseVarIntegerStream(&stream);
    time_t end = time(NULL);
    printf("\n%d seconds for image Encoding.\n", (int)(end - start));
    printf("%ld / %ld bytes=%2.f%% Compression\n", len / 8, (long)((float) Nx * Ny * Nz * D / 8), (1 - ((float)len / ((float) Nx * Ny * Nz * D))) * 100);

    return 0;
}