#include "testing/generate_image.h"
#include "testing/perlin.h"

#include <string.h>

char DEBUG = 0;

int main(int argInt, char **argS)
{
#if LOG
    Log_init();
#endif

    printf("Starting Image Handler..\n");
    if (argInt > 1)
    {
        if (!strcmp(argS[1], "generate"))
        {
            if (!strcmp(argS[2], "voronoi"))
            {
                GenerateVoronoiImage((dim3){atoi(argS[3]), atoi(argS[4]), atoi(argS[5])}, atoi(argS[6]), atoi(argS[7]));
            }
            if (!strcmp(argS[2], "perlin"))
            {
                GeneratePerlinImage((dim3){atoi(argS[3]), atoi(argS[4]), atoi(argS[5])}, atoi(argS[6]), atoi(argS[7]));
            }
        }
        else if (!strcmp(argS[1], "cv-csv-uhi"))
        {
            cv_csv_uhi(argS[2], argS[3]);
        }
    }
    else
    {
        GeneratePerlinImage((dim3){100, 100, 100}, 0, 10);
    }
#if LOG
    Log_close();
#endif
}