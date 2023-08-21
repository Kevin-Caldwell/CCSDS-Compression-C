#ifndef BODY_H
#define BODY_H

#include <inttypes.h>
#include "math/math_functions.h"
#include "dst/image.h"
#include "constants/encoder_constants.h"

int K = CLIP(ACCUMULATOR_INITIALIZATION_CONSTANT, 0, MIN(D-2, 14));
uint U_max = CLIP(UNARY_LENGTH_LIMIT, 8, 32);
int Gamma1 = BPOW(8);

uint32_t GolombPowerTwo(uint16_t j, uint16_t k){
    uint32_t u,r;
    if(j / (BPOW(k)) < U_max){
        
    } else{

    }

    return u + r;
}

void Accumulator(uint32_t x, uint32_t y, uint32_t z);

uint InitAccumulatorValue(uint32_t z){
    uint k_prime = (K <= 30-D) ? K : (2 * K + D - 30);
    return (3 * BPOW(k_prime + 6) - 49) * Gamma1;
}

int Encoder(image* hIMG){
    int counter = BPOW(INITIAL_COUNT_EXPONENT);
    //int accumulator = (3 * BPOW());
    dim3 sz = hIMG->size;

    for(int z = 0; z < sz.z; z++){
        for(int y = 0; y < sz.y; y++){
            for(int x = 0; x < sz.x; x++){
                if(x == 0 && y == 0){
                    int code = 0;
                }
            }
        }
    }
}

#endif /* BODY_H */
