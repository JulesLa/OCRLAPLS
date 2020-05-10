#include <stdio.h>
#include <stdlib.h>

#include "network.h"
#include "func.h"

#define LEARN_RATE 0.9 //Used in updateWeight
#define ITERATION 3500 //Number of max iteration before killing and re-create
                                             // a new network - Used in train
/*
    Init the network

    Input  : nblayer / matrix of layersize
    Output : network
*/
network* initNetwork(int nblayer, int *layersize)
{
  network *net = malloc(sizeof(network));

  net->nblayer = nblayer;
  net->layersize = layersize;
  net->layer = malloc(sizeof(net->layer)*nblayer);

  for(int i = 0; i < net->nblayer-1; i++)
  {
    net->layer[i] = malloc(sizeof(neuron)*net->layersize[i]);
    for(int j = 0; j < net->layersize[i]; j++)
      net->layer[i][j] = initNeuron(net->layersize[i+1]);
  }
    
  net->layer[net->nblayer-1] = malloc(sizeof(neuron) * 
                               net->layersize[net->nblayer-1]);

  for(int j = 0; j < net->layersize[net->nblayer-1]; j++)
    net->layer[net->nblayer-1][j] = initNeuron(0);

  return net;
}

/*
    Free the network

    Input  : network
    Output : -------
*/
void killNetwork(network *net)
{
  for(int i = 0; i < net->nblayer; i++)
  {
    for(int j = 0; j < net->layersize[i]; j++)
    {
      free(net->layer[i][j].weight);
    }
    free(net->layer[i]);
  }
  free(net->layer);
  free(net->layersize);
  free(net);
}


/*
  Function which returns abs
*/
/*static void aps(double *a)
{
  if(*a < 0)
    *a = -(*a);
}*/

/*
    The forward propagation of the network

    Input  : network / matrix of input
    Output : vActivation of the last neuron
*/
double *forwardpropagation(network *net,int *input)
{
  for(int i = 0; i < net->layersize[0]; i++)
  {
    net->layer[0][i].vActivation = input[i];
  }
  double sum;

  for(int i = 1; i < net->nblayer; i++)
  {
    for(int j = 0; j < net->layersize[i] ; j++)
    {
      sum = 0;
      for(int k = 0; k < net->layersize[i-1] ; k++)
      {
        sum += net->layer[i-1][k].vActivation * net->layer[i-1][k].weight[j];
      }

      net->layer[i][j].Z = sum;
      net->layer[i][j].vActivation = sigm(sum); //atanh(sum);
      //printf("%3f\n", sum);
    }
  }

  double *output = malloc(sizeof(double) * net->layersize[net->nblayer-1]);

  for(int i = 0; i < net->layersize[net->nblayer-1]; i++)
  {
   // aps(&net->layer[net->nblayer-1][i].vActivation);
    output[i] = net->layer[net->nblayer-1][i].vActivation;
  }
  return output;
}

/*
    The backward propagation of the network

    Input  : network / input
    Output : ---------------
*/
void backwardpropagation(network *net, int *output) 
{
  calculdelta(net, output);
  updateWeight(net);
}

/*
    Compute the delta for the backward propagation

    Input  : network / input
    Output : ---------------
*/
void calculdelta(network *net,int *output)
{
  int i = net->nblayer - 1;
  for(int j = 0; j < net->layersize[i]; j++)
  {
    net->layer[i][0].delta = /*aArctanh*/sigmder(net->layer[i][0].Z) *
                                    (output[0] - net->layer[i][0].vActivation);
  }

  for(int i = net->nblayer - 2; i > 0; i--)
  {
    for(int j = 0; j < net->layersize[i];j++)
     {
      double sum = 0;
      for(int k = 0; k < net->layersize[i+1];k++)
      {
        sum += net->layer[i+1][k].delta * net->layer[i][k].weight[k];
      }
      net->layer[i][j].delta = /*aArctanh*/sigmder(net->layer[i][j].Z) * sum;
    }
  }
}

/*)
    Update each of neuron

    Input  : network
    Output : -------
*/
void updateWeight(network *net)
{
  for(int i = net->nblayer-2; i >= 0; i--)
  {
    for(int j = net->layersize[i]-1; j >= 0 ; j-- )
    {
      for(int k = 0; k < net->layersize[i+1]; k++ )
      {
        net->layer[i][j].weight[k] = net->layer[i][j].weight[k] + 
                                       LEARN_RATE * net->layer[i+1][k].delta * 
                                       net->layer[i][j].vActivation;
      }
    }
  }
}

