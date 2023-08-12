#include "testing/synthetic_image_generator.h"

#include <stdio.h>

#define WRI(x, point, tl, br) (INSIDE_INTERVAL(point.x, top_left.x, bottom_right, x))

int WithinRect2(dim2 point, dim2 top_left, dim2 bottom_right)
{
    return (INSIDE_INTERVAL(point.x, top_left.x, bottom_right.x)) &&
           (INSIDE_INTERVAL(point.y, top_left.y, bottom_right.y));
}

int WithinRect3(dim3 point, dim3 top_left, dim3 bottom_right)
{
    return (INSIDE_INTERVAL(point.x, top_left.x, bottom_right.x)) &&
           (INSIDE_INTERVAL(point.y, top_left.y, bottom_right.y)) &&
           (INSIDE_INTERVAL(point.z, top_left.z, bottom_right.z));
}

int SpreadPoint2(dim2 **points, dim2 bounds, UINT point_count)
{
    *points = INIT_ARRAY(dim2, point_count);

    for (int i = 0; i < point_count; i++)
    {
        (*points)[i].x = rand() % bounds.x;
        (*points)[i].y = rand() % bounds.y;
    }

    return 0;
}

int SpreadPoint3(dim3 **points, dim3 bounds, UINT point_count)
{
    *points = INIT_ARRAY(dim3, point_count);

    for (int i = 0; i < point_count; i++)
    {
        (*points)[i].x = rand() % bounds.x;
        (*points)[i].y = rand() % bounds.y;
        (*points)[i].z = rand() % bounds.z;
    }

    return 0;
}

int GenerateVoronoiFlat2D(image2 *result, UINT point_count)
{

    dim2 *points;
    SpreadPoint2(&points, result->size, point_count);

    for (int i = 0; i < result->size.x; i++)
    {
        for (int j = 0; j < result->size.y; j++)
        {
            for (int k = 0; k < point_count; k++)
            {
                result->data[j * result->size.x + i] = Manhattan2(points[k], (dim2){.x = i, .y = j});
            }
        }
    }

    free(points);
    return 0;
}

UINT GetMinDistance3Naive(dim3 point, dim3 *points, UINT point_count)
{
    UINT min = INT16_MAX;
    int distance = 0;
    int index = 0;
    for (int i = 0; i < point_count; i++)
    {
        distance = Manhattan3(point, points[i]);
        if (distance < min)
        {
            min = distance;
            index = i;
        }
    }

    return index;
}

int GenerateVoronoiFlat3DNaive(image3 *result, UINT point_count)
{
    dim3 *points;
    SpreadPoint3(&points, result->size, point_count);

    for (int i = 0; i < result->size.x; i++)
    {
        for (int j = 0; j < result->size.y; j++)
        {
            for (int k = 0; k < result->size.z; k++)
            {
                data_t min = GetMinDistance3Naive((dim3){i, j, k}, points, point_count);
                SetPixel(result, i, j, k, min);
            }
        }
    }

    free(points);
    return 0;
}

int GeneratePointLocales(dim3 *points, UINT **p_locales, UINT **p_true_indices, UINT point_count)
{
    UINT *locales = *p_locales = INIT_ARRAY(UINT, point_count);
    UINT *true_indices = *p_true_indices = INIT_ARRAY(UINT, point_count);
    UINT min_distance = UINT16_MAX;
    UINT distance;
    for (int i = 0; i < point_count; i++)
    {
        min_distance = UINT16_MAX;
        for (int j = 0; j < point_count; j++)
        {
            distance = Manhattan3(points[i], points[j]);
            if (distance < min_distance && i != j)
            {
                min_distance = distance;
            }
        }

        locales[i] = min_distance / 2;
        true_indices[i] = i;
    }

    return 0;
}

UINT GetMinDistance3Locales(dim3 point, dim3 *points, UINT *locales, UINT *color_indices, UINT point_count)
{
    UINT min = INT16_MAX;
    UINT distance = 0;
    UINT index = 0;
    for (int i = 0; i < point_count; i++)
    {
        distance = Manhattan3(point, points[i]);
        if (distance <= locales[i])
        {
            if (i)
            {

                dim3 temp = points[0];
                points[0] = points[i];
                points[i] = temp;

                UINT temp_locale = locales[0];
                locales[0] = locales[i];
                locales[i] = temp_locale;

                UINT t_ind = color_indices[0];
                color_indices[0] = color_indices[i];
                color_indices[i] = t_ind;
            }
            return color_indices[0];
        }
        if (distance < min)
        {
            min = distance;
            index = i;
        }
    }
    return color_indices[index];
}

