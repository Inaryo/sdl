#ifndef WIN_PAGE_HEADER
    #define WIN_PAGE_HEADER
    #include "defs.h"
    #include <SDL2/SDL.h>    


     typedef struct ScoreBoard {
                char name[50];
                int score;
        } ScoreBoard;

    App createWinPage(int score);
    void createWinBackground();
    void createWinPageButtons();
    void displayScores(int score);
    void WinPageEvents(SDL_Event event);
    

#endif