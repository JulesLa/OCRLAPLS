#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "network.h"

void save_net(char *chemin, network *net);

//network * load(char *chemin);

void  loadtest(int **input, int nbinput);

network *load(char *chemin);

#endif
