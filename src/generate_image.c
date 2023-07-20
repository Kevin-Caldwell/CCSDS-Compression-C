#include "Testing/generate_image.h"

#include <stdio.h>


int GenerateData(image** hIMG, dim3* dataPoints, UINT point_count){
    InitImage(hIMG, Nx, Ny, Nz);

    UINT distance;
    UINT minimum_distance = 0;
    UINT index;

    for(int i = 0; i < Nx; i++){
        for(int j = 0; j < Ny; j++){
            for(int k = 0; k < Nz; k++){
                minimum_distance = 0;
                minimum_distance--;
                index = 0;
                for(int l = 0; l < point_count; l++){
                    distance = abs(dataPoints[l].x - i) + abs(dataPoints[l].y - j) + abs(dataPoints[l].z - k);
                    minimum_distance = MIN(minimum_distance, distance);
                }

                SetPixel(*hIMG, i, j, k, minimum_distance);
            }
        }
    }
    return 0;
}

#define INIT_ARRAY(T, count) (T*) malloc(sizeof(T) * count)

int SpreadPoints(dim3** points, dim3 bounds, UINT point_count){
    *points = INIT_ARRAY(dim3, point_count);

    for(int i = 0; i < point_count; i++){
        (*points)[i].x = rand() % bounds.x;
        (*points)[i].y = rand() % bounds.y;
        (*points)[i].z = rand() % bounds.z;
    }

    return 0;
}

int TEST_1()
{

    dim3* points;
    dim3 bounds;
    bounds.x = Nx;
    bounds.y = Ny;
    bounds.z = Nz;

    SpreadPoints(&points, bounds, 10);

    for(int i = 0; i < 10; i++){
        printf("{%lu, %lu, %lu}\n", points[i].x, points[i].y, points[i].z);
    }

    free(points);

    return 0;
}

//  git config --global user.email "you@example.com"
//  git config --global user.name "Your Name"