int ShadeVoronoiBox3(image3* img, dim3 top_right, dim3 bounds, dim3* points, UINT* locales, UINT* color_indices, UINT point_count){

    dim3 tlf_bounds = {top_right.x,             top_right.y,    top_right.z};
    dim3 tlb_bounds = {top_right.x,             top_right.y,    top_right.z + bounds.z};
    dim3 trf_bounds = {top_right.x + bounds.x,  top_right.y,    top_right.z};
    dim3 trb_bounds = {top_right.x + bounds.x,  top_right.y,    top_right.z + bounds.z};

    dim3 blf_bounds = {top_right.x,             top_right.y + bounds.y,     top_right.z};
    dim3 blb_bounds = {top_right.x,             top_right.y + bounds.y,     top_right.z + bounds.z};
    dim3 brf_bounds = {top_right.x + bounds.x,  top_right.y + bounds.y,     top_right.z};
    dim3 brb_bounds = {top_right.x + bounds.x,  top_right.y + bounds.y,     top_right.z + bounds.z};
    
    UINT tlf = GetMinDistance3Locales(tlf_bounds, points, locales, color_indices, point_count);
    UINT tlb = GetMinDistance3Locales(tlb_bounds, points, locales, color_indices, point_count);
    UINT trf = GetMinDistance3Locales(trf_bounds, points, locales, color_indices, point_count);
    UINT trb = GetMinDistance3Locales(trb_bounds, points, locales, color_indices, point_count);
    
    UINT blf = GetMinDistance3Locales(blf_bounds, points, locales, color_indices, point_count);
    UINT blb = GetMinDistance3Locales(blb_bounds, points, locales, color_indices, point_count);
    UINT brf = GetMinDistance3Locales(brf_bounds, points, locales, color_indices, point_count);
    UINT brb = GetMinDistance3Locales(brb_bounds, points, locales, color_indices, point_count);


    if(tlf == tlb && tlb == trf && trf == trb && trb == blf && blf == blb && brf == brb){
        for(int i = 0; i < bounds.x; i++){
            for(int j = 0; j < bounds.y; j++){
                for(int k = 0; k < bounds.z; k++){
                    SetPixel(img, i,j,k, brb);
                }
            }
        }
    } else{

        dim3 half_bounds = {bounds.x/2, bounds.y/2, bounds.z/2};

        tlf_bounds = (dim3) {top_right.x,                         top_right.y,                            top_right.z};
        tlb_bounds = (dim3) {top_right.x,                         top_right.y,                            top_right.z + half_bounds.z};
        trf_bounds = (dim3) {top_right.x + half_bounds.x,         top_right.y,                            top_right.z};
        trb_bounds = (dim3) {top_right.x + half_bounds.x,         top_right.y,                            top_right.z + half_bounds.z};

        blf_bounds = (dim3) {top_right.x,                         top_right.y + half_bounds.y,            top_right.z};
        blb_bounds = (dim3) {top_right.x,                         top_right.y + half_bounds.y,            top_right.z + half_bounds.z};
        brf_bounds = (dim3) {top_right.x + half_bounds.x,         top_right.y + half_bounds.y,            top_right.z};
        brb_bounds = (dim3) {top_right.x + half_bounds.x,         top_right.y + half_bounds.y,            top_right.z + half_bounds.z};        
        
        ShadeVoronoiBox3(img, tlf_bounds, half_bounds, points, locales, color_indices, point_count);
        ShadeVoronoiBox3(img, tlb_bounds, half_bounds, points, locales, color_indices, point_count);
        ShadeVoronoiBox3(img, trf_bounds, half_bounds, points, locales, color_indices, point_count);
        ShadeVoronoiBox3(img, trb_bounds, half_bounds, points, locales, color_indices, point_count);

        ShadeVoronoiBox3(img, blf_bounds, half_bounds, points, locales, color_indices, point_count);
        ShadeVoronoiBox3(img, blb_bounds, half_bounds, points, locales, color_indices, point_count);
        ShadeVoronoiBox3(img, brf_bounds, half_bounds, points, locales, color_indices, point_count);
        ShadeVoronoiBox3(img, brb_bounds, half_bounds, points, locales, color_indices, point_count);
    }

    return 0;
}

int GenerateVoronoiFlat3DLocal(image3 *result, UINT point_count)
{
    dim3 *points;
    SpreadPoint3(&points, result->size, point_count);

    UINT *locales;
    UINT *true_indices;
    GeneratePointLocales(points, &locales, &true_indices, point_count);

    //ShadeVoronoiBox3(result, (dim3){0,0,0}, result->size, points, locales, true_indices, point_count);

    for (int i = 0; i < result->size.x; i++)
    {
        printf("Generated %d/%d of Image.\n", (int) (i+1), (int) result->size.x);
        for (int j = 0; j < result->size.y; j++)
        {
            for (int k = 0; k < result->size.z; k++)
            {
                data_t min = GetMinDistance3Locales((dim3){i, j, k}, points, locales, true_indices, point_count);
                SetPixel(result, i, j, k, min);
            }
        }
    }

    free(points);
    free(locales);
    free(true_indices);
    return 0;
}