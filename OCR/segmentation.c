# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# include "segmentation.h"

void Terminus(int *mat, int line, int cols){
  for(int i = 0; i < line; i++){
    for(int j = 0; j < line; j++){
      mat[j + i * cols] = !mat[j + i * cols];
    }
  }
}

void segmentation(int    *mat, int line, int cols, int *compteur)
{

// create the horizontal histogram:
// 1 if the line contains at least a black pixel and 0 if not.
    printf("\n");
    int histo[line];
    for (int i = 0; i < line; i++)
    {
        histo[i] = 0;
    }

    for (int i = 0; i < line; i++)
    {
        int j = 0;

        while (j < cols && mat[j+i*cols]!=1)
        {
            j++;
        }
        if (j<cols)
        {
                histo[i] = 1;
        }
        //printf("%d", histo[i]);
    }

// cut the matrice into lines with text (in block)
    int i = 0;
    while(i < line)
    {
        if(histo[i]==1)
        {
            int begin = i;
            int acc = 0;
            while(i!=line && histo[i]==1)
            {
                acc ++;
                i += 1;
            }
            int *mat_line = malloc(sizeof(int) * cols * acc);

            int end = begin + acc;
            int k = 0;
            for(; begin < end; begin++)
            {
                for(int n = 0; n < cols; n++)
                {
                    mat_line[n + k * cols] = mat[n + begin * cols];

                }
                k++;
            }
            vertical_segmentation(mat_line, acc , cols,compteur);
            free(mat_line);
        }
        i++;
    }
}

                // DELETE WHITE 

void deleteWhite(int *mat, int line, int cols,int *compteur){
  // create histogramme
  int histo[line];
  for(int i = 0; i < line; i++)
    histo[i] = 0;
  for(int i = 0; i < line; i++){
    int j = 0;
    while(j < cols && mat[j+i*cols]!=1){
      j++;
    }
    if(j < cols){
      histo[i] = 1;
    }
  }
 
  int i = 0;
    while(i < line)
    {
        if(histo[i]==1)
        {
            int begin = i;
            int acc = 0;
            while(i!=line && histo[i]==1)
            {
                acc ++;
                i += 1;
            }
            int *mat_line = malloc(sizeof(int) * cols * acc);

            int end = begin + acc;
            int k = 0;
            for(; begin < end; begin++)
            {
                for(int n = 0; n < cols; n++)
                {
                    mat_line[n + k * cols] = mat[n + begin * cols];

                }
                k++;
            }
            fabulous_make_square(mat_line, acc, cols,compteur);
            free(mat_line);
        }
        i++;
    }
 
  // get out of here fcking 0s
  //printf("test1.1\n");
  /*int begin = 0;
  int end = line;
  for(; histo[begin] == 0; begin++)
    continue;
  for(; histo[end] == 0; end--)    
    continue;
  int *result = malloc(sizeof(int) * cols * (end-begin));
  int k = 0;
  for(; begin < end; begin++){
    for(int n = 0; n < cols; n++){
      result[n + k * cols] = mat[n + begin * cols];
    }
    k++;
  }
  print_mat(result, end-begin, cols);
  printf("test1.2\n");*/ 
  //fabulous_make_square(result, end-begin, cols);

/*
  printf("\n");
  print_mat(result, end-begin, cols);*/

}

void fabulous_make_square(int* mat, int line, int cols,int *compteur){
  if (line > cols)
  {
    int decalage = (line-cols)/2;
    int* res = malloc(sizeof(int)*line *line);
    for(int i = 0; i < line; i++)
    {
       for(int j = 0 ; j < line; j++)
       {
        if(j < decalage || j > decalage -1 + cols){
          res[j + i * line] = 0;
        }
        else{
          res[j + i * line] = mat[(j - decalage) + i * cols];
        }
      }
    }  
    printf("\n");
    int* final = resizePixels(res, line, line, 32, 32,compteur);
    Terminus(final, 32, 32);
    print_mat(final, 32, 32);
    save("arial.tst", final, 32, 32);
    free(final);
    free(res);
  }
  if(cols >= line){
    int decalage = (cols-line)/2;
    int* res = malloc(sizeof(int)*cols*cols);
    for(int i = 0; i < cols; i++){
      for(int j = 0; j < cols; j++){
        if(i < decalage || i > decalage -1 + line){
          res[j + i * cols] = 0;
        }
        else{
          res[j + i * cols] = mat[j + (i - decalage) * cols];
        }
      }
    }
    printf("\n");
    int* final = resizePixels(res, cols, cols, 32, 32,compteur);
    Terminus(final, 32, 32);
    print_mat(final, 32, 32);
    save("arial.tst", final, 32, 32);
    free(final);
    free(res);
  }
}

