#include "../headers/defs.h"
#include "../headers/other.h"
#include "../headers/home_page.h"
#include "../headers/pause_page.h"
#include "../headers/launch_page.h"
#include "../headers/win_page.h"
#include <math.h>

typedef struct CharLineArray {
                char line[6][25];
        } CharLineArray;

int repeat = 0;
App app;
SDL_Point positionClick;
int numberMatrice[7][7];
int copyNumberMatrice[7][7];
SDL_Rect numberRectMatrice[7][7];
struct CharLineArray pathBlocMatrice[6];
CharLineArray line;

SDL_Rect tempRect,pauseButtonRect,homeButtonRect;
SDL_Texture *pauseButtonTexture,*homeButtonTexture;
SDL_Surface *pauseButtonSurface,*homeButtonSurface;
SDL_Rect rectBlocMatrice[6][6];
Uint32 time_launched = 0;
float time_actual = 0;
float time_begin = 0;
float time_precedent = 0; 
char tempPath[50] = "";
int is_play_paused = 0;
SDL_Surface *tempImage;
SDL_Texture *tempTexture;
play_saving = 0;






char diagDirectory[] = "img/launch/diag/";


App createLaunchPage() {

    app = createWindowAndRenderer("launch",SCREEN_WIDTH,SCREEN_HEIGHT);
    time_launched = SDL_GetTicks() * 1000;
    createLaunchBackground();

    initPathBlocMatrice();
    initMatrice();
    initRectBlocMatrice();
    
    createLaunchButtons();
    createNumbersButtons();
    createPauseButtons();

    time_begin = SDL_GetTicks() / 1000;
    SDL_RenderPresent(app.renderer);
    return app;
}

void createLaunchButtons() {
        
        
        for (int i = 0; i < 6; i++)
        {
            
            line = pathBlocMatrice[i];
            for (int j = 0; j < 6; j++)
            {
                // Create the Image of Play
                
                tempRect = rectBlocMatrice[i][j];
                strcpy(tempPath,diagDirectory);
                
                
                tempImage = loadImage(strcat(tempPath,line.line[j]));
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
                SDL_RenderCopy(app.renderer,tempTexture,NULL,&tempRect);
            }
            
        }
        
}

/*
*   Initiating the Function responsible for the Creation of the Matrice ( Rectangles )
*/
void initRectBlocMatrice() {
    int j,i;
    for ( i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            
                tempRect.x = 685 + ( (j -1) * BUTTONS_BLOC_WIDTH);
                tempRect.y = 325 + ( (i -1) * BUTTONS_BLOC_HEIGHT);  
                tempRect.w = BUTTONS_BLOC_WIDTH;
                tempRect.h = BUTTONS_BLOC_HEIGHT;
                rectBlocMatrice[i][j] = tempRect;
            
                
        };
        
    };
}

void initPathBlocMatrice() {
    
    
    
    for (int i = 0; i < 6; i++) {
            line = pathBlocMatrice[i];
            for (int j = 0; j < 6; j++)
            {
                
                strcpy(line.line[j],"no_diag.bmp");
            }
            pathBlocMatrice[i] = line;
            

    }
    
}

/*
*   Initiating the Function responsible for The Number Matrice 
*/
void initMatrice() {
    
    int i,j;

   for(i = 0;i < 7; ++i)
    {
        for (j=0;j<7;++j)
        {
            numberMatrice[i][j] = 0;
            copyNumberMatrice[i][j] = 0;

        }
    }

    srand(time(0));

    for (i=0;i<6;i++)
        {
            for (j=0;j<6;j++) {
                if (rand() % 2 == 0)
                {
                    numberMatrice[i][j]++;
                    numberMatrice[i+1][j+1]++;
                    copyNumberMatrice[i][j]++;
                    copyNumberMatrice[i+1][j+1]++;
                    
                }
                else {
                    numberMatrice[i+1][j]++;
                    numberMatrice[i][j+1]++;
                    copyNumberMatrice[i+1][j]++;
                    copyNumberMatrice[i][j+1]++;
                }

            }
        }
         

       
}


