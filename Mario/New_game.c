#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "map.h"
#include "Mario_man.h"
#include "main_menu.h"
//DrawScreen crta na ekranu
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario);
void newGame(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario) {
	//Running for game loop
	int Running = 1;
	//TTF Init
	if (TTF_Init() < 0) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}
	//Font za poene,vreme,nivo..
	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 80);
	if (font == NULL) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}
	SDL_Color White = { 255, 255, 255 };
	//Surface for TTF text
	SDL_Surface* surfaceMessage = NULL;
	SDL_Texture* Message = NULL;
	//Text back rectangle
	//positions sluzi za text u igrici
	SDL_Rect menu_square, positions[3];
	menu_square.x = SCREEN_WIDTH / 2 - MENU_WIDTH / 2;
	menu_square.y = SCREEN_HEIGHT / 2 - MENU_HEIGHT / 2;
	menu_square.h = MENU_HEIGHT;
	menu_square.w = MENU_WIDTH;


}