void vertical_segmentation(int *mat, int line, int cols,int *compteur)
{

// create the vertical histogram:
//same as before
    int histo[cols];
    for (int i = 0; i < cols; i++)
        histo[i] = 0;
    for (int j = 0; j < cols; j ++)
    {
        int i = 0;
        while(i < line && mat[j+i*cols]!=1)
        {
            i++;
        }
        if( i< line)
            histo[j] = 1;
    }

// How many characters and medium size of a character

    int total_size = 0;
    int nbr_letters = 0;
    for(int i = 0; i < cols; i++){
      if(histo[i] == 1){
        while(i != cols && histo[i] == 1){
          total_size++;
          i++;
        }
        nbr_letters ++;
      }
    }
    // ratio
    double ratio = (double)total_size/(double)nbr_letters;


// cut the lines into single character
    int j = 0;
    int space_length = 0;
    int test1 = 0; // bool test if the space is already treated
    int test2 = 0; // bool test if the first 0 are passed
    while(j < cols)
    {
      if (histo[j] == 1)
      {
          test2 = 1;
          space_length = 0;
          int begin = j;
          int acc = 0;
          while(j!= cols && histo[j] == 1)
          {
              j++;
              acc++;
          }
          int *charactere = malloc(sizeof(int) * line * acc);
          int k = 0;
          int end = begin + acc;
          for(; begin < end ; begin ++)
          {
            for(int n = 0 ; n < line ; n++)
              {
                  charactere[k + n * acc] = mat[begin + n * cols];
              }
              k++;
          }
            
            // ajouter le resize avant

            // ====================== 
            //  neronal network call  
            // ====================== 
          
          deleteWhite(charactere, line, acc,compteur);
          free(charactere);
      }
      space_length ++;
      j++;
      space_length = (double)j - space_length; // size of a space
      if(test2&&!test1 && space_length > (ratio/3) && space_length < (ratio*3)){
        int *space = createMatrice(2, 32, 32);
        test1 = 1;
        save("arial.tst", space, 32, 32);
        //affichage
        printf("\n");
        print_mat(space, 32, 32);
        free(space);
        *(compteur) += 1;
      }
    }
    
    int *line_change = createMatrice(3, 32, 32);
    printf("\n");
    print_mat(line_change, 32, 32);
    save("arial.tst", line_change, 32, 32);
    free(line_change);
    *(compteur) += 1;
}

// The function resize a matrice
// w1,h1: width and height of the input matrice
// w2,h2: width and height of the output matrice
// int* size: number of characters
int* resizePixels(int *pixels, int w1, int h1, int w2, int h2,int *compteur)
{
    if(w2*h2 == 0){
        printf("height and width must be different of 0");
        return 0;
    }
    *(compteur) += 1;

    int *result = malloc(sizeof(int)*w2*h2);
    double x_ratio = w1/(double)w2;
    double y_ratio = h1/(double)h2;
    int x;
    int y;

    for(int i = 0; i < h2; i++)
    {
        for(int j = 0; j < w2; j++)
        {
            x = floor(j*x_ratio);
            y = floor(i*y_ratio);
            result[(i*w2)+j] = pixels[(int)(y*w1)+x];
        }
    }
    return result;
}

// Create a matrice(line * col) of a number
int* createMatrice(int number, int line, int col){
  int *mat = malloc(sizeof(int) * line * col);
  for(int i = 0; i < col; i++){
    for(int j = 0; j < line; j++){
      mat[i + j * col] = number;
    }
  }
  return mat;
}

// The function prints the matrice with the width and the height
void print_mat(int *mat, int line, int col)
{
    for (int i = 0; i< line; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d", mat[j+i*col]);
        }
        printf("\n");
    }
}

// The function prints the linear matrice
void print_linear(int *mat, int line, int col){
  for (int i = 0; i < line; i++){
    for(int j = 0; j < col; j++){
      printf("%d", mat[j+i*col]);
    }
  }
}

// The function save the different matrices into a file
void save(char *chemin, int* mat, int line, int col){
  //strcat(chemin, ".save");
  FILE *fichier = fopen(chemin, "a");
  for(int i = 0; i < line; i++){
    for(int j = 0; j < col; j++){
      fprintf(fichier, "%d", mat[j+i*col]);
    }
  }
  fprintf(fichier, "\n");
  fclose(fichier);
}
