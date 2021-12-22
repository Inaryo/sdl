#ifndef LAUNCH_PAGE_HEADER
    #define LAUNCH_PAGE_HEADER

    #include "defs.h"

    typedef struct CharLineArray {
                char line[6][25];
        } CharLineArray;

    typedef struct SaveGame {
                char playerName[50];
                int actual_time;
                int numberArray[7][7];
                struct CharLineArray pathBlocMatrice[6];
        } SaveGame;

    App createLaunchPage();
    void LaunchPageEvent(SDL_Event event);
    void createLaunchButtons();
    void initMatrice();
    void initRectBlocMatrice();
    void createLaunchBackground();
    void changeBlocPath(int i,int j);
    void createPauseButtons();
    void initPathBlocMatrice();
    void createNumbersButtons();
    void updateRender();
    void updateNumbersButtons(int i,int j);

    int getSave();
#endif