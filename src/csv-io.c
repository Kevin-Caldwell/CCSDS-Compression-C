#include "files/csv-io.h"

#include <string.h>

#if LOG
#include "files/logs.h"
#endif

// void SaveArrayAsCSV(uint16_t *data, UINT _count, char *file_name)
// {
//     file_t *fp;
//     fp = F_OPEN(file_name, WRITE);
// #if LOG
//     if (!fp)
//     {
//         Log_error("SaveArrayAsCSV: Unable to open file");
//     }
// #endif

//     char string_buffer[50];

//     for (int i = 0; i < _count; i++)
//     {
//         sprintf(string_buffer, "%hu,", data[i]);
//         fputs(string_buffer, fp);
//     }

//     // fputs("%hu", fp);

//     F_CLOSE(fp);
// }

int SaveImageAsCSV(image *hIMG, char *file_name)
{
    // FILE* fp;
    file_t *fp;
    dim3 size = hIMG->size;

    fp = F_OPEN(file_name, WRITE);

#if LOG
    if (!fp)
    {
        Log_error("SaveImageAsCSV: Unable to open file");
        return FILE_ACCESS_ERROR;
    }
#endif

    char string_buffer[50];
    int res;

    res = snprintf(string_buffer, 50, "%lu,%lu,%lu,", (long unsigned)size.x, (long unsigned)size.y, (long unsigned)size.z);
    if(res){
        perror("SaveImageAsCSV: Unable to format String Buffer.");
    }

    res = fputs(string_buffer, fp);
    if(res){
        perror("SaveImageAsCSV: Unable to write String Buffer.");
    }

    #ifndef S_SPLINT_S
    for (int i = 0; i < size.z; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            for (int k = 0; k < size.x; k++)
            {
                res = sprintf(string_buffer, "%hu,", GetPixel(hIMG, k, j, i));
                if(res){
                    perror("SaveImageAsCSV: Error while formatting pixel data.");
                }

                res = fputs(string_buffer, fp);
                if(res){
                    perror("SaveImageAsCSV: Error while storing Pixel Data.");
                }
            }
        }
    }
    #endif

    // sprintf(string_buffer, "%hu", hIMG->data[size.x * size.y * size.z - 1]);
    // fputs(string_buffer, fp);
    res = F_CLOSE(fp);
    global_error_handle

    return 0;
}

int ReadImageFromCSV(image *hIMG, char *file_name)
{
    int res = 0;
    file_t *fp;
    fp = F_OPEN(file_name, READ);

#if LOG
    if (!fp)
    {
        Log_error("ReadImageFromCSV: Unable to open File");
        return FILE_ACCESS_ERROR;
    }
#endif
    dim3 size = {0, 0, 0};
    char read_buffer = (char) 1;

    char num_buffer[30];
    int buffer_ptr = 0;

    int num;

    int img_counter = 0;

    while (read_buffer != (char) EOF)
    {
        res = (int) F_READ(&read_buffer, sizeof(char), 1, fp);
        global_error_handle

        if (read_buffer == ',')
        {

            num_buffer[buffer_ptr] = (char) 0;
            num = atoi(num_buffer);
            buffer_ptr = 0;

            if (size.x != 0)
            {
                size.x = (DIM) num;
            }

            else if (size.y != 0)
            {
                size.y = (DIM) num;
            }

            else if (size.z != 0)
            {
                size.z = (DIM) num;
                res = InitImage(hIMG, size.x, size.y, size.z);
            }
            else
            {
                break;
                // if (img_counter == (int) (size.x * size.y * size.z))
                // {
                //     break;
                // }
            }
        }
        else
        {
            num_buffer[buffer_ptr++] = read_buffer;
        }
    }

    return RES_OK;
}