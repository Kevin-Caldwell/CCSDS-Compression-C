#include "dst/image.h"

#include <unistd.h>

#if MEMORY_SAVING

int file_index = 0;

int InitImage(image* img_p, size_t x, size_t y, size_t z) {
    char file_name[40];
    sprintf(file_name, "_%lux%lux%lu_%d.UHI", x, y, z, file_index);
    UHI_Initialize(img_p, (dim3) {x, y, z}, file_name, READ_AND_WRITE);
}

PIXEL GetPixel(image* hIMG, INDEX x, INDEX y, INDEX z){
    return UHI_ReadPixel(hIMG, (dim3) {x, y, z});
}

void SetPixel(image* hIMG, INDEX x, INDEX y, INDEX z, PIXEL data) {
    UHI_WritePixel(hIMG, (dim3) {x, y, z}, data);
}

int Image_Equals(image* img1, image* img2){
    if(img1->size.x != img2->size.x || 
    img1->size.y != img2->size.y || 
    img1->size.z != img2->size.z) {
        return 0;
    }
    dim3 size = img1->size;
    for(int i = 0; i < size.x; i++){
        for(int j = 0; j < size.y; j++){
            for(int k = 0; k < size.y; k++){
                if(UHI_ReadPixel(img1, (dim3) {i, j, k}) != UHI_ReadPixel(img1, (dim3) {i, j, k})) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

#else

int InitImage(image* img_p, size_t x, size_t y, size_t z){
    img_p = (image*) malloc(sizeof(image));
    img_p->size.x = x;
    img_p->size.y = y;
    img_p->size.z = z;
    img_p->data = (PIXEL*) calloc(x * y * z, sizeof(PIXEL));

    return 0;
}

PIXEL GetPixel(image* hIMG, INDEX x, INDEX y, INDEX z){
    //sleep(0.005);
    dim3 size = hIMG->size;
    return hIMG->data[MAP3_1(x, y, z, size)];
}

PIXEL* GetFrame(image* hIMG, INDEX y){
    dim3 size = hIMG->size;
    return hIMG->data + y * FRAME_SIZE(size);
}

void SetPixel(image* hIMG, INDEX x, INDEX y, INDEX z, PIXEL data){
    //sleep(0.01);
    hIMG->data[MAP3_1(x, y, z, hIMG->size)] = data;
}

int Image_Equals(image* img1, image* img2){
    dim3 s1 = img1->size;
    dim3 s2 = img2->size;

    if(s1.x != s2.x || s1.y != s2.y || s1.z != s2.z){
        return 0;
    }
    for(int i = 0; i < s1.x * s1.y * s1.z; i++){
        if(img1->data[i] != img2->data[i]){
            return i;
        }
    }

    return INT32_MAX;
}

#endif

