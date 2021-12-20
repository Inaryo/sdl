#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* loadImage(char *path) {

    SDL_Surface *image = SDL_LoadBMP(path);
    
	if(!image)
	{
		/* image failed to load */
		printf("IMG_Load: %s\n", IMG_GetError());
		return image;
    }
	return image;

}


