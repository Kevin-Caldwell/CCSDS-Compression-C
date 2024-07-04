#include "testing/perlin.h"

/**
 * @brief 3D floating point vector
 * @details
 * Struct for 3D vector with floaitng point x, y, z coordinates
 */
typedef struct fVector3
{
    float x, y, z;
} fVector3;

float dot(fVector3 u, fVector3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

fVector3 normalize(fVector3 v)
{
    float mag = sqrtf(dot(v, v));
    return (fVector3){v.x / mag, v.y / mag, v.z / mag};
}

float interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

uint16_t mapper(float val)
{
    return (uint16_t)(val * (float)(1u << 14));
}

fVector3 RandomizeVector(int vector_x, int vector_y, int vector_z)
{
    srand(vector_x + 10000);
    int x = rand() % 100;
    srand(vector_y + 20000);
    int y = rand() % 100;
    srand(vector_z + 30000);
    int z = rand() % 100;

    float mag = sqrtf(SQ(x) + SQ(y) + SQ(z));
    return (fVector3){(float)x / mag, (float)y / mag, (float)z / mag};
}

uint16_t SolvePerlin4(int x, int y, int z, int len, dim3 size)
{
    // int vertexX = x - x % len;
    // int vertexY = y - y % len;
    // int vertexZ = z - z % len;

    // fVector3 offset_vector = normalize((fVector3){x % len, y % len, z % len});

    float value = 0;

    // for (int i = 0; i <= len; i += len)
    // {
    //     for (int j = 0; j <= len; j += len)
    //     {
    //         for (int k = 0; k <= len; k += len)
    //         {
    //             // fVector3 grid_vector = RandomizeVector(vertexX + i * len, vertexY + j * len, vertexZ + k * len);
    //             // float dot_product = dot(grid_vector, offset_vector);
    //         }
    //     }
    // }

    return mapper(value);
}

void Perlin4(image *result, int cube_side)
{
    printf("PERLIN \n");
    srand(1);
    dim3 size = result->size;
    time_t start;
    time_t end;
    start = time(NULL);
    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            for (int z = 0; z < size.z; z++)
            {
                SetPixel(result, x, y, z, SolvePerlin4(x, y, z, cube_side, size));
            }

            time_t time_elapsed = time(NULL) - start;
            time_t time_left = time_elapsed * ((result->size.x - x - 1) * result->size.y + (result->size.y - y - 1)) / (result->size.y * (x + 1) + (y + 1));
            #ifdef ARM_COMPILE
            printf("\rGenerated %d/%d of Image. (%lld seconds Elapsed, %lld seconds Left)", (int)(x + 1), (int)result->size.x, time_elapsed, time_left);
            #else
            printf("\rGenerated %d/%d of Image. (%ld seconds Elapsed, %ld seconds Left)", (int)(x + 1), (int)result->size.x, time_elapsed, time_left);
            #endif
            fflush(stdout);
        }
    }

    end = time(NULL);
    printf("\n%d seconds for image prediction.\n", (int)(end - start));
}

void GeneratePerlinImage(dim3 size, int index, int length)
{
    char filename[100];
    sprintf(filename, "../data/test-images/PERLIN_%lux%lux%lu_%d.csv",
            (long unsigned)size.x,
            (long unsigned)size.y,
            (long unsigned)size.z,
            (int)index);
    image testImage = decl_image;
    InitImage(&testImage, size.x, size.y, size.z);
    Perlin4(&testImage, length);

    SaveImageAsCSV(&testImage, filename);
}