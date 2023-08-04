#include "predictor/predictor.h"
#include <time.h>
#include <stdio.h>

int RunPredictor(image* hIMG, image* result){
    time_t start;
    time_t end;
    dim3 size = hIMG->size;
    start = time(NULL);
    for(int i = 0; i < size.x; i++){
        for(int j = 0; j < size.y; j++){
            for(int k = 0; k < size.z; k++){

                data_t raw_data = GetPixel(hIMG, i,j,k);
                data_t predicted_value = MappedQuantizerIndex(hIMG, k,j,i);
                SetPixel(result, i,j,k, predicted_value);
                
            }
        }
        
        
    }
    end = time(NULL);
    printf("%d seconds for image prediction.\n", (int) (end - start));
    return 0;
}
