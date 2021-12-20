#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/defs.h"  


SDL_Surface* loadImage(char *path) {

    SDL_Surface *image = SDL_LoadBMP(path);
    
	if(!image)
	{
		/* image failed to load */
		fprintf(stderr,"IMG_Load: %s\n", SDL_GetError());
		return image;
    }
	return image;

}


