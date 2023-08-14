#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

#include "constants/constants.h"
#include "cache/image_instance.h"
#include "predictor/predictor.h"
#include "files/csv-io.h"
#include "files/file_IO.h"

int TEST_1();

void TestHeader();
void TestReadImage();

void GenerateTest(dim3 size, int index);

void BenchmarkVoronoi();

#endif /* GENERATE_IMAGE_H */
