gcc main.c src/pause_page.c src/stat_page.c src/credits_page.c src/other.c src/name_page.c src/launch_page.c src/defs.c src/home_page.c -o file -Wall -w -lm -lSDL2 -lSDL2_image -lSDL_ttf  && ./file


del main.exe && gcc -std=c17 main.c src/pause_page.c src/stat_page.c src/credits_page.c src/other.c src/name_page.c src/launch_page.c src/defs.c src/win_page.c src/home_page.c -IF:\WebDev\Projects\sdl\SDL2\include -LF:\WebDev\Projects\sdl\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main && main.exe