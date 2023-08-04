#ifndef CSV_IO_H
#define CSV_IO_H

#include <inttypes.h>
#include <stdio.h>

#include "math/image.h"

void SaveArrayAsCSV(uint16_t* data, UINT count, char* file_name);

void SaveImageAsCSV(image* hIMG, char* file_name);

#endif /* CSV_IO_H */
