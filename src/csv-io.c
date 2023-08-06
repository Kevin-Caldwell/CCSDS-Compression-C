#include "files/csv-io.h"

void SaveArrayAsCSV(uint16_t* data, UINT count, char* file_name){
    FILE* fp;
    fp = F_OPEN(file_name, WRITE);

    char string_buffer[50];

    for(int i = 0; i < count; i++){
        sprintf(string_buffer, "%hu,", data[i]);
        fputs(string_buffer, fp);
    }
    fputs("%hu", fp);

    F_CLOSE(fp);
}



void SaveImageAsCSV(image* hIMG, char* file_name){
    FILE* fp;
    fp = fopen(file_name, "w");
    dim3 size = hIMG->size;

    char string_buffer[50];

    sprintf(string_buffer, "%ld,%ld,%ld,", (long unsigned) size.x, (long unsigned) size.y,(long unsigned) size.z);
    fputs(string_buffer, fp);

    for(int i = 0; i < size.x; i++){
        for(int j = 0; j < size.y; j++){
            for(int k = 0; k < size.z; k++){
                sprintf(string_buffer, "%hu,", GetPixel(hIMG, i,j,k));
                fputs(string_buffer, fp);

            }
        }
    }

    sprintf(string_buffer, "%hu", hIMG->data[size.x * size.y * size.z - 1]);
    fputs(string_buffer, fp);
}