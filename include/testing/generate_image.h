#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

#include "predictor/predictor.h"
#include "encoder/header.h"
#include "files/csv-io.h"
#include "testing/synthetic_image_generator.h"

#include <stdio.h>
#include <time.h>



int TEST_1();

void TestHeader();
void TestReadImage();
void PredictImage(char* source, char* destination);

void GenerateTest(dim3 size, int index);

void BenchmarkVoronoi();

#endif /* GENERATE_IMAGE_H */
