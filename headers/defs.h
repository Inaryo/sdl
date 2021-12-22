#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED


        #define SCREEN_WIDTH 1920
        #define SCREEN_HEIGHT 1080
        #define BUTTONS_HEIGHT 110
        #define BUTTONS_WIDTH 424
        #define BUTTONS_MARGIN 20

        #define BUTTONS_BLOC_WIDTH 135
        #define BUTTONS_BLOC_HEIGHT 135

        extern int is_play_paused;
        extern int play_saving;
        extern char savingFilePath;

        #include <time.h>                
        #include <stdlib.h>
        #include <stdio.h>        
        #include <string.h>
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
        SDL_Surface* loadImage(char *path);

        typedef struct App {
                SDL_Window *window;
                SDL_Renderer *renderer;
                char page[50];
        } App;

#endif // DEFS_H_INCLUDED
