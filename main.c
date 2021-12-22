#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "headers/home_page.h"
#include "headers/other.h"
#include "headers/launch_page.h"
#include "headers/name_page.h"
#include "headers/win_page.h"
#include "headers/pause_page.h"

     SDL_Texture *texture;
     SDL_Event event;
     App currentApp;

int initSDL() {

    if ( SDL_Init(SDL_INIT_VIDEO ) == -1) {
        fprintf(stderr,"Error in initialisation of SDL, Error : %s\n",SDL_GetError());
        return 0;
    };

    return 1;


}








int main(int argc, char *argv[]) {

    if (initSDL() == 0) {
        DestroyWindowAndQuit(currentApp);
    };
    
    TTF_Init();
    createHomePage();



    while(1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
                    SDL_Quit();
            };

        HomePageEvent(event);
        NamePageEvent(event);
        LaunchPageEvent(event);
        WinPageEvents(event);
        PausePageEvents(event);
        
    }

    return 0;
}


/* 
gcc -std=c17 main.c src/pause_page.c src/stat_page.c src/credits_page.c src/other.c src/name_page.c src/launch_page.c src/defs.c src/home_page.c -IF:\WebDev\Projects\sdl\SDL2\include -LF:\WebDev\Projects\sdl\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main
*/