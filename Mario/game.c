#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "map.h"
#include "mario.h"
#include "main_menu.h"
//DrawScreen crta na ekranu
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario) {
	;
}
//igranje igre
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario) {
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
	SDL_Rect game_square, positions[3];
	game_square.x = 0;
	game_square.y = 0;
	game_square.h = SCREEN_HEIGHT;
	game_square.w = SCREEN_WIDTH;


}