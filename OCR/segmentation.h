/* segmentation.h : segmentation header */

# ifndef SEGMENTATION_H
# define SEGMENTATION_H

# include <stdlib.h>

void segmentation(int *mat, int line, int cols,int *compteur);

void vertical_segmentation(int *mat, int line, int cols, int *compteur);

void fabulous_make_square(int* mat, int line, int cols, int *compteur);

void deleteWhite(int *mat, int line, int cols, int *compteur);

void print_mat(int *mat, int line, int col);

void print_linear(int *mat, int line, int col);

int* createMatrice(int number, int line, int col);

int* resizePixels(int *pixels, int w1, int h1, int w2, int h2, int *compteur);

void save(char *chemin, int *mat, int line, int col);

void Terminus(int *mat,int line,int cols);
# endif 
