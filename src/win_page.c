#include "../headers/win_page.h"   
#include "../headers/other.h" 
#include "../headers/home_page.h" 

    App app;
    SDL_Point positionClick;

    SDL_Rect tempRect,homeButtonRect;
    SDL_Texture *homeButtonTexture;
    SDL_Surface *homeButtonSurface;
    FILE* file;
    char path[] = "scores.dat";

    
    App createWinPage(int score,char name[50]) {

        app = createWindowAndRenderer("win",SCREEN_WIDTH,SCREEN_HEIGHT);

        createWinBackground();
        createWinPageButtons();  
        SavePlayerScore(name,score);  
        displayScores(score);
        fprintf(stderr,"score ramzi %d",scoreByName("ramzi"));


        SDL_RenderPresent(app.renderer);
        return app;
    
    }

    int scoreByName(char name[50]){
        FILE* file = fopen(path, "ab+");
        struct ScoreBoard input;

        while(fread(&input, sizeof(struct ScoreBoard), 1, file)) {
            if (strcmp(input.name,input.name) == 0) {
                return input.score;
            }
        } 

        fclose(file);
        return 0;
    }

    void displayScores(int actual_score) {

        TTF_Font* font = TTF_OpenFont("arial.ttf", 25);

        // this is the color in rgb format,
        // maxing out all would give you the color white,
        // and it will be your text's color
        SDL_Color color = {255, 255, 255};

        // as TTF_RenderText_Solid could only be used on
        // SDL_Surface then you have to create the surface first
        char scoreMessage[8] = "";

        sprintf(scoreMessage,"%d",actual_score);
        /*SDL_Surface* surfaceMessage =
            TTF_RenderText_Solid(font,scoreMessage , color); 

        // now you can convert it into a texture
        SDL_Texture* Message = SDL_CreateTextureFromSurface(app.renderer, surfaceMessage);

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = 979;  //controls the rect's x coordinate 
        Message_rect.y = 479; // controls the rect's y coordinte
        Message_rect.w = 100; // controls the width of the rect
        Message_rect.h = 100; // controls the height of the rect
        SDL_RenderCopy(app.renderer, Message, NULL, &Message_rect);

        // Don't forget to free your surface and texture
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);*/

    }


    void SavePlayerScore(char name[50],int score) {

        struct ScoreBoard player;
        strcpy(player.name,name);
        player.score = score;

        int exists = editPlayerScore(player);
        fprintf(stderr,"Nom %s ",player.name);

        if (exists == 0 ) {
                FILE* file = fopen(path, "ab+");
                
                
                if( (fwrite (&player, sizeof(struct ScoreBoard), 1, file)) != 0)
                    fprintf(stderr,"contents to file written successfully !\n");
                else
                    fprintf(stderr,"error writing file !\n");
            
                // close file
                fclose (file);
        }
        
    }

    int editPlayerScore(struct ScoreBoard player) {
        FILE* file = fopen(path, "r+b");
        struct ScoreBoard input;

        while(fread(&input, sizeof(struct ScoreBoard), 1, file)) {
            if (strcmp(input.name,player.name) == 0) {
                if (input.score >= player.score) {
                    player.score = input.score;
                    
                } else {
                    fprintf(stderr,"meilleur temps");
                }
                fseek(file, ftell(file) - sizeof(player), SEEK_SET);
                fwrite(&player, sizeof(player), 1, file);
                fclose(file);
                fprintf(stderr,"file edited with success");
                return 1;
            }
        } 

        fclose(file);
        return 0;
        
        

    }

    int bestScore() {
        FILE* file = fopen(path, "r+b");
        struct ScoreBoard input;
        int best = 0; 

        while(fread(&input, sizeof(struct ScoreBoard), 1, file)) {
           
                if (input.score >= best) {
                    best = input.score;
                }
                
            }
            fclose(file);
            return best;
        
    }


    

    /*int isFirstMore(struct ScoreBoard score_board_1, struct ScoreBoard score_board_2){

            int score_1, score_2;
            score_1  = score_board_1.score;
            score_2  = score_board_2.score ;
            if (score_1 < score_2)
                return 1;
            else if (s1 == s2)
                return -1;
            else
                return 0;
}*/


    void createWinBackground() {

            SDL_Surface *backgroundImage;
            SDL_Texture *backgroundTexture;
            SDL_Rect backgroundRect;

            backgroundRect.x = 0;
            backgroundRect.y = 0;
            backgroundRect.h = SCREEN_HEIGHT;
            backgroundRect.w = SCREEN_WIDTH;

            backgroundImage = loadImage("img/win/win-screen.bmp");
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
    
    void createWinPageButtons() {

        
        SDL_Surface *tempImage;
        SDL_Texture *tempTexture;
        

        
                homeButtonRect.x = 911; 
                homeButtonRect.y = 656; 
                homeButtonRect.w = 100;
                homeButtonRect.h = 100;
                
                tempImage = loadImage("img/win/win-home-button.bmp");
                if (!tempImage) {
                    fprintf(stderr,"error in loading the image %s", SDL_GetError());
                    DestroyWindowAndQuit(app);
                }
                tempTexture = SDL_CreateTextureFromSurface(app.renderer, tempImage);
                SDL_FreeSurface(tempImage);
                if(NULL == tempTexture)
                {
                        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                        SDL_GetError());
                        DestroyWindowAndQuit(app);
                }

                SDL_RenderCopy(app.renderer,tempTexture,NULL,&homeButtonRect);
                
        }
        
    



    void WinPageEvents(SDL_Event event) {

        if (strcmp(app.page,"win") == 0) {

            switch (event.type)
            {
            
                case SDL_MOUSEBUTTONDOWN: 
            
                            if (event.button.button == SDL_BUTTON_LEFT) {
                                
                                positionClick.x = event.button.x;
                                positionClick.y = event.button.y;
                                
                            
                                if (SDL_PointInRect(&positionClick,&homeButtonRect)) {
                                    DestroyWindow(app);
                                    createHomePage();
                                };
                                
                                
                            }
                    break;
            }
        }
    }