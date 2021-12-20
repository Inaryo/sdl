#include "../headers/defs.h"

void DestroyWindow(App app) {

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);  
    

}

void DestroyWindowAndQuit(App app) {

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();

}

App createWindowAndRenderer(char page[50],int width,int height ) {
    
    App app;
    if (width > 0 && height > 0 ) {
        app.window = SDL_CreateWindow("Jeux de Droite",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,0 );
    } else {
        app.window = SDL_CreateWindow("Jeux de Droite",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,0 );
    }
    
    


    if (!app.window) {
        fprintf(stderr,"Failed to open the Home Page Window %s\n",SDL_GetError());
        DestroyWindowAndQuit(app);
        return app;
    }

    strncpy(app.page,page,sizeof(app.page));

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
    app.renderer = SDL_CreateRenderer(app.window,-1,SDL_RENDERER_ACCELERATED);

    

    if (app.renderer == NULL) {
        fprintf(stderr,"Failed to create a renderer %s\n",SDL_GetError());
        DestroyWindowAndQuit(app);
        return app;
    }
    
    return app;
    
}
