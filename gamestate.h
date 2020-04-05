#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "pipe.h"
#include "bird.h"
#include "text.h"

extern const int WIDTH;
extern const int HEIGHT;
extern int PIPES;
extern int BIRDS;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    Bird bird;
	SDL_Texture *bird_sprite;
	SDL_Texture *pipe_sprite;
	SDL_Texture *bkg_sprite;
	SDL_Rect bkg_window;
    Pipe pipes[4];
	Text text;
    int running;
    long long unsigned TimeNow;
    long long unsigned TimeLast;
    unsigned PipeGenerationTimeLast;
    size_t WhichPipeToStart;
	TTF_Font *font;
} Gamestate;

SDL_Texture* LoadTexture(char *, Gamestate *);
int LoadMedia(Gamestate *);
int InitGame(Gamestate *);
void ReceiveInput(Gamestate *);
void UpdateGame(Gamestate *);
void RenderDisplay(Gamestate *);
void FreeResources(Gamestate *);

#endif  // GAMESTATE_H
