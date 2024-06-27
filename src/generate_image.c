#include "testing/generate_image.h"


int GenerateVoronoiImage(dim3 size, int index, int points)
{
    int res = RES_OK;

    char filename[100];
    res = snprintf(filename, 100, "../data/test-images/VORONOI_%ux%ux%u_%d.csv",
            (unsigned int) size.x, (unsigned int) size.y, (unsigned int) size.z, index) >= 100;
    
    
    image testImage = decl_image;

    res = InitImage(&testImage, size.x, size.y, size.z);
    log_global_error_handle

    res = GenerateVoronoiFlat3DLocal(&testImage, (UINT) points);
    log_global_error_handle
 
    res = SaveImageAsCSV(&testImage, filename);
    log_global_error_handle

    return res;
}

int PredictImage(char *source, char *destination)
{
    image hIMG = decl_image;
    image result = decl_image;
    int res;

    printf("___________C PREDICTOR____________\n");

    res = ReadImageFromCSV(&hIMG, source);
#if LOG
    if (res)
    {
        Log_error("Unable to Read Image");
        return res;
    }
#endif

    res = InitImage(&result, hIMG.size.x, hIMG.size.y, hIMG.size.z);
#if LOG
    if (res)
    {
        Log_error("Unable to Initialize Image");
        return res;
    }
#endif

#if LOG
    Log_add("Setup Complete! Proceeding to Predictor Setup");
#endif
    res = RunPredictor(&hIMG, &result);
#if LOG
    if (res)
    {
        Log_error("Predictor Error, Aborted");
        return res;
    }
#endif

    res = SaveImageAsCSV(&result, destination);
#if LOG
    if (res)
    {
        Log_error("Unable to Save Image as CSV. Aborted.");
        return res;
    }
#endif
    return res;
}

int PredictImageUHI(char *source, char *destination)
{
    image hIMG = decl_image;
    image result = decl_image;
    int res;

    dim3 size = (dim3){145, 145, 220};

    printf("___________C PREDICTOR____________\n");

    res = UHI_Initialize((UHI *)&hIMG, size, source, READ_AND_WRITE);
#if LOG
    if (res)
    {
        Log_error("Unable to Read Image");
        return res;
    }
#endif

    res = UHI_Initialize((image *)&result, size, destination, WRITING_AND_READING);
#if LOG
    if (res)
    {
        Log_error("Unable to Initialize Image");
        return res;
    }
#endif

#if LOG
    Log_add("Setup Complete! Proceeding to Predictor Setup");
#endif
    res = RunPredictor(&hIMG, &result);
#if LOG
    if (res)
    {
        Log_error("Predictor Error, Aborted");
        return res;
    }
#endif

// res = SaveImageAsCSV(result, destination);
#if LOG
    if (res)
    {
        Log_error("Unable to Save Image as CSV. Aborted.");
        return res;
    }
#endif

    res = F_CLOSE(hIMG.fs);
    log_global_error_handle
    
    res = F_CLOSE(result.fs);
    log_global_error_handle

    return RES_OK;
}

int EncodeImage(char *source, char *destination)
{
    int res = RES_OK;
    image predicted_image = decl_image;

    res = ReadImageFromCSV(&predicted_image, source);
    log_global_error_handle

    res = LoadConstantFile("../data/constants/predictor.CONST", &predictor_constants);
    log_global_error_handle

    InitalizePredictorConstants();
    res = EncodeBody(&predicted_image, destination, "w", 100);
    log_global_error_handle

    return RES_OK;
}

int CompressImage(/*@unused@*/ char *source, /*@unused@*/ char *destination)
{
    return RES_OK;
}

void TestHeader()
{
    uint8_t header[22];
    memset(header, 0, 22);

    PrepareImageMetadata(header, (dim3){0, 0, 0});
    PreparePredictorMetadata(header + 12);
    PrepareSampleAdaptiveEntropyCoder(header + 12 + 8);
}

int TestReadImage()
{
    int res = RES_OK;
    image img = decl_image;
    res = ReadImageFromCSV(&img, "data_locale.csv");
    log_global_error_handle

    res = SaveImageAsCSV(&img, "data_locale2.csv");
    log_global_error_handle

    return RES_OK;
}

int cv_csv_uhi(char *src_csv, const char *dest_uhi)
{
    int res = RES_OK;

    image img = decl_image;
    dim3 size;
    /*@unused@*/
    dim3 index;
    UHI stream = decl_image;

    printf("Reading Source Image From CSV...\n");
    res = ReadImageFromCSV(&img, src_csv);
    log_global_error_handle

    size = img.size;
    res = UHI_Initialize(&stream, size, dest_uhi, WRITE);
    log_global_error_handle

    printf("Read CSV\n");
    for (int i = 0; i < size.x; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            for (int k = 0; k < size.z; k++)
            {
                index = (dim3){i, j, k};
                PIXEL p = GetPixel(&img, i, j, k);

                res = UHI_WritePixel(&stream, index, p);
                log_global_error_handle
            }
        }
    }
    printf("Written CSV\n");

    res = F_CLOSE(stream.fs);
    log_global_error_handle

    return 0;
}

int cv_uhi_csv(/*@unused@*/ const char *src_uhi, /*@unused@*/ const char *dest_csv)
{
    return RES_OK;
}