#ifndef LAUNCH_PAGE_HEADER
    #define LAUNCH_PAGE_HEADER

    #include "defs.h"

    

    App createLaunchPage(int retry);
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