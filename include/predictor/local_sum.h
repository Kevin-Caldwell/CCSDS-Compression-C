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
#define LS(hIMG, z, y, x) FindLocalSum(hIMG, z, y, x)

/**
 * @brief Local Sum Calculations using direct Image Access
 * @note Soon Deprecated.
 * @warning Direct Image Access
 */
uint32_t FindLocalSum(image *hIMG, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_SUM_H */
