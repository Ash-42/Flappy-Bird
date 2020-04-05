#include "main.h"

int main(int argc, char* args[])
{
    Gamestate game;
    if (!InitGame(&game)) printf ("Initialisation failed.\n");
    else {
        while(game.running) {
            ReceiveInput(&game);
            UpdateGame(&game);
            RenderDisplay(&game);
        }
    }   
    FreeResources(&game);
    return 0;
}

            