void createPauseButtons() {
        // Create the Image of Pause
        pauseButtonRect.x = 664;
        pauseButtonRect.y = 52;
        pauseButtonRect.w = 100;
        pauseButtonRect.h = 100;

        pauseButtonSurface = loadImage("img/launch/pause-button.bmp");
        if (!pauseButtonSurface) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        pauseButtonTexture = SDL_CreateTextureFromSurface(app.renderer, pauseButtonSurface);
        SDL_FreeSurface(pauseButtonSurface);
        if(NULL == pauseButtonTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,pauseButtonTexture,NULL,&pauseButtonRect);
        


        // Create the Button of Home
        homeButtonRect.x = 1157;
        homeButtonRect.y = 47;
        homeButtonRect.w = 100;
        homeButtonRect.h = 100;

        homeButtonSurface = loadImage("img/launch/home-button.bmp");
        if (!homeButtonSurface) {
            fprintf(stderr,"error in loading the image %s", SDL_GetError());
            DestroyWindowAndQuit(app);
        }
        homeButtonTexture = SDL_CreateTextureFromSurface(app.renderer, homeButtonSurface);
        SDL_FreeSurface(homeButtonSurface);
        if(NULL == homeButtonTexture)
        {
                fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
                                SDL_GetError());
                DestroyWindowAndQuit(app);
        }
        SDL_RenderCopy(app.renderer,homeButtonTexture,NULL,&homeButtonRect);
        

        SDL_RenderPresent(app.renderer);
}

void createNumbersButtons() {

        SDL_Rect tempRect ;
        SDL_Surface *tempImage;
        SDL_Texture *tempTexture;
        char path[60] = "";
        int number;

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                tempRect.x = 515 + (j * BUTTONS_BLOC_WIDTH); 
                tempRect.y = 155 + (i * BUTTONS_BLOC_HEIGHT); 
                tempRect.w = 76;
                tempRect.h = 76;
                
                number = copyNumberMatrice[i][j];
                numberRectMatrice[i][j] = tempRect;
                strcpy(path,"");
                strcat(path,"img/launch/numbers/");
                strcat(path,"gear-num-");
                char temp[2];
                sprintf(temp,"%d",number);
                strcat(path,temp);
                strcat(path,".bmp");
                
            
                tempImage = loadImage(path);
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

                SDL_RenderCopy(app.renderer,tempTexture,NULL,&tempRect);
                
            }
            
        }

}


