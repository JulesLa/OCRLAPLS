#include "save.h"
#include "string.h"

void save(char *chemin, NeuralNetwork *net)
{
  strcat(chemin,".ntw");
  FILE *fichier = fopen(chemin, "w");
  fprintf(fichier ,"%d\n", net->nbrLayers);
  for(int i = 0; i < net->nbrLayers;i++)
  {
    fprintf(fichier,"%d\n", net->layersList[i].nbrNeurones);
    for(int j = 0; j < net->layersList[i].nbrNeurones; j++)
    {
      fprintf(fichier, "%d\n", net->layersList[i]->neuronesList[j].nbrSynapses);
      for(int k = 0; k < net->layersList[i]->neuronesList[j].nbrSynapses; k++)
      {
        fprintf(fichier, "%f\n", net->layersList[i]->neuronesList[j]->exitWeights[k]);
      }
    }
  }
  fclose(fichier);
}


NeuralNetwork *load(char *chemin)
{
  strcat(chemin, ".ntw");
  FILE *fichier = fopen(chemin, "r");
  
  if(fichier == NULL)
  {
    printf("/!\\ Problem with the file /!\\\n\n");
    return NULL;
  }
  NeuralNetwork *net = malloc(sizeof(Neural Network));

  fscanf(fichier, "%d\n", &net->nbrLayers);
  neuralNetwork->layerList = malloc(net->nbrLayers * sizeof(Layer));
  
  for(int i = 0; i < net->nbrLayers; i++)
  {
    fscanf(fichier, "%d\n", &net->layersList[i].nbrNeurones);
    for(int j = 0; j < net->layersList[i].nbrNeurones; j++)
    {
      fscanf(fichier, "%d\n", &net->layersList[i]->neuronesList[j].nbrSynapses);
      for(int k = 0; k < net->layerList[i]->neuronesList[j].nbrSynapses)
      {
        fscanf(fichier, "%lf\n", &net->layersList[i]->neuronesList[j]->exitWeight[k]);
      }
    }
  }

  fclose(fichier);
  return net;
}




void loadtest(int **input)
{
  FILE *file = fopen("test.tst", "r");

  int a = 0;
  int size;
  a += fscanf(file, "%d", &size);
  fgetc(file);
  input[0] = malloc(sizeof(int)*size);
  input[1] = malloc(sizeof(int)*size);
  char c;
  for( int i = 0; i < 16*16; i++)
  {
    c = fgetc(file);
    input[0][i] = 1 ? c== '1' : 0;
  }
  fgetc(file);
  for(int i = 0; i < 16*16; i++)
  {
    c = fgetc(file);
    input[1][i] = 1 ? c == '1' : 0;
  }
}
