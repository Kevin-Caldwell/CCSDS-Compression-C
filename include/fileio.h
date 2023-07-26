#ifndef FILEIO
#define FILEIO

#include <inttypes.h>
#include <stdio.h>

#include "image.h"

void SaveArrayAsCSV(uint16_t* data, UINT count, char* file_name);

void SaveImageAsCSV(image* hIMG, char* file_name);

#endif /* FILEIO */
