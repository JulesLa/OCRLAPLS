#include "save.h"
#include "string.h"

void save_net(char *chemin, network *net)
{
  strcat(chemin,".ntw");
  FILE *fichier = fopen(chemin, "w");
  fprintf(fichier, "%d\n", net->nblayer);

  for(int i = 0; i < net->nblayer; i++)
  {
    fprintf(fichier, "%d ", net->layersize[i]);
  }
  fprintf(fichier, "\n");

  for(int i = 0; i < net->nblayer-1; i++)
  {
    for(int j = 0; j < net->layersize[i]; j++)
    {
      for(int k = 0; k < net->layersize[i+1]; k++)
      {
        fprintf(fichier, "%lf ", net->layer[i][j].weight[k]);
      }
      fprintf(fichier, "\n");
    }
  }

  fclose(fichier);
}


/*network * load(char *chemin)
{
  strcat(chemin, ".ntw");
  FILE *fichier = fopen(chemin, "r");
  
  if(fichier == NULL)
  {
    printf("/!\\ Problem with the file /!\\\n\n");
    return NULL;
  }

  int a = 0;
  int nblayer = 1024;
  int *layersize = malloc(sizeof(int)*nblayer);
  for(int i = 0; i < nblayer; i++)
  {
    a += fscanf(fichier, "%d", &layersize[i]);
    fgetc(fichier);
  }
  
  network *net = initNetwork(nblayer, layersize);
  for(int i = 0; i < net->nblayer-1; i++)
  {
    for(int j = 0; j < net->layersize[i]; j++)
    {
      for(int k = 0; k < net->layersize[i+1]; k++)
      {
        a += fscanf(fichier, "%lf", &net->layer[i][j].weight[k]);
        fgetc(fichier);
      }
      fgetc(fichier);
    }
  }
  free(layersize);
  if (!a) return NULL;

  fclose(fichier);
  return net;
}*/

network *load(char *chemin)
{
  FILE *fichier = fopen(chemin, "r");

  int a = 0;
  int nblayer;
  fscanf(fichier,"%d\n",&nblayer);
  int *layersize = malloc(sizeof(int)*nblayer);
  for(int i = 0; i < nblayer; i++)
  {
    a += fscanf(fichier, "%d/", &layersize[i]);
  }
  fgetc(fichier);
  network *net = initNetwork(nblayer, layersize);

  for(int i = 0; i < net->nblayer-1; i++)
  {
    for(int j = 0; j < net->layersize[i]; j++)
    {
      for(int k = 0; k < net->layersize[i+1]; k++)
      {
        a += fscanf(fichier, "/%lf", &net->layer[i][j].weight[k]);
      }
    }
  }

 // result = malloc(sizeof(char) * layersize[nblayer-1]);
  //free(layersize);
 /* for(int z = 0; z < layersize[nblayer-1]; z++)
  {
    *(result+z) = fgetc(fichier);
  }*/
  //free(layersize);
  if(!a) 
    return NULL;

  fclose(fichier);
  return net;
}


void loadtest(int **input, int nbinput)
{
  FILE *file = fopen("arial.tst", "r");

  int size = 1024;
  char c;
  
 // a += fscanf(file, "%d", &size);
  //fgetc(file);

  for(int i = 0; i < nbinput; i++)
  {
    input[i] = malloc(sizeof(int)*size);
    for(int j = 0; j < size; j++)
    {
      c = fgetc(file);
      if(c == '1')
        input[i][j] = 1;
      else if(c == '0')
        input[i][j] = 0;
      else if(c == '2')
        input[i][j] = 2;
      else if(c == '3')
        input[i][j] = 3;
    }
    fgetc(file);
  }
}
