#include "testing/test_UHI.h"

#include "testing/synthetic_image_generator.h"

int test_UHI(){
    UHI stream;
    image baseImg;

    int _Nx = 100;
    int _Ny = 100;
    int _Nz = 100;
    // Prepare Random Hyperspectral Image
    InitImage(&baseImg, _Nx, _Ny, _Nz);
    GenerateVoronoiFlat3DNaive(&baseImg, 10);
    
    
    UHI_Initialize(&stream, baseImg.size, "data/test-images/test.UHI", READ_AND_WRITE);
    for(int i = 0; i < _Nx; i++){
        for(int j = 0; j < _Ny; j++){
            for(int k = 0; k < _Nz; k++){
                UHI_WritePixel(&stream, (dim3) {i, j, k}, GetPixel(&baseImg, _Nx, _Ny, _Nz));
            }
        }
    }

    char fail = 0;

    for(int i = 0; i < _Nx; i++){
        for(int j = 0; j < _Ny; j++){
            for(int k = 0; k < _Nz; k++){
                if(UHI_ReadPixel(&stream, (dim3) {i, j, k}) != GetPixel(&baseImg, i, j, k)){
                    fail = 1;
                }

                if(fail) break;
            }
            if(fail) break;
        }
        if(fail) break;
    }

    #ifndef MEMORY_SAVING
    free(baseImg.data);
    #endif
    F_CLOSE(stream.fs);

    

    
    return fail;
}