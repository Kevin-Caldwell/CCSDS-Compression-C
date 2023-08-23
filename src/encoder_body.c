#include "encoder/body.h"

#include "encoder/encoder_helper_functions.h"

int K = 14;//CLIP(ACCUMULATOR_INITIALIZATION_CONSTANT, 0, MIN(D-2, 14));
uint U_max = CLIP(UNARY_LENGTH_LIMIT, 8, 32);
int Gamma1 = 8;

GolombInt GolombPowerTwo(uint16_t j, uint16_t k){
    uint32_t u;
    uint len = 0;
    uint32_t div = j / (BPOW(k));
    if(div < U_max){

        u <<= div;
        u <<= 1;
        u |= 1;
        u <<= k;
        uint mask = (1 << k) - 1;
        u |= (j & mask);
        len = div + 1 + k;
    } else{

        u <<= UNARY_LENGTH_LIMIT;
        u <<= D;
        uint mask = (1 << k) - 1;
        u |= j;
        len = k + D;
    }

    return (GolombInt) {u, len};
}

uint InitAccumulatorValue(uint32_t z){
    uint k_prime = (K <= 30-D) ? K : (2 * K + D - 30);
    return (3 * BPOW(k_prime + 6) - 49) * Gamma1;
}


int EncodeBody(image* hIMG, const char* file_name, const char* write_mode, int buffer_size){

    int K_ZPRIME = 2 * K + D - 30;
    dim3 sz = hIMG->size;

    uint32_t gamma;
    uint32_t epsilon_z;
    uint32_t codeword;
    uint32_t k_z;

    VIFS stream;
    InitializeVarIntStream(&stream, file_name, buffer_size);

    for(int z = 0; z < sz.z; z++){
        for(int y = 0; y < sz.y; y++){
            for(int x = 0; x < sz.x; x++){
                if(x == 0 && y == 0){
                    gamma = BPOW(Gamma1);
                    epsilon_z = ((3 * BPOW(K_ZPRIME + 6) - 49) * gamma) >> 7;
                    StreamVarInteger(&stream, GetPixel(hIMG, x,y,z), D);
                    continue;
                }

                if(2 * gamma > epsilon_z + ((49 * gamma) << 7)){
                    k_z = 0;
                } else{
                    for(int i = D-1; i > 0; i++){
                        if(gamma * BPOW(i) <= epsilon_z + ((49 * gamma) << 7)){
                            k_z = i;
                            break;
                        }
                    }
                }

                GolombInt res = GolombPowerTwo(GetPixel(hIMG, x, y, x), k_z);
                StreamVarInteger(&stream, res.data, res.length);
                

                if(gamma < BPOW(GAMMA_STAR) - 1){
                    epsilon_z += GetPixel(hIMG, x,y,z);
                    gamma++;
                } else if (gamma == BPOW(GAMMA_STAR) - 1)
                {
                    epsilon_z = (epsilon_z + GetPixel(hIMG, x,y,z) + 1) / 2;
                    gamma = (gamma + 1) / 2;
                }
                

                
            }
        }
    }
    CloseStreamVarInteger(&stream);

    return 0;
}