/*
*   Create the Main Background Image for the game
*/ 
void createLaunchBackground() {

    SDL_Surface *backgroundImage;
    SDL_Texture *backgroundTexture;
    SDL_Rect backgroundRect;

    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.h = SCREEN_HEIGHT;
    backgroundRect.w = SCREEN_WIDTH;

    backgroundImage = loadImage("img/launch/game-screen.bmp");
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


/*
*   The Function update the path of the bloc for the rendering and then change 
*   The value of the Matric Number
*/
void changeBlocPath(int i,int j) {
    

      line = pathBlocMatrice[i];
      
     
     if (strcmp(line.line[j],"no_diag.bmp") == 0) {
            numberMatrice[i][j+1]++;
            numberMatrice[i+1][j]++;

            strcpy(line.line[j],"diag_top_right.bmp");
            pathBlocMatrice[i] = line;
     } else if (strcmp(line.line[j],"diag_top_right.bmp") == 0) {
            numberMatrice[i][j+1]--;
            numberMatrice[i+1][j]--;
            numberMatrice[i][j]++;
            numberMatrice[i+1][j+1]++;

            strcpy(line.line[j],"diag_top_left.bmp");
            pathBlocMatrice[i] = line;

     } else if (strcmp(line.line[j],"diag_top_left.bmp") == 0) {

            numberMatrice[i][j]--;
            numberMatrice[i+1][j+1]--;

            strcpy(line.line[j],"no_diag.bmp");
            pathBlocMatrice[i] = line;
     };

                strcpy(tempPath,"");
                strcpy(tempPath,diagDirectory);
                strcat(tempPath,line.line[j]);
                fprintf(stderr,"%s \n",tempPath);
                tempRect = rectBlocMatrice[i][j];

                tempImage = loadImage(tempPath);
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

                SDL_RenderCopy(app.renderer,tempTexture,NULL,&tempRect);
                updateNumbersButtons(i,j);
                SDL_RenderPresent(app.renderer);

}

void updateNumbersButtons(int i,int j) {
               
               
                tempRect = numberRectMatrice[i][j];
                int number =  copyNumberMatrice[i][j];
                strcpy(tempPath,"");
                strcat(tempPath,"img/launch/numbers/");
                strcat(tempPath,"gear-num-");
                char temp[2];
                sprintf(temp,"%d",number);
                strcat(tempPath,temp);
                strcat(tempPath,".bmp");

                tempImage = loadImage(tempPath);
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

                SDL_RenderCopy(app.renderer,tempTexture,NULL,&tempRect);


                tempRect = numberRectMatrice[i+1][j];
                 number =  copyNumberMatrice[i+1][j];
                strcpy(tempPath,"");
                strcat(tempPath,"img/launch/numbers/");
                strcat(tempPath,"gear-num-");
                sprintf(temp,"%d",number);
                strcat(tempPath,temp);
                strcat(tempPath,".bmp");

                tempImage = loadImage(tempPath);
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

                SDL_RenderCopy(app.renderer,tempTexture,NULL,&tempRect);

                tempRect = numberRectMatrice[i][j+1];
                 number =  copyNumberMatrice[i][j+1];
                strcpy(tempPath,"");
                strcat(tempPath,"img/launch/numbers/");
                strcat(tempPath,"gear-num-");
                sprintf(temp,"%d",number);
                strcat(tempPath,temp);
                strcat(tempPath,".bmp");

                tempImage = loadImage(tempPath);
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

                SDL_RenderCopy(app.renderer,tempTexture,NULL,&tempRect);

                tempRect = numberRectMatrice[i+1][j+1];
                 number =  copyNumberMatrice[i+1][j+1];
                strcpy(tempPath,"");
                strcat(tempPath,"img/launch/numbers/");
                strcat(tempPath,"gear-num-");
                sprintf(temp,"%d",number);
                strcat(tempPath,temp);
                strcat(tempPath,".bmp");

                tempImage = loadImage(tempPath);
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

                SDL_RenderCopy(app.renderer,tempTexture,NULL,&tempRect);




}


int checkIfWin()
{
 int i,j;

 for (i=0;i<7;i++){
    for (j=0;j<7;j++){
        if (numberMatrice[i][j] != 0)  return 0;
    }
    }
    return 1;
}


void updateTimer() {
    fprintf(stderr,"%f \n",time_actual);
}

/*
*   The Function responsible for the Game Events
*/ 
void LaunchPageEvent(SDL_Event event) {


    if (strcmp(app.page,"launch") == 0) {

            if (is_play_paused == 0) {

                time_actual = (SDL_GetTicks() / 1000);
                time_actual = time_actual - time_begin;
                time_actual = roundf(time_actual);
                
                if (time_actual > time_precedent) {
                    
                    updateTimer(time_actual);
                    time_precedent = time_actual;
                }
                
            }

            if (play_saving) {
                FILE* file = fopen(savingFilePath , "ab+");
                
                
                if( (fwrite (&player, sizeof(struct ScoreBoard), 1, file)) != 0)
                    fprintf(stderr,"contents to file written successfully !\n");
                else
                    fprintf(stderr,"error writing file !\n");
            
                // close file
                fclose (file);
            }
            
            

            switch (event.type)
            {
            
            case SDL_MOUSEBUTTONDOWN: 
            
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        
                        positionClick.x = event.button.x;
                        positionClick.y = event.button.y;
                        
                        for (int i = 0; i < 6; i++)
                        {
                            for (int j = 0; j < 6; j++)
                            {
                                if (SDL_PointInRect(&positionClick,&rectBlocMatrice[i][j]) == 1) {
                                        changeBlocPath(i,j);

                                        repeat++;
                                        if (repeat > 4) {
                                            repeat = 0;
                                            DestroyWindow(app); 
                                            createWinPage(time_actual,"ramzi");
                                            time_actual = 0;
                                        };    
                                        if(checkIfWin() == 1) {
                                            DestroyWindow(app); 
                                            createWinPage(time_actual,"ramzi");
                                            time_actual = 0;
                                        };
                                        
                                        break;  
                                }
                            }
                            
                        }

                        if (SDL_PointInRect(&positionClick,&pauseButtonRect)) {
                            is_play_paused = 1;
                            createPausePage();
                        } else if (SDL_PointInRect(&positionClick,&homeButtonRect)) {
                            DestroyWindow(app);
                            createHomePage();
                        };
                        
                        
                    }
                    break;
            }
    }

    
}