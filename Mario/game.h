#ifndef game_h
#define game_h
#include <SDL.h>
#include <SDL_ttf.h>
#include "mario.h"
#include "map.h"
#include "ai.h"
//posititons for coords for texts in game
#define POSITIONS 3
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario);
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario);
int collision(Pair_xy dim1, Pair_xy coord1, Pair_xy dim2, Pair_xy coord2);
Pair_xy blok;
#endif