#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

#include "predictor/predictor.h"
#include "encoder/header.h"
#include "files/csv-io.h"
#include "testing/synthetic_image_generator.h"

#include <time.h>

void TestHeader();
void TestReadImage();
int PredictImage(char *source, char *destination);

int PredictImageUHI(char *source, char *destination);

int EncodeImage(char *source, char *destination);

int CompressImage(char *source, char *destination);

int GenerateVoronoiImage(dim3 size, int index, int points);

int cv_csv_uhi(char *src_csv, const char *dest_uhi);

#endif /* GENERATE_IMAGE_H */
