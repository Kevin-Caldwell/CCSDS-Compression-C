#include "files/csv-io.h"

#include <string.h>

#if LOG
#include "files/logs.h"
#endif

void SaveArrayAsCSV(uint16_t* data, UINT count, char* file_name){
    file_t* fp;
    fp = F_OPEN(file_name, WRITE);
    #if LOG
    if(!fp){
        Log_error("SaveArrayAsCSV: Unable to open file");
    }
    #endif

    char string_buffer[50];

    for(int i = 0; i < count; i++){
        sprintf(string_buffer, "%hu,", data[i]);
        fputs(string_buffer, fp);
    }
    fputs("%hu", fp);

    F_CLOSE(fp);
}



int SaveImageAsCSV(image* hIMG, char* file_name){
    // FILE* fp;
    file_t* fp;
    dim3 size = hIMG->size;

    fp = F_OPEN(file_name, WRITE);

    #if LOG
    if(!fp) {
        Log_error("SaveImageAsCSV: Unable to open file");
        return FILE_ACCESS_ERROR;
    }
    #endif

    char string_buffer[50];

    sprintf(string_buffer, "%ld,%ld,%ld,", (long unsigned) size.x, (long unsigned) size.y,(long unsigned) size.z);
    fputs(string_buffer, fp);

    for(int i = 0; i < size.z; i++){
        for(int j = 0; j < size.y; j++){
            for(int k = 0; k < size.x; k++){
                sprintf(string_buffer, "%hu,", GetPixel(hIMG, k,j,i));
                fputs(string_buffer, fp);

            }
        }
    }

    // sprintf(string_buffer, "%hu", hIMG->data[size.x * size.y * size.z - 1]);
    // fputs(string_buffer, fp);
    F_CLOSE(fp);

    return RES_OK;
}

int ReadImageFromCSV(image* hIMG, char* file_name){
    file_t* fp;
    fp = F_OPEN(file_name, READ);
    
    #if LOG
    if(!fp) {
        Log_error("ReadImageFromCSV: Unable to open File");
        return FILE_ACCESS_ERROR;
    }
    #endif
    dim3 size =  {0,0,0};
    char read_buffer = 1;

    char num_buffer[30];
    int buffer_ptr = 0;

    uint16_t num;

    int img_counter = 0;

    while(read_buffer != EOF){
        size_t res = F_READ(&read_buffer, sizeof(char), 1, fp);

        if(read_buffer == ','){

            num_buffer[buffer_ptr] = 0;
            num  = atoi(num_buffer);
            buffer_ptr = 0;

            if(!size.x){
                size.x = num;
            }

            else if(!size.y){
                size.y = num;
            }

            else if(!size.z){
                size.z = num;
                InitImage(hIMG, size.x, size.y, size.z);   
            }
            else{
                (hIMG)->data[img_counter++] = num;
                if(img_counter == size.x * size.y * size.z){
                    break;
                }
            }

        } else{
            num_buffer[buffer_ptr++] = read_buffer;
        }
    }

    return RES_OK;

}