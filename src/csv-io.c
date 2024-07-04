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
        return FILE_NON_EXISTENT;
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

    // sprintf(string_buffer, "%hu", hIMG->data[size.x * size.y * size.z - 1]);
    // fputs(string_buffer, fp);
    res = F_CLOSE(fp);
    log_global_error_handle

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
        return FILE_NON_EXISTENT;
    }
#endif
    dim3 size = {0, 0, 0};
    char read_buffer = (char) 1;

    char num_buffer[30];
    int buffer_ptr = 0;

    int num;
    int size_counter = 0;

    int img_counter = 0;
    int i=0, j=0, k=0;

    while (read_buffer != (char) EOF)
    {
        res = (int) (F_READ(&read_buffer, sizeof(char), 1, fp)) != 1;
        log_global_error_handle

        if (read_buffer == ',' || read_buffer == (char) EOF)
        {
            num_buffer[buffer_ptr] = (char) 0;
            num = atoi(num_buffer);
            buffer_ptr = 0;

            if (size_counter == 0)
            {
                size.x = (DIM) num;
                size_counter++;
            }

            else if (size_counter == 1)
            {
                size.y = (DIM) num;
                size_counter++;
            }

            else if (size_counter == 2)
            {
                size.z = (DIM) num;
                res = InitImage(hIMG, size.x, size.y, size.z);
                log_global_error_handle
                
                printf("Size Calculated: {%d, %d, %d}\n", size.x, size.y, size.z);
                size_counter++;
            }
            else
            {
                printf("{(%d %d %d): %d} ", i, j, k, num);
                SetPixel(hIMG, i, j, k, num);

                i++;
                img_counter++;

                if(i == size.x){
                    i = 0;
                    j++;
                }

                if(j == size.y) {
                    j = 0;
                    k++;
                }

                if(k == size.z){
                    printf("%d Pixels Found, out of %d total pixels.\n", img_counter, size.x * size.y * size.z);
                    printf("End of data reached.\n");
                    break;

                }
                
            }
        }
        else
        {
            num_buffer[buffer_ptr++] = read_buffer;
        }
    }

    return RES_OK;
}