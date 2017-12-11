

Neurone *initNeurone(int nbrSynapses);
double *weightSum(NeuralNetwork *neuralNetwork, int layerIndex, Neurone neuron);
void forward(NeuralNetwork *neuralNetwork, double *result);
void backward(NeuralNetwork *neuralNetwork, double *expectedResult);


