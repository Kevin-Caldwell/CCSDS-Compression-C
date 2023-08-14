#include "predictor/predictor.h"
#include <time.h>
#include <stdio.h>

int RunPredictor(image* hIMG, image* result){
    time_t start;
    time_t end;
    dim3 size = hIMG->size;
    start = time(NULL);
    for(int i = 0; i < size.z; i++){
        for(int j = 0; j < size.y; j++){
            for(int k = 0; k < size.x; k++){

                if(j == 0 && k == 0){
                    free(global_cache->weights);
                    InitializeWeights(&(global_cache->weights), i,j,k);
                } 

                data_t raw_data = GetPixel(hIMG, k,j,i);
                data_t predicted_value = MappedQuantizerIndex(hIMG, i,j,k);
                SetPixel(result, k,j,i, predicted_value);
                
            }
        }
        printf("Generated %d/%d of Image.\n", (int) (i+1), (int) hIMG->size.x);
        
    }
    end = time(NULL);
    printf("%d seconds for image prediction.\n", (int) (end - start));
    return 0;
}
