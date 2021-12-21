#ifndef WIN_PAGE_HEADER
    #define WIN_PAGE_HEADER
    #include "defs.h"
    #include <SDL2/SDL.h>    
    #include <SDL2/SDL_ttf.h>

     typedef struct ScoreBoard {
                char name[50];
                int score;
        } ScoreBoard;

    App createWinPage(int score, char name[50]);
    void createWinBackground();
    int scoreByName(char name[50]);
    void createWinPageButtons();
    void displayScores(int score);
    void WinPageEvents(SDL_Event event);

    void SavePlayerScore(char name[50],int score);
    int editPlayerScore(struct ScoreBoard player);
    int bestScore();

#endif