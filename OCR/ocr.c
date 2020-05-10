#include <stdlib.h>
#include <stdio.h>

#include "ocr.h"

void OCR(char *filename)
{
  if(filename == NULL)
  {
    printf("No filename\n");
    return;
  }

  /**************
    Segmentation
  **************/

  SDL_Surface *image = load_image(filename);
  int line = image->h;
  int cols = image->w;
  int *matbin = malloc(sizeof(int) * line * cols);
  int *compteur = malloc(sizeof(int));
  FILE *file = fopen("arial.tst","w");
  fclose(file);
  *compteur = 0;

  matbin = Otsu_Method(image);
  print_mat(matbin,line,cols);
  segmentation(matbin,line,cols,compteur);
  
  SDL_FreeSurface(image);
  
  /******
    NN
  *******/
  
  int nbinput = *compteur;
  int **input = malloc(sizeof(int *) * nbinput);

  FILE *fileRES = fopen("result.ocr","w");
 
  loadtest(input,nbinput);
  
  network *net = load("arial.net");

  char res[91] = "!#$%&()*+-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}~";
  
  for(int i = 0; i < nbinput; i++)
  {
    char c;
    if(input[i][0] == 2)
      c = ' ';
    else if(input[i][0] == 3)
      c = '\n';
    else
      c = foundletter(net,input[i],res);
    
    fputc(c,fileRES);
    printf("%c\n",c);
  }

//  writeRes(net,input,fileRES,nbinput);
  
  for(int i = 0; i < nbinput; i++)
    free(input[i]);

  free(input);
  free(matbin);
  free(compteur);
  fclose(fileRES);
  killNetwork(net);
}

/*void writeRes(network *net,int **input,FILE *fileRES, int nbinput)
{
  char res[91] = "!#$%&()*+-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}~";
  
  for(int i = 0; i < nbinput; i++)
  {
    char c;
    if(input[i][0] == 2)
      c = ' ';
    else if(input[i][0] == 3)
      c = '\n';
    else
      c = foundletter(net,input[i],res);
    
    fputc(c,fileRES);
    printf("%c\n",c);
  }
}*/
