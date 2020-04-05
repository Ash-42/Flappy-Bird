#include "text.h"

void TextInit(Text *text, TTF_Font *font, int GameOver)
{		
	char *txt;
	if (GameOver) {
		txt = "Game Over";
		text -> text_rect.x = WIDTH / 2;
		text -> text_rect.y = 300;
	}
	else {
		txt = "Flappy Bird";
		text -> text_speed = 5;
		text -> text_rect.x = WIDTH;
		text -> text_rect.y = 300;
	}

	text -> text_color.r = 255;
	text -> text_color.g = 255;
	text -> text_color.b = 255;
	text -> text_color.a = 255;
	
	text -> surface = TTF_RenderText_Solid(font, txt, text -> text_color);
    if (text -> surface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		exit(1);
    }
	else{
        text -> text_rect.w = text -> surface -> w;
		text -> text_rect.h = text -> surface -> h;
	}
}

int UpdateText(Text* text)
{	
	text -> text_rect.x -= text -> text_speed;
	return 1;
}
