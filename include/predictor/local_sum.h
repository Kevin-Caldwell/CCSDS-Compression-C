/**
 * @file local_sum.h
 *
 * @brief Functions for finding Local Sum
 */

#ifndef LOCAL_SUM_H
#define LOCAL_SUM_H

#include "sample_representative.h"

/** 
 * @brief Local Sum Shorthand 
 * @warning Direct Image Access
*/
#define LS(hIMG, s, z, y, x) FindLocalSum(hIMG, s, z, y, x)
#define L_LS(hIMG, z, y, x) L_FindLocalSum(hIMG, z, y, x)

/**
 * @brief Local Sum Calculations using direct Image Access
 * @note Soon Deprecated.
 * @warning Direct Image Access
 */
uint32_t FindLocalSum(LBuf *hIMG, dim3 s, INDEX z, INDEX y, INDEX x);
uint32_t L_FindLocalSum(image *hIMG, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_SUM_H */