/*
    Train the network nbinput times

  Input  : network / number of inputs / matrix of input / array of output
  Output : 1 -> the train works | 0 -> the train converge and will start again
*/
int train(network *net, int nbinput, int **input, int **output)
{
  int res = 0;
  int var;
  //int c = 0;

  for(int j = 0; j < ITERATION && res <nbinput; j++)
  {
    printf("\t\t\t\t\tITERATION %d \n",j);
    for(int i = 0; i < nbinput; i++)
    {
      var = onetrain(net, input[i], output[i]);
      res = res * var + var;
      printIO(net,input[i],output[i]);
    }

    if(res>=nbinput)
    {
      printNN(net,nbinput,input);
      return 1;
    }
  }
  return 0;
}


static double equal(double *tab, int *output, int size)
{
  double t = 1;
  for(int i = 0; t==1 && i < size; i++)
  {
    //if(!((output[i]==1 && tab[i]>0.9) || (output==0 && tab[i]<0.1)))
    // t = 0;
    if(!((output[i]==1 && tab[i]>0.9) || (output[i]==0 && tab[i]<0.1 && 
                                                          tab[i] > -0.1)))
      t=0;
  }
  return t;
}

/*
    Train the network for one input

    Input  : network / array of input / output expected
    Output : 1 -> work | 0 -> fail
*/
int onetrain(network *net, int *input,int *output)
{
  //double *tab = malloc(sizeof(int)*net->layersize[net->nblayer-1]);
  double *tab = forwardpropagation(net, input);
  backwardpropagation(net,output);

  double a = equal(tab,output,net->layersize[net->nblayer-1]);
  free(tab);
  return a;
}

/*
    Print the neuronal network with every neuron and inputs

    Input  : network / number of input / matrix of input
    Output : -------------------------------------------
*/
void printNN(network *net,int nbinput, int **input)
{
    for(int j = 0; j < nbinput;j++)
    {
      for(int zo = 0; zo < 1; zo++)
      {
        printf("===============================");
        printf("===============================");
        printf("\nPrinting the neuronal network : %d layers \t",net->nblayer);
        printf("INPUT : [%d][%d]\n",input[j][0],input[j][zo+1]);
        printf("===============================");
        printf("===============================\n\n");

        for(int i = 0; i < net->nblayer; i++)
        {
          printf("\t\t\t\t\t\t\tLayer number : %d\n",i);
          for(int j =0; j < net->layersize[i]; j++)
            printNeuron(net->layer[i][j],i,j);
        }
      }
    }
    printWeights(net);
}

/*
    Print the neuron with details

    Input   : neuron / i , j : corresponding to the matrix of neuron(**layer)
    Output : ----------------------------------------------------------------
*/
void printNeuron(neuron n,int i, int j)
{
    printf("Neuron [%d][%d]: \n",i,j);
    printf("\t\t vActivation = %f \n",n.vActivation);
    printf("\t\t Delta       = %f \n",n.delta);
    printf("\t\t Z           = %f \n",n.Z);
    printf("\t\t Nb weight   = %d \n",n.nbweight);

    for(int i = 0; i < n.nbweight; i++)
    {
        printf("\t\t weight[%d]   = %f\n",i,n.weight[i]);
    }
    printf("\n");
}

/*
    Print the output of the last neuron with the expected output

    Input     :   network /  array of input /  output expected
    Output    :   --------------------------------------------
*/
void printIO(network *net,int *input,int *output) //TODO
{
    for(int i = 0; i < 1; i++)
    {
      printf("[Input : [%d][%d][%d]] [Output : %lf] [Should be %d]\n",
                input[i],input[i+1],input[i+2],net->layer[2][0].vActivation
                ,output[i]);
    }
}

/*
    Print the final weights

    Input     : a network
    Output    : ---------

*/
void printWeights(network *net)
{
	printf("\n===============\n");
	printf("FINAL WEIGHTS : \n");
	printf("===============\n");
  
	for(int i = 0; i < net->nblayer-1; i++)
  {
  	printf("\t\t\t\t\t\t\tLayer number : %d\n",i);
    for(int j =0; j < net->layersize[i]; j++)
    {
			printf("Neuron [%d][%d] : \n",i,j);
    	for(int k = 0; k < net->layer[i][j].nbweight; k++)
      {
      	printf("\t\t weight[%d]   = %f\n",k,net->layer[i][j].weight[k]);
      }
    }
  }
}

static int foundMax(double *tab, int size)
{
  int max = 0; double valmax = tab[0];
  for(int i = 1; i < size; i++)
  {
    if(tab[i] > valmax)
    {
      valmax = tab[i];
      max = i;
    }
  }
  return max;
}

char foundletter(network *net, int *letter, char *listchar)
{
  double *tab = forwardpropagation(net, letter); 
  int max = foundMax(tab, net->layersize[net->nblayer - 1]);
  free(tab);
  return listchar[max];
}
