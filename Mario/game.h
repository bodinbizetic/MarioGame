#ifndef New_menu_h
#define New_menu_h
#include <SDL.h>
#include <SDL_ttf.h>
//posititons for coords for texts in game
#define POSITIONS 3
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario);
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario);
#endif