#include "testing/generate_image.h"
#include "encoder/body.h"

void GenerateTest(dim3 size, int index){
    char filename[100];
    sprintf(filename, "../data/test-images/TEST_%lux%lux%lu_%d.csv", 
                                        size.x, size.y, size.z, index);
    image* testImage;
    InitImage(&testImage, size.x, size.y, size.z);
    GenerateVoronoiFlat3DLocal(testImage, size.x * size.y * size.z / 180000);

    SaveImageAsCSV(testImage, filename);
    free(testImage->data);
    free(testImage);
}

void PredictImage(char* source, char* destination){
    image* hIMG;
    image* result;
    printf("___________C PREDICTOR____________\n");

    ReadImageFromCSV(&hIMG, source);
    printf("Read File.\n");

    InitializePredictorCache(&global_cache, hIMG);
    printf("Cache Created..\n");


    InitImage(&result, hIMG->size.x, hIMG->size.y, hIMG->size.z);
    RunPredictor(hIMG, result);

    SaveImageAsCSV(result, destination);

    DeletePredictorCache(global_cache);

    //free(hIMG->data);
    free(result->data);
    //free(hIMG);
    free(result);
}

void EncodeImage(char* source, char* destination){
    image* predicted_image;
    ReadImageFromCSV(&predicted_image, source);
    LoadConstantFile("../data/constants/predictor.CONST", &predictor_constants);
    InitalizeImageConstants(predicted_image->size);
    InitalizePredictorConstants();
    EncodeBody(predicted_image, destination, "w", 100);
    free(predicted_image->data);
    free(predicted_image);

}

void CompressImage(char* source, char* destination){
    
}

void TestHeader(){
    uint8_t header[22];
    PrepareImageMetadata(header);
    PreparePredictorMetadata(header + 12);
    PrepareSampleAdaptiveEntropyCoder(header + 12 + 8);
}

void TestReadImage(){
    image* img;
    ReadImageFromCSV(&img, "data_locale.csv");
    SaveImageAsCSV(img, "data_locale2.csv");
    free(img->data);
    
}