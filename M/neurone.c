// Neurone.c

#include <stdio.h>
#include "neurone.h"

Neurone *initNeurone(int nbrSynapses)
{
	Neurone *neurone = malloc(sizeof(Neurone));
	
	neurone->nbrSynapses = nbrSynapses;
	neurone->biais = 0;
	neurone->errorPace = 0;
	neurone->result = 0;
	neurone->exitWeights = malloc(nbrSynapses * sizeof(double));

	srand(time(NULL));
	for (int i = 0; i < nbrSynapses; i++)
	{
		neurone->exitWeights[i] = (double)rand() / (double)RAND_MAX;
	}
	
	return neurone;	
}

NeuralNetwork *initNeuralNetwork(int nbrLayers, int *neuronesPerLayer)
{
	NeuralNetwork *neuralNetwork = malloc(sizeof(NeuralNetwork));
	
	neuralNetwork->nbrLayers = nbrLayers;
	neuralNetwork->layersList = malloc(nbrLayers * sizeof(Layer));
	
	for (int i = 0; i < nbrLayers; i++)
	{
		neuralNetwork->layersList[i].nbrNeurones = neuronesPerLayer[i];
		neuralNetwork->layersList[i].neuronesList = malloc(neuronesPerLayer[i] * sizeof(Neurone));
		for (int j = 0; j < neuronesPerLayer[i]; j++)
		{	
			if (i + 1 < nbrLayers)		
				neuralNetwork->layersList[i].neuronesList[j] = *initNeurone(neuronesPerLayer[i + 1]);
			else
				neuralNetwork->layersList[i].neuronesList[j] = *initNeurone(0);
		}		
	}
	
	return neuralNetwork;
}

double *weightSum(NeuralNetwork *neuralNetwork, int layerIndex ,Neurone neuron)
{
	double sommePonderee = 0;
	for (int i = 0; i < neuralNetwork->layersList[layerIndex - 1].nbrNeurones; i++)
	{
		sommePonderee += neuron.exitWeights[i] * neuralNetwork->layersList[layerIndex - 1].neuronesList[i].result;
	}
	return sommePonderee;
}

void forward(NeuralNetwork *neuralNetwork, double *result)	//This function is executed after the entry neurons are set. It sets the result, a double because of XOR //TODO
{
	int layerIndex = 1;
	for (;layerIndex < neuralNetwork->nbrLayers; layerIndex++)
	{
		for (int i = 0; i < neuralNetwork->layersList[layerIndex].nbrNeurones; i++)
		{
			Neurone neuron = neuralNetwork->layersList[layerIndex].neuronesList[i];
			double value = weightSum(neuralNetwork, layerIndex, neuron);
			neuron.result = 1 / (1 - exp(-value));
		}
	}
  int n = neuralNetwork->layersList[neuralNetwork->nbrLayers-1].nbrNeurones;
  //result = malloc(sizeof(double) * n);
  for(int i = 0; i < n; i++)
  {
	  result[i] = neuralNetwork->layersList[layerIndex - 1].neuronesList[i].result;	//the result is set here
  }
}

void backward(NeuralNetwork *neuralNetwork, double *expectedResult)		//This function corrects the weights of every neurons (only one expected value for XOR) // TODO
{
	int layerIndex = neuralNetwork->nbrLayers - 1;
	double pasDapprentissage = 2.0;
	
	Layer lastLayer = neuralNetwork->layersList[layerIndex];
	Layer penultimate = neuralNetwork->layersList[layerIndex - 1]; //penultimate = "avant-dernier"
		
	double currentResult = neuralNetwork->layersList[layerIndex].neuronesList[0].result;
	
	for (int i = 0; i < lastLayer.nbrNeurones; i++)	//Update the weights of the connexions that are going into the exit layer. (for XOR only one neuron)
	{
		for (int j = 0; j < penultimate.nbrNeurones; j++) //DO je crois
		{
      currentresult = lastLayer.neuronesList[i].result;
			lastLayer.neuronesList[i].errorPace = (expectedResult[i] - currentResult) * currentResult * (1 - currentResult);
			lastLayer.neuronesList[i].exitWeights[j] += pasDapprentissage * lastLayer.neuronesList[i].errorPace * penultimate.neuronesList[j].result;
		}
	}
	layerIndex--;
	for (;layerIndex > 0; layerIndex--)	//Update the weights of the connexions in the hidden layers
	{
		Layer previousLayer = neuralNetwork->layersList[layerIndex - 1];
		Layer currentLayer = neuralNetwork->layersList[layerIndex];
		Layer nextLayer = neuralNetwork->layersList[layerIndex + 1];
		
		for (int i = 0; i < currentLayer.nbrNeurones; i++)
		{
			for (int j = 0; j < previousLayer.nbrNeurones; j++)
			{
				double sigmoidDerived = currentLayer.neuronesList[i].result * (1 - currentLayer.neuronesList[i].result);
				double sum = 0;
				for (int k = 0; k < nextLayer.nbrNeurones; k++)
				{
					sum += (nextLayer.neuronesList[k].errorPace * nextLayer.neuronesList[k].exitWeights[i]);
				}
				currentLayer.neuronesList[i].errorPace = sigmoidDerived * sum;
				currentLayer.neuronesList[i].exitWeights[j] = pasDapprentissage * errorSignal * previousLayer.neuronesList[j].result;
			}
		}
	}	
}


void train(double **input, int nbinput, double **output, int nboutput, neuralNetwork *neuralNetwork)
{
  int res = 0;
  while(res < nbinput)
  {
    for(int i = 0; i < nbinput && res < nbinput; i++)
    {
      for(int j = 0; j < neuralNetwork->layerList[0].nbrNeurones ; j++)
      {
        neuralNetwork->layerList[0]->neuronesList[j]->result = input[i][j];
      }

      double *result = malloc(sizeof(double)*nboutput);
      forward(neuralnetwork, result);
      backward(neuralNetwork, ouput[i]);

      if(equal(result, output[i])) 
        res++;
      else 
        res = 0;
    }
  }
}
