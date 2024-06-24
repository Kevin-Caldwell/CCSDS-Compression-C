/**
 * @file linear_algebra.h
 * @authors Kevin Caldwell BrianShTsoi
 * @brief Skeleton File for Generin Vector Operations.
 * @details
 * Skeleton File for Generic Vector Operations.
 *
 * Features
 *  Initialization
 *  Deletion
 *  Addition
 *  Subtraction
 *  Scalar Product
 *  Inner Product (Dot Product)
 *
 * Uses
 *  Local Difference Vector
 *  Weight Vector
 *
 * Dependencies
 *  constants.h
 *  math_functions.h
 */

#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include "constants/typedefs.h"
#include "constants/constants.h"
#include "math_functions.h"


/**
 * @brief Initializes the vector
 * @deprecated Dynamic Memory Allocation not supported anymore.
 * @param v Dereferenced Address of Memory to initialize
 * @param len Length of Vector
 * @returns Success if Memory successfully allocated.
 * 
 */
error_t InitVector(int32_t **v, UINT len);

/**
 * @brief Deletes a Dynamically Allocated Vector.
 * @deprecated Dynamic Memory Allocation not supported anymore.
 * @param v The address of the vector to initialize.
 * @returns RES_OK
 */
error_t DeleteVector(data_t *v);

/**
 * @brief Adds two vectors with length size
 * @details 
 * Adds 2 vectors sequentially, memory overlap not supported.
 * @param v1 The first vector to be added
 * @param v2 The second vector to be added
 * @param res Address of the result vector
 * @param size Vector Length
 * @param RES_OK 
 */
error_t AddVectors(data_t *v1, data_t *v2, data_t *res, UINT size);

/**
 * @brief Subtracts two vectors with length size
 * @details 
 * Calculates v1-v2 sequentially, memory overlap not supported.
 * @param v1
 * @param v2
 * @param res Address of result vector
 * @param size Vector Length
 * @param RES_OK 
 */
error_t SubtractVectors(data_t *v1, data_t *v2, data_t *res, UINT size);

/**
 * @brief Finds the Inner Product of v1 and v2
 * @details 
 * Calculates v1 dot v2 sequentially.
 * @param v1
 * @param v2
 * @param res Address of result vector
 * @param size Vector Length
 * @param RES_OK 
 */
int64_t InnerProduct(int32_t *v1, int32_t *v2, UINT size);

/**
 * @brief Calculates scalar * v
 * @details 
 * Calculates scalar * v sequentially.
 * @param v
 * @param scalar
 * @param res Address of the result vector
 * @param size Vector Length
 * @param RES_OK 
 */
error_t ScalarProduct(data_t *v, data_t scalar, data_t *res, UINT size);

#define AddToVector(v, other, size) AddVectors(v, other, v, size)
#define SubtractFromVector(v, other, size) SubtractVectors(v, other, v, size)
#define ScalarProduct_C(v, other, size) ScalarProduct(v, other, v, size)

#endif /* LINEAR_ALGEBRA_H */
