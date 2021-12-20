
#include "../headers/defs.h"
#include "../headers/other.h"
#include "../headers/launch_page.h"

App app;
char inputText[50] = "Your Name";
SDL_Rect  buttonLaunchRect,buttonBackRect;
SDL_Point positionClick;
SDL_Surface *buttonLaunchImage, *buttonBackImage;
SDL_Texture *buttonLaunchTexture, *buttonBackTexture;
int renderText = 0;



SDL_Color White = {255, 255, 255};

TTF_Font* sans = NULL;
SDL_Surface* surfaceMessage = NULL; 
SDL_Texture* message;
SDL_Rect message_rect; 

void createNamePage() {

    
    app = createWindowAndRenderer("name",SCREEN_WIDTH,SCREEN_HEIGHT);

    sans = TTF_OpenFont("fonts/Sans.ttf", 14);
    if (sans == NULL) {
        
    };
    surfaceMessage = TTF_RenderText_Solid(sans, &inputText, White);

    message = SDL_CreateTextureFromSurface(app.renderer, surfaceMessage);
    //create a rect
    message_rect.x = 0;  //controls the rect's x coordinate 
    message_rect.y = 0; // controls the rect's y coordinte
    message_rect.w = 500; // controls the width of the rect
    message_rect.h = 100;

    createNameButtons();

    SDL_RenderCopy(app.renderer, message, NULL, &message_rect);
    SDL_RenderPresent(app.renderer);
    

}

void createNameButtons() {
        buttonLaunchRect.x = 100;
        buttonLaunchRect.y = 100;
        buttonLaunchRect.w = BUTTONS_WIDTH;
        buttonLaunchRect.h = BUTTONS_HEIGHT;

        buttonLaunchImage = loadImage("img/home/button_play.bmp");
        if (!buttonLaunchImage) {
            fprintf("error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonLaunchTexture = SDL_CreateTextureFromSurface(app.renderer, buttonLaunchImage);
        SDL_FreeSurface(buttonLaunchImage);
        if(NULL == buttonLaunchTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonLaunchTexture,NULL,&buttonLaunchRect);
        


        // Create the Button of Stat
        buttonBackRect.x = 100;
        buttonBackRect.y = 100 + BUTTONS_HEIGHT + BUTTONS_MARGIN;
        buttonBackRect.w = BUTTONS_WIDTH;
        buttonBackRect.h = BUTTONS_HEIGHT;

        buttonBackImage = loadImage("img/home/button_play.bmp");
        if (!buttonBackImage) {
            fprintf("error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        buttonLaunchTexture = SDL_CreateTextureFromSurface(app.renderer, buttonBackImage);
        SDL_FreeSurface(buttonBackImage);
        if(NULL == buttonLaunchTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,buttonLaunchTexture,NULL,&buttonBackRect);
        
}



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
                
                if (SDL_PointInRect(&positionClick,&buttonLaunchRect) == 1) {
                    
                    SDL_DestroyWindow(app.window);
                    createLaunchPage();

                } else if (SDL_PointInRect(&positionClick,&buttonBackRect) == 1) {
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
}