#ifndef mario_h
#define mario_h
#include "ai.h"
#include "map.h"

typedef struct {
	
	Pair_xy coordinates, size, speed;
	int direction;
	int lives;
	int immortality;
	int projectileTimer;
	int animation_Stage;
}Mario;
//Update govori koja je komanda
void updateMario(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario,int update);
#endif
