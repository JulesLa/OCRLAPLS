# include <stdlib.h>
# include <stdio.h>

# include "pixel_operations.h"
# include "segmentation.h"
# include <err.h>

# include <SDL.h>
# include <SDL_image.h>

# include "otsu.h"



void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}




void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}




SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}




SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
}

// BRUIT
/*
void moyenneFilter(SDL_Surface *img){
  double somme = 0;
  // Run the matrice
  for(int x = 1; x < img->(w-1); x++){
    for(int y = 1; y < img->(h-1); y++){
      // Run the 3x3 matrice
      for(int i = x-1; i < i+2; i++){
        for(int j = y-1; j < j+2; j++){
          somme += //niveau de gris du pixel[i,j];
          //pixel[x,y] = somme / 9;
        }
      }
      somme = 0;
    }
  }
}*/
/*
// initialize the list
void list_init(struct list *list){
  list->next = NULL;
  list->value = 0;
}

// check if the list is empty
int list_is_empty(struct list *list){
  if(list->next != NULL){
    return 0;
  return 1;
}

// insert in a sorted way  an element 
void list_insert(struct list *list, int value){
  struct list *elm = malloc(sizeof(struct list));
  elm->next = NULL;
  elm->value->value;
  if(list_is_empty(list))
    list->next = elm;
  else{
    for(; list->next != NULL && list->next->value < elm->data; list = list->next)
      continue;
    elm->next = list->next;
    list->next = elm;
  }
}

// return the length of the list
int list_len(struct list *list){
  int i = 0;
  if(!(list_is_empty(list))){
    for(; list->next != NULL; list = list->next){
      i++;
    }
  }
  return i;
}

// return the value of the median element in the list
int medianValue(struct list *list){
  for(int i = 0; i < 5; i++){
    list  = list->next;
  }
  return list->value;
}

// Fonction that implements the median filter to reduce the noise in an image
void medianFilter(SDL_Surface *img){
  struct list *list = malloc(sizeof(struct list));
  // Run the matrice
  for(int i = 0; i < img->h;  i++){
    for(int j = 0; i < img->w; j++){
      // Run the 3x3 matrice
      for(int x = ; x < ; x + img->w){
        for(int y = ; y < y + 3; y++){
          list_insert(list, );
        }
      }
    }
  }
  int result = medianValue(list);
  = result;
}*/


// Otsu's Algorithm
// Transform a classic image into a black and white one
int*  Otsu_Method(SDL_Surface *img)
{
    float hist[256] = {0.0F};
    Uint8 r,g,b;

    for (int x = 0; x < img->w; x++)
        {
            for (int y = 0; y < img-> h ; y++)
            {
                SDL_GetRGB(getpixel(img,x,y), img->format, &r, &g, &b);
                Uint8 graylevel = r* 0.3+ g* 0.59 + b*0.11;
                hist[graylevel] += 1;
            }
        }

    int nb_pixel = img->w * img->h;

    for(int i = 0; i<256; i++)
    {
        hist[i] /= nb_pixel;
    }

    float ut =0;
    for (int i=0; i<256; i++)
    {
        ut += i * hist[i];
    }

    int max_k = 0;
    int max_sigma_k_ = 0;

    for (int k = 0; k < 256; k++)
    {
        float wk = 0;
        for (int i = 0; i<= k ; i++)
        {
            wk += hist[i];
        }
        float uk = 0;
        for (int i=0; i<=k;i++)
        {
            uk += i*hist[i];
        }

        float sigma_k = 0;
        if(wk != 0 && wk != 1)
        {sigma_k = ((ut*wk-uk)*(ut*wk- uk))/(wk*(1-wk));}

        if (sigma_k > max_sigma_k_)
        {
            max_k = k;
            max_sigma_k_ = sigma_k;
        }
    }

// binarize the image into a 0 and 1 matrice (0 = white, 1 = black)
    int *binarization = malloc(sizeof(int) * img->w * img->h);
    int test = 0;
    int acc0 = 0; // blanc
    int acc1 = 0; // noir
    for(int y = 0; y < img->h; y++)
    {
        for (int x = 0; x < img->w; x++)
        {
            SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
            Uint8 graylevel = r * 0.3 + g * 0.59 + b * 0.11;

            if (graylevel <max_k)
            {
                putpixel(img, x, y, SDL_MapRGB(img -> format, 0,0,0));
                binarization[(y*(img->w))+x] = 1;
                acc1++;
            }
            else
            {
                putpixel(img, x, y, SDL_MapRGB(img -> format,255,255,255));
                binarization[(y*(img->w))+x] = 0;
                acc0++;
            }
            test++;
        }
    }

    // inversion of the colors
    if(acc1 > acc0){
      for(int i = 0; i < img->w; i++){
        for(int j = 0; j < img->h; j++){
          if(binarization[(j*(img->h))+i] == 1)
            binarization[(j*(img->h))+i] = 0;
          else
            binarization[(j*(img->h))+i] = 1;
        }
      }
    }
    //printf("test : %d \n" , test);
    return binarization;
}
