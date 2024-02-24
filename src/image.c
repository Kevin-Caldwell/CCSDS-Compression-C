#include "dst/image.h"

#ifdef WIN_GCC

#include <unistd.h>

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


#ifdef ARM_GCC

#include <unistd.h>

int InitImage(image** img_p, size_t x, size_t y, size_t z){
    image* img = *img_p = (image*) malloc(sizeof(image));
    img->size.x = x;
    img->size.y = y;
    img->size.z = z;
    img->data = (PIXEL*) calloc(x * y * z, sizeof(PIXEL));

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