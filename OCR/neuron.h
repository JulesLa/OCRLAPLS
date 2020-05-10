#ifndef NEURON_H
#define NEURON_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
	The structure of the neuron
*/
struct neuron_s
{
	double *weight;			//Array of weights
	int nbweight;				//Number of weight in the array
	double delta;				//Delta of the neuron
	double vActivation;	//The value "in" the neuron
	double Z;						//Z means the sum used for the forward propagation
}; typedef struct neuron_s neuron;
 

//Init a neuron
neuron initNeuron(int nbweights);


#endif
