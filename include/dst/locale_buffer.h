#ifndef LOCALE_BUFFER_H
#define LOCALE_BUFFER_H
/**
 * @file locale_buffer.h
 * @brief Contains Pixel Buffer Functions
 * @details
 * Contains Includes, Macros, Structures and 
 * Functions for loading the neighborhood of a 
 * Pixel from storage into memory.
 * @todo Implement LocaleBuffer_SimpleLoad
 * @todo Implement LocaleBuffer_SmartLoad
 * @todo Implement LocaleBuffer_FetchPixel
 */

#include "dst/image.h"

#define LocaleBuffer_Load LocaleBuffer_SimpleLoad

/** @brief Defined in the standard */
#define MAX_PRECEDING_BANDS 16
/** @brief Defines in the standard */
#define MAX_NEIGHBORS 4
/** @brief Assume Pixel takes one buffer space */
#define PIXEL_BUFFER_SPACE 1

/** @brief Length of the Neighbor Index Lookup list */
#define LOCAL_BUFFER_NEIGHBOR_SIZE \
    (MAX_NEIGHBORS + PIXEL_BUFFER_SPACE)

/** @brief Total Buffer Length */
#define LOCAL_BUFFER_TOTAL_SIZE \
    (MAX_PRECEDING_BANDS + MAX_NEIGHBORS + PIXEL_BUFFER_SPACE)

/** @brief Array containing order of relative x-coordinates in Buffer */
extern const int LocaleBuffer_neighbor_index_x[LOCAL_BUFFER_NEIGHBOR_SIZE];
/** @brief Array containing order of relative y-coordinates in Buffer */
extern const int LocaleBuffer_neighbor_index_y[LOCAL_BUFFER_NEIGHBOR_SIZE];


/**
 * @brief Stores Pixel Neighborhood in Buffer
 * @details
 * The Locale Buffer is designed to store the
 * Neighborhood of the current Pixel being 
 * compressed.
*/
typedef struct LocaleBuffer{
    PIXEL data[LOCAL_BUFFER_TOTAL_SIZE];
} LocaleBuffer, LBuf;

/**
 * @brief
 * Initializes the values in LocaleBuffer based on the indices 
 * in neighbor_index lookup table
 */
error_t LocaleBuffer_SimpleLoad(LocaleBuffer* buf, image* hIMG, dim3 index);
/**
 * @brief 
 * Initializes the values in LocaleBuffer using values from the 
 * previous buffer. It assumes the LocaleBuffer object persists
 * for each pixel.
 * \todo Finish Implementation (More complex than SimpleLoad)
 */
error_t LocaleBuffer_SmartLoad(LocaleBuffer* buf, image* hIMG, dim3 index);

/**
 * @brief 
 * Fetches Data from the respective Offset off the active image coordinates.
 * @details 
 * If offset is (0, 0, 0), return the value of active pixel data.
 * If offset is on previous predictor bands, it returns the element at
 * index: PIXEL_BUFFER_SPACE + MAX_NEIGHBORS + offset_z
 * If offset is a neighboring pixel, it searches in indices in range:
 * [PIXEL_BUFFER_SPACE, PIXEL_BUFFER_SPACE + MAX_NEIGHBORS] with the 
 * respective offset search in neighbor_offset_{x and y} within the 
 * indices [0, LOCAL_BUFFER_NEIGHBOR_SIZE]
 */
error_t LocaleBuffer_FetchPixel(
    LocaleBuffer* buf,
    PIXEL* data,
    DIM offset_x, 
    DIM offset_y, 
    DIM offset_z
);
PIXEL LocaleBuffer_FetchPixel_Direct(LocaleBuffer* buf, DIM z, DIM y, DIM x);


void print_locale_buffer(LocaleBuffer* pixel_buffer);

static inline BOOL _index_within_bounds(DIM x, DIM y, DIM z, dim3 s){
    return (0 <= x && x < s.x) && (0 <= y && y < s.y) && (0 <= z && z < s.z);
}
#endif /* LOCALE_BUFFER_H */
