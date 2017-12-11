#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Neurone Neurone;
struct Neurone
{
  int nbrSynapses;
  double *exitWeights;
  double bias;
  double errorPace;
  double result;
}

typedef struct Layer Layer;
struct Layer
{
  int nbrNeurones;
  Neurone *neuronesList;
}

typedef struct NeuralNetwork NeuralNetwork;
struct NeuralNetwork
{
  int nbrLayers;
  Layer *layersList;
}

Neurone *initNeurone(int nbrSynapses);

double *weightSum(NeuralNetwork *neuralNetwork, int layerIndex, Neurone neuron);

void forward(NeuralNetwork *neuralNetwork, double *result);

void backward(NeuralNetwork *neuralNetwork, double *expectedResult);

void train(double **input,
           int nbinput, 
           double **output, 
           int nboutput,
           neuralNetwork *neuralNetwork);

