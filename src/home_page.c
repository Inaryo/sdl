
#include "../headers/defs.h"
#include "../headers/other.h"
#include "../headers/name_page.h"
#include "../headers/launch_page.h"
#include "../headers/home_page.h"


App app;
SDL_Rect  buttonPlayRect,buttonAutoPlayRect,buttonScoresRect,buttonExitRect;
SDL_Point positionClick;
SDL_Surface *buttonPlayImage, *buttonAutoPlayImage, *buttonScoresImage,*buttonExitImage;
SDL_Texture *buttonPlayTexture, *buttonAutoPlayTexture, *buttonScoresTexture,*buttonExitTexture;
char savingFilePath[] = "saved.dat";

App createHomePage() {

    app = createWindowAndRenderer("home",SCREEN_WIDTH,SCREEN_HEIGHT);

    createBackground();
    createHomeButtons();    
    return app;
}

void createBackground() {

    SDL_Surface *backgroundImage;
    SDL_Texture *backgroundTexture;
    SDL_Rect backgroundRect;

    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.h = SCREEN_HEIGHT;
    backgroundRect.w = SCREEN_WIDTH;

    backgroundImage = loadImage("img/home/home-screen.bmp");
        if (!backgroundImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        backgroundTexture = SDL_CreateTextureFromSurface(app.renderer, backgroundImage);
        SDL_FreeSurface(backgroundImage);
        if(NULL == backgroundTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,backgroundTexture,NULL,&backgroundRect);

}


void createHomeButtons() {

        // Create the Image of Play
        buttonPlayRect.x = 748;
        buttonPlayRect.y = 287;
        buttonPlayRect.w = BUTTONS_WIDTH;
        buttonPlayRect.h = BUTTONS_HEIGHT;

        buttonPlayImage = loadImage("img/home/button_play.bmp");
        if (!buttonPlayImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonPlayTexture = SDL_CreateTextureFromSurface(app.renderer, buttonPlayImage);
        SDL_FreeSurface(buttonPlayImage);
        if(NULL == buttonPlayTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonPlayTexture,NULL,&buttonPlayRect);
        


        // Create the Button of AutoPlay
        buttonAutoPlayRect.x = 748;
        buttonAutoPlayRect.y = 475;
        buttonAutoPlayRect.w = BUTTONS_WIDTH;
        buttonAutoPlayRect.h = BUTTONS_HEIGHT;

        buttonAutoPlayImage = loadImage("img/home/button_autoplay.bmp");
        if (!buttonAutoPlayImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonAutoPlayTexture = SDL_CreateTextureFromSurface(app.renderer, buttonAutoPlayImage);
        SDL_FreeSurface(buttonAutoPlayImage);
        if(NULL == buttonAutoPlayTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonAutoPlayTexture,NULL,&buttonAutoPlayRect);
        

        // Create the Button of Scores
        buttonScoresRect.x = 748;
        buttonScoresRect.y =  676;
        buttonScoresRect.w = BUTTONS_WIDTH;
        buttonScoresRect.h = BUTTONS_HEIGHT;

        buttonScoresImage = loadImage("img/home/button_scores.bmp");
        if (!buttonScoresImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonScoresTexture = SDL_CreateTextureFromSurface(app.renderer, buttonScoresImage);
        SDL_FreeSurface(buttonScoresImage);
        if(NULL == buttonScoresTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonScoresTexture,NULL,&buttonScoresRect);


        // Create the Button of Exit
        buttonExitRect.x = 748;
        buttonExitRect.y =  867;
        buttonExitRect.w = BUTTONS_WIDTH;
        buttonExitRect.h = BUTTONS_HEIGHT;

        buttonExitImage = loadImage("img/home/button_exit.bmp");
        if (!buttonExitImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonExitTexture = SDL_CreateTextureFromSurface(app.renderer, buttonExitImage);
        SDL_FreeSurface(buttonExitImage);
        if(NULL == buttonExitTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonExitTexture,NULL,&buttonExitRect);
        SDL_RenderPresent(app.renderer);

        
}

void HomePageEvent(SDL_Event event) {

    

    if (strcmp(app.page,"home") == 0) {
            switch (event.type)
            {
            
            case SDL_MOUSEBUTTONDOWN: 
            
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        
                        positionClick.x = event.button.x;
                        positionClick.y = event.button.y;
                        
                        if (SDL_PointInRect(&positionClick,&buttonPlayRect) == 1) {
                            DestroyWindow(app);
                            createLaunchPage();
                        } else if (SDL_PointInRect(&positionClick,&buttonAutoPlayRect) == 1) {
                            
                        } else if (SDL_PointInRect(&positionClick,&buttonScoresRect) == 1) {

                        } else if (SDL_PointInRect(&positionClick,&buttonExitRect) == 1) {
                            DestroyWindowAndQuit(app);
                        }

                        
                    }
                    break;

            default:
                break;
            }
    }

    
}

