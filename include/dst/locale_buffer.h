#ifndef LOCALE_BUFFER_H
#define LOCALE_BUFFER_H
/**
 * @file locale_buffer.h
 * @author Kevin Caldwell
 * @brief Contains Pixel Buffer Functions
 * @details
 * Contains Includes, Macros, Structures and 
 * Functions for loading the neighborhood of a 
 * Pixel from storage into memory.
 * @todo Implement LocaleBuffer_SimpleLoad
 * @todo Implement LocaleBuffer_SmartLoad
 */

#include "constants/typedefs.h"
#include "constants/constants.h"
#include "dst/image.h"

/** \brief Defined in the standard */
#define MAX_PRECEDING_BANDS 16
/** \brief Defines in the standard */
#define MAX_NEIGHBORS 4
/** \brief Assume Pixel takes one buffer space */
#define PIXEL_BUFFER_SPACE 1

/** Length of the Neighbor Index Lookup list */
#define LOCAL_BUFFER_NEIGHBOR_SIZE \
    (MAX_NEIGHBORS + PIXEL_BUFFER_SPACE)

/**  */
#define LOCAL_BUFFER_TOTAL_SIZE \
    (MAX_PRECEDING_BANDS + MAX_NEIGHBORS + PIXEL_BUFFER_SPACE)

/** \brief Array containing order of relative x-coordinates in Buffer */
extern INDEX LocaleBuffer_neighbor_index_x[LOCAL_BUFFER_NEIGHBOR_SIZE];
/** \brief Array containing order of relative y-coordinates in Buffer */
extern INDEX LocaleBuffer_neighbor_index_y[LOCAL_BUFFER_NEIGHBOR_SIZE];


/**
 * \struct
 * \brief
 * The Locale Buffer is designed to store the
 * Neighborhood of the current Pixel being 
 * compressed.
*/
typedef struct LocaleBuffer{
    PIXEL data[LOCAL_BUFFER_TOTAL_SIZE];
} LocaleBuffer;

/**
 * \brief
 * Initializes the values in LocaleBuffer based on the indices 
 * in neighbor_index lookup table
 */
error_t LocaleBuffer_SimpleLoad(LocaleBuffer* buf, image* hIMG);

/**
 * \brief 
 * Initializes the values in LocaleBuffer using values from the 
 * previous buffer. It assumes the LocaleBuffer object persists
 * for each pixel.
 * \todo Finish Implementation (More complex than SimpleLoad)
 */
error_t LocaleBuffer_SmartLoad(LocaleBuffer* buf, image* hIMG);
#endif /* LOCALE_BUFFER_H */
