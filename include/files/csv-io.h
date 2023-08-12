#ifndef CSV_IO_H
#define CSV_IO_H

#include <inttypes.h>
#include <stdio.h>

#include "dst/image.h"
#include "files/file_IO.h"

void SaveArrayAsCSV(uint16_t* data, UINT count, char* file_name);

void SaveImageAsCSV(image* hIMG, char* file_name);

void ReadImageFromCSV(image** hIMG, char* file_name);

#endif /* CSV_IO_H */
