#include "neuron.h"
#include <time.h>
#include <math.h>

/*
    Init the neuron

    Input  : number of weights of the neuron
    Output : neuron
*/
neuron initNeuron(int nbweights)
{
    neuron n;//= malloc(sizeof(neuron));
    n.nbweight = nbweights;
    n.delta = 0;
    n.vActivation = 0;
    n.Z = 0;
    if(nbweights != 0)
    {
        n.weight = malloc(sizeof(double) * nbweights);
        srand(time(NULL));
        for(int i = 0; i < nbweights; i++)
                n.weight[i] = 2 * (double)rand()/(double)RAND_MAX - 1;//0.5 - (double)((rand()) % 100) / 100;
    }
    else n.weight = NULL;

    return n;
}
