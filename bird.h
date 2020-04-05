#ifndef BIRD_H
#define BIRD_H

#include <stdlib.h>
#include <SDL2/SDL.h>

extern const int HEIGHT;

typedef struct {
	int x;
	int y;
	int w;
	int h;
	float gravity;
	float velocity;
	float lift;
	int isAlive;
	int jump;
	SDL_Rect b;
} Bird;

void BirdInit(Bird *);
void UpdateBird(Bird *);
void SetBoundary(Bird *);

#endif  // BIRD_H
