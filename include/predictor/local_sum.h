/**
 * local_sum.h
 * @author @Kevin-Caldwell
 * 
 * Functions for finding Local Sum
*/

#ifndef LOCAL_SUM_H
#define LOCAL_SUM_H

#include "constants/constants.h"
#include "sample_representative.h"
#include "cache/cache_predictor.h"

#define LS(hIMG, z, y, x) FindLocalSum(hIMG, z, y, x)
uint32_t FindLocalSum(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_SUM_H */
