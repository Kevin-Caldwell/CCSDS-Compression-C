/**
 * @file csv-io.h
 * @authors Kevin Caldwell and @BrianShTsoi
 * @brief Functions for image file read and write to CSV
 * @note When Saving Data, consider using uhi files.
 */

#ifndef CSV_IO_H
#define CSV_IO_H

#include <inttypes.h>

#include "dst/image.h"
#include "files/file_IO.h"

/**
 * @brief Save contents of an array as a CSV file.
 * @note Implementation has been removed temporarily
 * @todo Finish new implementation
 */
void SaveArrayAsCSV(uint16_t *data, UINT count, char *file_name);

/**
 * @brief Store all values of an image into the file at file_name
 * @details 
 * Writes the contents of image into the file, by converting 
 * the 3D image into a 1D stream in increasing count of x, y, z
 * indices, till the image boundaries are hit. 
 * @note Compatible with Python CSV Parser, used to validate
 * Predictor output with python predictor.
 * 
 */
int SaveImageAsCSV(image *hIMG, char *file_name);

/**
 * @brief Retrieve all values of an image from the file at file_name
 * @details 
 * Reads the contents of image from the file, by converting 
 * the 1D stream into a 3D object. 
 * @note Compatible with Python CSV Parser, used to validate
 * Predictor output with python predictor.
 * 
 */
int ReadImageFromCSV(image *hIMG, char *file_name);

#endif /* CSV_IO_H */
