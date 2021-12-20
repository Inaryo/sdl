#include "../headers/win_page.h"   
#include "../headers/other.h" 
#include "../headers/home_page.h" 

    App app;
    SDL_Point positionClick;

    SDL_Rect tempRect,homeButtonRect;
    SDL_Texture *homeButtonTexture;
    SDL_Surface *homeButtonSurface;
    FILE* file;
    char path[] = "../scores.dat";

    
    App createWinPage(int score) {

        app = createWindowAndRenderer("win",SCREEN_WIDTH,SCREEN_HEIGHT);

        createWinBackground();
        createWinPageButtons();    
        displayScores(score);

        SDL_RenderPresent(app.renderer);
        return app;
    
    }

    void displayScores(int score) {

    }


    void SavePlayerScore(char[50] name,int score) {

        struct ScoreBoard player = {name,score};
        
        if (editPlayerScore(player) == 0 ) {
                FILE* file = fopen(path, "r+b");
                fwrite (&player, sizeof(struct ScoreBoard), 1, file);
                
                if(fwrite != 0)
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
        int exist = 0;

        while(fread(&input, sizeof(struct ScoreBoard), 1, file)) {
            if (strcmp(input.name,player.name) == 0) {
                if (input.score >= player.score) {
                    player.score = input.score;
                }
                fseek(file, -sizeof(player), SEEK_CUR);
                fwrite(&player, sizeof(player), 1, file);
                fclose(file);
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

        fclose(file);
        return 0;
        
    }


    

    int isFirstMore(struct ScoreBoard score_board_1, struct ScoreBoard score_board_2){

            int score_1, score_2;
            score_1  = score_board_1.score;
            score_2  = score_board_2.score ;
            if (score_1 < score_2)
                return 1;
            else if (s1 == s2)
                return -1;
            else
                return 0;
}


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