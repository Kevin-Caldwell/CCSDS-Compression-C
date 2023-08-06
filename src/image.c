#include "dst/image.h"

int InitImage(image** img_p, size_t x, size_t y, size_t z){
    image* img = *img_p = (image*) malloc(sizeof(image));
    img->size.x = x;
    img->size.y = y;
    img->size.z = z;
    img->data = (PIXEL*) calloc(x * y * z, sizeof(PIXEL));
    return 0;
}

PIXEL GetPixel(image* hIMG, INDEX x, INDEX y, INDEX z){
    dim3 size = hIMG->size;
    return hIMG->data[MAP3_1(x, y, z, size)];
}

PIXEL* GetFrame(image* hIMG, INDEX y){
    dim3 size = hIMG->size;
    return hIMG->data + y * FRAME_SIZE(size);
}

void SetPixel(image* hIMG, INDEX x, INDEX y, INDEX z, PIXEL data){
    hIMG->data[MAP3_1(x, y, z, hIMG->size)] = data;
}