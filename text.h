#ifndef TEXT_H
#define TEXT_H

#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

extern const int WIDTH;
extern const int HEIGHT;

typedef struct {
	SDL_Color text_color;
	SDL_Surface *surface;
	SDL_Rect text_rect;
	int text_speed;

} Text;

void TextInit(Text *, TTF_Font *, int);
int UpdateText(Text *);

#endif 	// TEXT_H
