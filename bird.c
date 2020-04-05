#include "bird.h"

void BirdInit(Bird *bird)
{
    bird -> x = 250;
    bird -> y = HEIGHT / 2;
    bird -> w = 50;
    bird -> h = 50;
	bird -> jump = 0;
    bird -> isAlive = 1;
    bird -> gravity = 0.2;
    bird -> velocity = 0;
    bird -> lift = -0.8;
    bird -> b.x = bird -> x;
    bird -> b.y = bird -> y;
    bird -> b.w = bird -> w;
    bird -> b.h = bird -> h;
}

void UpdateBird(Bird *bird)
{
	if (bird -> jump) {
		bird -> velocity += bird -> lift;
		bird -> jump = 0;
	}
	bird -> velocity += bird -> gravity;
	bird -> y += bird -> velocity; 
	bird -> b.y = bird -> y;
}

void SetBoundary(Bird *bird)
{
    if (bird -> y >= HEIGHT - 45) {
      bird -> y = HEIGHT - 45;
      bird -> velocity = 0;
    }
    if (bird -> y < 0) {
      bird -> y = 0;
      bird -> velocity = 0;
    }
    bird -> b.y = bird -> y;
}
