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
    
    
    UHI_Initialize(&stream, baseImg.size, "../data/test-images/test.UHI", READ_AND_WRITE);

    for(int i = 0; i < _Nx; i++){
        for(int j = 0; j < _Ny; j++){
            for(int k = 0; k < _Nz; k++){
                PIXEL p = GetPixel(&baseImg, i, j, k);
                UHI_WritePixel(&stream, (dim3) {i, j, k}, p);
                // printf("WRITING: %d INSTEAD OF %d\n", UHI_ReadPixel(&stream, (dim3) {i, j, k}), p);
            }
        }
    }

    char fail = 0;

    for(int i = 0; i < _Nx; i++){
        for(int j = 0; j < _Ny; j++){
            for(int k = 0; k < _Nz; k++){
                PIXEL p0 = UHI_ReadPixel(&stream, (dim3) {i, j, k});
                PIXEL p1 = GetPixel(&baseImg, i, j, k);
                // printf("%d\n", p1);
                if(p0 != p1){
                    fail = 1;
                    // printf("NOT SAME at {%d,%d,%d} | UHI: %u, BASE: %u\n", i, j, k, p0, p1);
                }

                if(fail) break;
            }
            if(fail) break;
        }
        if(fail) break;
    }

    if(fail) 
        printf("Failed to Read and Write UHI Image Properly.\n");
    else 
        printf("Successfully Written and Read UHI File.\n");

    #ifndef MEMORY_SAVING
    free(baseImg.data);
    #endif
    F_CLOSE(stream.fs);
    return fail;

}