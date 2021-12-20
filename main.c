#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "headers/home_page.h"
#include "headers/other.h"
#include "headers/launch_page.h"


     SDL_Texture *texture;
     SDL_Event event;
     App currentApp;

int initSDL() {

    if ( SDL_Init(SDL_INIT_VIDEO ) == -1) {
        fprintf(stderr,"Error in initialisation of SDL, Error : %s\n",SDL_GetError());
        return 0;
    };

    

    TTF_Init();
    
   

    return 1;


}








int main() {

    if (initSDL() == 0) {
        DestroyWindowAndQuit(currentApp);
    };
    

    createHomePage();



    while(1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
                    SDL_Quit();
            };

        HomePageEvent(event);
        NamePageEvent(event);
        LaunchPageEvent(event);
        
    }

    return 0;
}


