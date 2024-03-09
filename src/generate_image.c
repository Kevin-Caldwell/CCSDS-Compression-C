#include "testing/generate_image.h"
#include "encoder/body.h"
#include "files/logs.h"

int GenerateVoronoiImage(dim3 size, int index, int points){
    char filename[100];
    sprintf(filename, "../data/test-images/VORONOI_%ux%ux%u_%d.csv", 
                                        size.x, size.y, size.z, index);
    image testImage;
    InitImage(&testImage, size.x, size.y, size.z);
    GenerateVoronoiFlat3DLocal(&testImage, points);

    SaveImageAsCSV(&testImage, filename);
    #ifndef MEMORY_SAVING
    free(testImage.data);
    #endif

    return RES_OK;
}

int PredictImage(char* source, char* destination){
    image* hIMG;
    image* result;
    int res;

    printf("___________C PREDICTOR____________\n");

    res = ReadImageFromCSV(hIMG, source);
    #if LOG
    if(res){
        Log_error("Unable to Read Image");
        return res;
    }
    #endif

    res = InitializePredictorCache(&global_cache, hIMG);
    #if LOG
    if(res){
        Log_error("Unable to Create Cache");
        return res;
    }
    #endif


    res = InitImage(result, hIMG->size.x, hIMG->size.y, hIMG->size.z);
    #if LOG
    if(res) {
        Log_error("Unable to Initialize Image");
        return res;
    }
    #endif

    #if LOG
    Log_add("Setup Complete! Proceeding to Predictor Setup");
    #endif
    res = RunPredictor(hIMG, result);
    #if LOG
    if(res) {
        Log_error("Predictor Error, Aborted");
        return res;
    }
    #endif
    

    res = SaveImageAsCSV(result, destination);
    #if LOG
    if(res) {
        Log_error("Unable to Save Image as CSV. Aborted.");
        return res;
    }
    #endif
    

    DeletePredictorCache(global_cache);

    #ifndef MEMORY_SAVING
    //free(hIMG->data);
    free(result->data);
    //free(hIMG);
    free(result);
    #endif
}

int PredictImageUHI(char* source, char* destination){
    image hIMG;
    image result;
    int res;

    dim3 size = (dim3) {145, 145, 220};

    printf("___________C PREDICTOR____________\n");

    res = UHI_Initialize((UHI*) &hIMG, size, source, READ_AND_WRITE);
    #if LOG
    if(res){
        Log_error("Unable to Read Image");
        return res;
    }
    #endif

    res = InitializePredictorCache(&global_cache, &hIMG);
    #if LOG
    if(res){
        Log_error("Unable to Create Cache");
        return res;
    }
    #endif


    res = UHI_Initialize((image*) &result, size, destination, WRITING_AND_READING);
    #if LOG
    if(res) {
        Log_error("Unable to Initialize Image");
        return res;
    }
    #endif

    #if LOG
    Log_add("Setup Complete! Proceeding to Predictor Setup");
    #endif
    res = RunPredictor(&hIMG, &result);
    #if LOG
    if(res) {
        Log_error("Predictor Error, Aborted");
        return res;
    }
    #endif
    

    // res = SaveImageAsCSV(result, destination);
    #if LOG
    if(res) {
        Log_error("Unable to Save Image as CSV. Aborted.");
        return res;
    }
    #endif
    

    DeletePredictorCache(global_cache);

    #ifndef MEMORY_SAVING
    //free(hIMG->data);
    free(result->data);
    //free(hIMG);
    free(result);
    #else
    F_CLOSE(hIMG.fs);
    F_CLOSE(result.fs);
    
    #endif
}

int EncodeImage(char* source, char* destination){
    image* predicted_image;
    ReadImageFromCSV(predicted_image, source);
    LoadConstantFile("../data/constants/predictor.CONST", &predictor_constants);
    InitalizeImageConstants(predicted_image->size);
    InitalizePredictorConstants();
    EncodeBody(predicted_image, destination, "w", 100);
    #ifndef MEMORY_SAVING
    free(predicted_image->data);
    #endif
    free(predicted_image);

    return RES_OK;

}

int CompressImage(char* source, char* destination){
    
}

void TestHeader(){
    uint8_t header[22];
    PrepareImageMetadata(header);
    PreparePredictorMetadata(header + 12);
    PrepareSampleAdaptiveEntropyCoder(header + 12 + 8);
}

void TestReadImage(){
    image* img;
    ReadImageFromCSV(img, "data_locale.csv");
    SaveImageAsCSV(img, "data_locale2.csv");
    #ifndef MEMORY_SAVING
    free(img->data);
    #endif
    
}

int cv_csv_uhi(char* src_csv, const char* dest_uhi){
    image img;
    dim3 size;
    dim3 index;
    UHI stream;

    ReadImageFromCSV(&img, src_csv);
    size = img.size;
    UHI_Initialize(&stream, size, dest_uhi, WRITE);
    printf("Read CSV\n");

    for(int i = 0; i < size.x; i++){
        for(int j = 0; j < size.y; j++){
            for(int k = 0; k < size.z; k++){
                index = (dim3) {i, j, k};
                PIXEL p = GetPixel(&img, i, j, k);
                UHI_WritePixel(&stream, index, p);
            }
        }
    }
    printf("Written CSV\n");

    #ifndef MEMORY_SAVING
    free(img.data);
    #endif
    F_CLOSE(stream.fs);

    return 0;
}

int cv_uhi_csv(const char* src_uhi, const char* dest_csv){

}