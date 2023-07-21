#ifndef LOCAL_SUM_H
#define LOCAL_SUM_H

#include "constants.h"
#include "sample_representative.h"

#define LS(hIMG, z, y, x) FindLocalSum(hIMG, z, y, x)
int FindLocalSum(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_SUM_H */
