#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Neurone
{
  int nbrSynapses;
  double *exitWeights;
  double biais;
  double errorPace;
  double result;
} Neurone;

typedef struct Layer
{
  int nbrNeurones;
  Neurone *neuronesList;
} Layer;

typedef struct NeuralNetwork
{
  int nbrLayers;
  Layer *layersList;
} NeuralNetwork;

Neurone *initNeurone(int nbrSynapses);

NeuralNetwork *initNeuralNetwork(int nbrLayers, int *neuronesPerLayer);

double weightSum(NeuralNetwork *neuralNetwork, int layerIndex, Neurone neuron);

void forward(NeuralNetwork *neuralNetwork, double *result);

void backward(NeuralNetwork *neuralNetwork, double *expectedResult);

void train(double **input,
           int nbinput, 
           double **output, 
           int nboutput,
           NeuralNetwork *neuralNetwork);

void killnetwork(NeuralNetwork *net);
