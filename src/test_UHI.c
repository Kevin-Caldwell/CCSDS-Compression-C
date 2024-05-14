#include "testing/test_UHI.h"

#include "testing/synthetic_image_generator.h"

int test_UHI()
{
    UHI stream;
    image baseImg;

    int _Nx = 145;
    int _Ny = 145;
    int _Nz = 220;
    // Prepare Random Hyperspectral Image
    InitImage(&baseImg, _Nx, _Ny, _Nz);
    GenerateVoronoiFlat3DNaive(&baseImg, 10);

    UHI_Initialize(&stream, baseImg.size, "../data/test-images/indian_pines.UHI", READ_AND_WRITE);

    // Write baseImg into UHI file
    for (int i = 0; i < _Nx; i++)
    {
        for (int j = 0; j < _Ny; j++)
        {
            for (int k = 0; k < _Nz; k++)
            {
                PIXEL p = GetPixel(&baseImg, i, j, k);
                UHI_WritePixel(&stream, (dim3){i, j, k}, p);
            }
        }
        printf("%dth Frame\n", i);
        fflush(stdout);
    }

    char write_error = 0;

    for (int i = 0; i < _Nx; i++)
    {
        for (int j = 0; j < _Ny; j++)
        {
            for (int k = 0; k < _Nz; k++)
            {
                PIXEL p0 = UHI_ReadPixel(&stream, (dim3){i, j, k});
                PIXEL p1 = GetPixel(&baseImg, i, j, k);
                if (p0 != p1)
                {
                    write_error = 1;
                }

                if (write_error)
                    break;
            }
            if (write_error)
                break;
        }
        if (write_error)
            break;

        printf("%dth Frame\n", i);
        fflush(stdout);
    }

    if (write_error)
        printf("Failed to Read and Write UHI Image Properly.\n");
    else
        printf("Successfully Written and Read UHI File.\n");

    F_CLOSE(stream.fs);
    return write_error;
}