#ifndef mario_h
#define mario_h
#include "ai.h"
#include "map.h"

#define G 1
typedef struct {
	
	Pair_xy coordinates, size, speed;
	int direction;
	int lives;
	int immortality;
	int projectileTimer;
	int animation_Stage;
	int facing;
	int time;
	SDL_Texture *animation[2][2][2];
}Mario;
//Update govori koja je komanda
void updateMario(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario,Pair_xy update);
#endif
