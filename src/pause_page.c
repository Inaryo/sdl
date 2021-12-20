
#include "../headers/defs.h"
#include "../headers/other.h"
#include "../headers/launch_page.h"

App app;
SDL_Rect  buttonSaveRect,buttonRetryRect,buttonContinueRect;
SDL_Point positionClick;
SDL_Surface *buttonSaveImage, *buttonRetryImage,*buttonContinueImage;
SDL_Texture *buttonRetryTexture, *buttonBackTexture,*buttonContinueTexture;
SDL_Event event;






void createPausePage() {

    
    app = createWindowAndRenderer("pause",1920,1080);

    createPauseBackground();
    createPauseButtons();



    SDL_RenderPresent(app.renderer);

    while (1) {
        SDL_WaitEvent(&event);
       // PausePageEvents(event);
    }
    

}

void createPausePageButtons() {

        // Create the Button of Save
        buttonSaveRect.x = 1063;
        buttonSaveRect.y = 102;
        buttonSaveRect.w = 100;
        buttonSaveRect.h = 100;

        buttonSaveImage = loadImage("img/pause/button_save.bmp");
        if (!buttonSaveImage) {
            fprintf("error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonRetryTexture = SDL_CreateTextureFromSurface(app.renderer, buttonSaveImage);
        SDL_FreeSurface(buttonSaveImage);
        if(NULL == buttonRetryTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonRetryTexture,NULL,&buttonSaveRect);
        


        // Create the Button of Retry
        buttonRetryRect.x = 1196;
        buttonRetryRect.y = 102 ;
        buttonRetryRect.w = 100;
        buttonRetryRect.h = 100;

        buttonRetryImage = loadImage("img/pause/button_retry.bmp");
        if (!buttonRetryImage) {
            fprintf("error in loading the image %s", SDL_GetError());
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
            fprintf("error in loading the image %s", SDL_GetError());
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



void createPauseBackground() {

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
            
                   /* if (event.button.button == SDL_BUTTON_LEFT) {
                        
                        positionClick.x = event.button.x;
                        positionClick.y = event.button.y;
                        
                        for (int i = 0; i < 6; i++)
                        {
                            for (int j = 0; j < 6; j++)
                            {
                                if (SDL_PointInRect(&positionClick,&rectBlocMatrice[i][j]) == 1) {
                                        fprintf(stderr,"in");
                                        changeBlocPath(i,j);
                                        break;  
                                }
                            }
                            
                        }

                        if (SDL_PointInRect(&positionClick,&pauseButtonRect)) {
                            createPausePage();
                        } else if (SDL_PointInRect(&positionClick,&homeButtonRect)) {
                            DestroyWindow(app);
                            createHomePage();
                        };
                        
                        
                    }*/
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