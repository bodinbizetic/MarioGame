#ifndef mario_h
#define mario_h
#include "ai.h"
#include "map.h"
#include "all.h"
#define MAX_JUMP 25
#define MAX_IMORTAL 250
#define MAXSPEED 8
#define G 1
//Update govori koja je komanda
void updateMario(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario,Pair_xy update);
#endif
