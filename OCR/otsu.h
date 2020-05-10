/* segmentation.h : segmentation header */

# ifndef OTSU_H
# define OTSU_H

# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <err.h>

/*
struct list {
  struct list *next;
  int value;
};*/

void wait_for_keypressed(void);
void init_sdl(void);
SDL_Surface* load_image(char *path);
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
int* Otsu_Method(SDL_Surface *img);
void moyenneFilter(SDL_Surface *img);

#endif
