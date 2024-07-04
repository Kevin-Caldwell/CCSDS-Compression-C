#include "encoder/header.h"

#include <stdio.h>

void PrepareImageMetadata(uint8_t *essential, dim3 img_size)
{
    uint8_t buf;

    essential[0] = 0;
    essential[1] = (uint8_t)((uint16_t)img_size.x >> 8);
    essential[2] = (uint8_t)img_size.x % (1 << 8);

    essential[3] = (uint8_t)((uint16_t)img_size.y >> 8);
    essential[4] = (uint8_t)img_size.y % (1 << 8);

    essential[5] = (uint8_t)((uint16_t)img_size.z >> 8);
    essential[6] = (uint8_t)img_size.z % (1 << 8);

    buf = (uint8_t) !kUnsignedSamples;

#ifdef UNSIGNED_SAMPLES // TODO FIX #DEFINE
    buf = 0;
#else
    buf = 1;
#endif
    Encode(essential, 7, buf, 1);
    Encode(essential, 7, 0, 1);

#if D > 16
    buf = 1;
#else
    buf = 0;
#endif
    Encode(essential, 7, buf, 1);
    Encode(essential, 7, (uint8_t) kD, 4);
    // TODO: Sample Encoding Order
    Encode(essential, 7, 1, 1);

    Encode(essential, 10, 0, 2);
    Encode(essential, 10, B, 3);
    Encode(essential, 10, ENTROPY_CODER, 2);
    Encode(essential, 10, 0, 1);

    Encode(essential, 11, QUANTIZER_FIDELITY_CONTROL, 2);
    Encode(essential, 11, 0, 2);
    Encode(essential, 11, TABLE_COUNT, 4);

    for (int i = 0; i < SIZEOF_HEADER_ESSENTIAL; i++)
    {
        PrintBinary(essential[i]);
    }
    printf("\n");
}

void PreparePredictorMetadata(uint8_t *predicted_metadata)
{
    uint8_t *primary = predicted_metadata;

    Encode(primary, 0, 0, 1);
    Encode(primary, 0, SAMPLE_REP_FLAG, 1);
    Encode(primary, 0, (uint8_t) kP, 4);
    Encode(primary, 0, (uint8_t) kPredictionMode, 1);
    Encode(primary, 0, WEIGHT_EXPONENT_OFFSET_FLAG, 1);

    Encode(primary, 1, kLocalSumType, 2);
    Encode(primary, 1, (uint8_t) kR, 6);

    Encode(primary, 2, (uint8_t) Omega, 4);
    Encode(primary, 2, (uint8_t) (kTInc - 4), 4);

    Encode(primary, 3, (uint8_t) kVMin + 6, 4);
    Encode(primary, 3, (uint8_t) kVMax + 6, 4);

    Encode(primary, 4, WEO_TABLE_FLAG, 1);
    Encode(primary, 4, WEIGHT_INITIALIZATION, 1);
    Encode(primary, 4, WEIGHT_INITIALIZATION_TABLE_FLAG, 1);
    Encode(primary, 4, 0, 5); // TODO 0: Default Weight Initialization Resolution

    uint8_t *sr = predicted_metadata + 5;

    Encode(sr, 0, 0, 5);
    Encode(sr, 0, kResolution, 3);

    Encode(sr, 1, 0, 1);
    Encode(sr, 1, BAND_VARYING_DAMPING_FLAG, 1);
    Encode(sr, 1, DAMPING_TABLE_FLAG, 1);
    Encode(sr, 1, 0, 1);
    Encode(sr, 1, FIXED_DAMPING, 4);

    Encode(sr, 2, 0, 1);
    Encode(sr, 2, BAND_VARYING_OFFSET_FLAG, 1);
    Encode(sr, 2, OFFSET_TABLE_FLAG, 1);
    Encode(sr, 2, 0, 1);
    Encode(sr, 2, FIXED_OFFSET, 4);
}

void PrepareSampleAdaptiveEntropyCoder(uint8_t *entropy_coder_metadata)
{
    Encode(entropy_coder_metadata, 0, UNARY_LENGTH_LIMIT, 5);
    #ifndef S_SPLINT_S
    Encode(entropy_coder_metadata, 0, RESCALING_COUNTER_SIZE, 3);
    Encode(entropy_coder_metadata, 1, INITIAL_COUNT_EXPONENT, 3);
    Encode(entropy_coder_metadata, 1, ACCUMULATOR_INITIALIZATION, 4);
    Encode(entropy_coder_metadata, 1, ACCUMULATOR_INITIALIZATION_TABLE_FLAG, 1);
    #else

    #endif
}
