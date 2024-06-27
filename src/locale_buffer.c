#include "dst/locale_buffer.h"

const int LocaleBuffer_neighbor_index_x[] = {0, -1, -1,  0, +1};
const int LocaleBuffer_neighbor_index_y[] = {0, -1,  0, -1, -1};

PIXEL LocaleBuffer_FetchPixel_Direct(LocaleBuffer* buf, DIM z, DIM y, DIM x){
    if(!x && !y && !z){ // Get Active Pixel
        return buf->data[0];
    }

    if(!z){
        for(int i = 1; i < LOCAL_BUFFER_NEIGHBOR_SIZE; i++){ // Search Neighbors
            if(LocaleBuffer_neighbor_index_x[i] == x && 
                LocaleBuffer_neighbor_index_y[i] == y){
                
                return buf->data[i];
            }
        }
    } else {
        return buf->data[LOCAL_BUFFER_NEIGHBOR_SIZE + z];
    }

    snprintf(log_write_buffer, 100, "UNABLE TO ACCESS PIXEL AT (x,y,z): %d %d %d", x, y, z);
    Log_error(log_write_buffer);
    return -1;
}

error_t LocaleBuffer_SimpleLoad(LocaleBuffer* buf, image* hIMG, dim3 index){
    int i = 0;
    int alx = index.x;
    int aly = index.y;
    int alz = index.z;
    

    for(i = 0; i < LOCAL_BUFFER_NEIGHBOR_SIZE; i++){
        alx = index.x + LocaleBuffer_neighbor_index_x[i];
        aly = index.y + LocaleBuffer_neighbor_index_y[i];

        if(_index_within_bounds(alx, aly, alz, hIMG->size)){
            buf->data[i] = GetPixel(hIMG, alx, aly, alz);
        }
    }

    alx = index.x, 
    aly = index.y;
    alz = index.z;
    for(i; i < LOCAL_BUFFER_TOTAL_SIZE; i++){
        alz--;
        if(_index_within_bounds(alx, aly, alz, hIMG->size)){
            buf->data[i] = GetPixel(hIMG, alx, aly, alz);
        }
    }

    return RES_OK;
}

error_t LocaleBuffer_FetchPixel(
    LocaleBuffer* buf,
    PIXEL* data,
    DIM offset_x, 
    DIM offset_y, 
    DIM offset_z) {
    
    if(!offset_x && !offset_y && !offset_z){ // Get Active Pixel
        *data = buf->data[0]; 
        return RES_OK;
    }

    if(!offset_z){
        for(int i = 1; i < LOCAL_BUFFER_NEIGHBOR_SIZE; i++){ // Search Neighbors
            if(LocaleBuffer_neighbor_index_x[i] == offset_x && 
                LocaleBuffer_neighbor_index_y[i] == offset_y){
                
                *data = buf->data[i];
                return RES_OK;
            }
        }
        return PIXEL_BUFFER_INDEX_INVALID;
    } else {
        *data = buf->data[LOCAL_BUFFER_NEIGHBOR_SIZE + offset_z];
        return RES_OK;
    }

    return PIXEL_BUFFER_PIXEL_NOT_FOUND;

}

void print_locale_buffer(LocaleBuffer* pixel_buffer){
    printf("Buffer Contents: [%d", pixel_buffer->data[0]);
    for(int i = 1; i < LOCAL_BUFFER_TOTAL_SIZE; i++){
        printf(", %d", pixel_buffer->data[i]);
    }
    printf("]\n");
}