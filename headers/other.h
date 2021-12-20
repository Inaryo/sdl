#ifndef OTHER_H_INCLUDED
#define OTHER_H_INCLUDED

        #include <SDL2/SDL.h>

        void DestroyWindow(App app);
        void DestroyWindowAndQuit(App app);
        App createWindowAndRenderer(char page[],int width,int height);

#endif // OTHER_H_INCLUDED
