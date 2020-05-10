#ifndef OCR_H
#define OCR_H

#include <stdlib.h>
#include <stdio.h>

#include "pixel_operations.h"
#include "segmentation.h"

#include "otsu.h"
#include "network.h"
#include "save.h"

#include "func.h"

void OCR(char *filename);

//void writeRes(network *net, int **input, FILE *fileRES, int nbinput);

#endif
