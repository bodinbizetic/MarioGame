#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <SDL.h>
#include "ai.h"
typedef struct {

	Pair_xy coordinates, size, speed;
	int direction;
	int lives;
	int immortality;
	int projectileTimer;
	int animation_Stage;
}Mario;

void updateMario(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario,int update) {
	SDL_Rect rect;
	rect.h = mario->size.y;
	rect.w = mario->size.x;
	if (update == 0) {
		mario->direction = 1;
		if (mario->speed.x <= 16)
			mario->speed.x += 2;
		mario->coordinates.x += mario->speed.x;
	}
	else if (update == 1) {
		mario->direction = 0;
		if (mario->speed.x >= -16)
			mario->speed.x -= 2;
		mario->coordinates.x += mario->speed.x;
	}
	else if (update == 2) {
		if (mario->speed.x - 16)
			mario->speed.x -= 2;
		mario->coordinates.x += mario->speed.x;
	}
	else if (update == 3) {
		if (mario->speed.x - 16)
			mario->speed.x -= 2;
		mario->coordinates.x += mario->speed.x;
	}
	rect.x = mario->coordinates.x;
	rect.y = mario->coordinates.y;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(renderer, &rect);
}