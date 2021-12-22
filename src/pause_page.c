
#include "../headers/defs.h"
#include "../headers/other.h"
#include "../headers/launch_page.h"
#include "../headers/pause_page.h"


App app;
struct SaveGame game;
SDL_Rect  buttonSaveRect,buttonRetryRect,buttonContinueRect;
SDL_Point positionClick;
SDL_Surface *buttonSaveImage, *buttonRetryImage,*buttonContinueImage;
SDL_Texture *buttonRetryTexture, *buttonSaveTexture,*buttonContinueTexture;
SDL_Event event;

int play_retry;



void createPausePage(struct SaveGame save) {
    game = save;
    app = createWindowAndRenderer("pause",1920,1080);

    createPausePageBackground();
    createPausePageButtons();



    SDL_RenderPresent(app.renderer);
}


int saveGame() {
                
                FILE* file = fopen(savingFilePath , "wb+");
                if (!file) return 0;

                if( (fwrite (&game, sizeof(struct SaveGame), 1, file)) != 0)
                    fprintf(stderr,"Play saved successfully !\n");
                else
                    fprintf(stderr,"error writing file !\n");
            
                fclose (file); 
                return 1; 

}
void createPausePageButtons() {

        // Create the Button of Save
        buttonSaveRect.x = 1063;
        buttonSaveRect.y = 102;
        buttonSaveRect.w = 100;
        buttonSaveRect.h = 100;

        buttonSaveImage = loadImage("img/pause/button_save.bmp");
        if (!buttonSaveImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonSaveTexture = SDL_CreateTextureFromSurface(app.renderer, buttonSaveImage);
        SDL_FreeSurface(buttonSaveImage);
        if(NULL == buttonSaveTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonSaveTexture,NULL,&buttonSaveRect);
        


        // Create the Button of Retry
        buttonRetryRect.x = 1196;
        buttonRetryRect.y = 102 ;
        buttonRetryRect.w = 100;
        buttonRetryRect.h = 100;

        buttonRetryImage = loadImage("img/pause/button_retry.bmp");
        if (!buttonRetryImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonRetryTexture = SDL_CreateTextureFromSurface(app.renderer, buttonRetryImage);
        SDL_FreeSurface(buttonRetryImage);
        if(NULL == buttonRetryTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonRetryTexture,NULL,&buttonRetryRect);


        // Create the Button of Continue
        buttonContinueRect.x = 1350;
        buttonContinueRect.y = 96;
        buttonContinueRect.w = 100;
        buttonContinueRect.h = 100;

        buttonContinueImage = loadImage("img/pause/button_continue.bmp");
        if (!buttonContinueImage) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonContinueTexture = SDL_CreateTextureFromSurface(app.renderer, buttonContinueImage);
        SDL_FreeSurface(buttonContinueImage);
        if(NULL == buttonContinueTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonContinueTexture,NULL,&buttonContinueRect);
        
}



void createPausePageBackground() {

    SDL_Surface *backgroundImage;
    SDL_Texture *backgroundTexture;
    SDL_Rect backgroundRect;

    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.h = SCREEN_HEIGHT;
    backgroundRect.w = SCREEN_WIDTH;

    backgroundImage = loadImage("img/pause/pause-screen.bmp");
        
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




void PausePageEvents(SDL_Event event) {


    if (strcmp(app.page,"pause") == 0) {
            switch (event.type)
            {
            
            case SDL_QUIT:
                DestroyWindowAndQuit(app);
            break;
            case SDL_MOUSEBUTTONDOWN: 
            
                   if (event.button.button == SDL_BUTTON_LEFT) {
                        
                        positionClick.x = event.button.x;
                        positionClick.y = event.button.y;
                        
                        if (SDL_PointInRect(&positionClick,&buttonSaveRect)) {
                                if(saveGame() == 1) {
                                        play_retry = 0;  
                                        DestroyWindow(app);
                                        createLaunchPage(0);
                                }
                                
                        
                        } else if (SDL_PointInRect(&positionClick,&buttonRetryRect)) {
                            
                            play_retry = 1;    
                            DestroyWindow(app);
                            createLaunchPage(1);
                            
                        } else if (SDL_PointInRect(&positionClick,&buttonContinueRect)) {
                            
                            if(saveGame() == 1) {
                                        play_retry = 0;  
                                        DestroyWindow(app);
                                        createLaunchPage(0);
                                }
                        };
                        
                        
                    }
                    break;
            }
    }

    
}


/*
void NamePageEvent(SDL_Event event) {
    renderText = 0;

    if (strcmp(app.page ,"name") == 0) {
    switch (event.type)
    {
    
    case SDL_KEYDOWN:
        if( event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0 )
                        {
                            //lop off character
                            inputText[strlen(inputText)-1] = '\0';
                            renderText = 1;
                        }
                        //Handle copy
                        else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                        {
                            SDL_SetClipboardText( &inputText );
                        };
                        
    break;

    case SDL_TEXTINPUT:
                    
                        //Not copy or pasting
                        if( !( SDL_GetModState() & KMOD_CTRL && ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' || event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) ) )
                        {
                            //Append character
                            strcat(inputText,event.text.text);
                            renderText = 1;
                        }
                    
    break;
    
    case SDL_MOUSEBUTTONDOWN: 
    
            if (event.button.button == SDL_BUTTON_LEFT) {
                
                positionClick.x = event.button.x;
                positionClick.y = event.button.y;
                
                if (SDL_PointInRect(&positionClick,&buttonSaveRect) == 1) {
                    
                    SDL_DestroyWindow(app.window);
                    createLaunchPage();

                } else if (SDL_PointInRect(&positionClick,&buttonRetryRect) == 1) {
                    SDL_DestroyWindow(app.window);
                    createHomePage();
                };

                
            }
            break;

    default:
        break;
    }

    if (renderText == 1) {
            
            SDL_DestroyTexture(message);
            SDL_RenderClear(app.renderer);
            createNameButtons();
            surfaceMessage = TTF_RenderText_Solid(sans, &inputText, White);


            message = SDL_CreateTextureFromSurface(app.renderer, surfaceMessage);
            SDL_RenderCopy(app.renderer, message, NULL, &message_rect);
            SDL_RenderPresent(app.renderer);

    }
    }
}*/