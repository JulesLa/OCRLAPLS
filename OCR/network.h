#ifndef	NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>

#include "neuron.h"

/*
	The structure of the network
*/
typedef struct networks
{
	int nblayer;		//Number of layer
	int *layersize;	//{nbneuron,nbneuron..}  number of neurons by layer
	neuron **layer;	//{{1,2},{3,4}}					 Array of neuron array
} network;

//Init the network
network* initNetwork(int nblayer, int *layersize);

//Free the network
void		 killNetwork(network *net);

//The forward propagation of the network
double 	*forwardpropagation(network *net, int *input);

//The backward propragation of the network
void 		 backwardpropagation(network *net, int *input);

//Train the network nbinput times
int 		 train(network *net, int nbinput,int **input, int **output);

//Train the network for one input
int	 		 onetrain(network *net, int *input, int *output);

//Compute the delta for the backward propagation
void		 calculdelta(network *net, int *input);

//Update  each weight of neuron
void		 updateWeight(network *net);

//Print the neuronal network with every neuron and inputs
void		 printNN(network *net,int nbinput,int **input);

//Print the neuron with details
void		 printNeuron(neuron n,int i,int j);

//Print the output of the last neuron with the expected output
void 		 printIO(network *net,int *input,int *output);

//Print the final weights
void 		 printWeights(network *net);


char     foundletter(network *net, int *letter, char *listchar);
#endif
