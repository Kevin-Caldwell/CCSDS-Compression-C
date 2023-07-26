#ifndef LOCAL_SUM
#define LOCAL_SUM

#include "constants.h"
#include "sample_representative.h"
#include "cache/cache_predictor.h"

#define LS(hIMG, z, y, x) FindLocalSum(hIMG, z, y, x)
data_t FindLocalSum(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_SUM */
