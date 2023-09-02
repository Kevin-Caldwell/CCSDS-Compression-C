#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

#include "predictor/predictor.h"
#include "encoder/header.h"
#include "files/csv-io.h"
#include "testing/synthetic_image_generator.h"

#include <stdio.h>
#include <time.h>

void TestHeader();
void TestReadImage();
void PredictImage(char* source, char* destination);

void EncodeImage(char* source, char* destination);

void CompressImage(char* source, char* destination);

void GenerateVoronoiImage(dim3 size, int index, int points);

#endif /* GENERATE_IMAGE_H */
