#include "testing/generate_image.h"
#include "encoder/body.h"
#include "files/logs.h"

int GenerateVoronoiImage(dim3 size, int index, int points){
    char filename[100];
    sprintf(filename, "../data/test-images/VORONOI_%lux%lux%lu_%d.csv", 
                                        size.x, size.y, size.z, index);
    image testImage;
    InitImage(&testImage, size.x, size.y, size.z);
    GenerateVoronoiFlat3DLocal(&testImage, points);

    SaveImageAsCSV(&testImage, filename);
    free(testImage.data);

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

    //free(hIMG->data);
    free(result->data);
    //free(hIMG);
    free(result);
}

int EncodeImage(char* source, char* destination){
    image* predicted_image;
    ReadImageFromCSV(predicted_image, source);
    LoadConstantFile("../data/constants/predictor.CONST", &predictor_constants);
    InitalizeImageConstants(predicted_image->size);
    InitalizePredictorConstants();
    EncodeBody(predicted_image, destination, "w", 100);
    free(predicted_image->data);
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
    free(img->data);
    
}