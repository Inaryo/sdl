#ifndef PAUSE_PAGE_HEADER
    #define PAUSE_PAGE_HEADER
    #include "defs.h"
    

    void createPausePage(struct SaveGame game);
    void createPausePageBackground();
    void createPausePageButtons();
    void PausePageEvents(SDL_Event event);
    

#endif