#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "map.h"
#include "mario.h"
#include "main_menu.h"

#define dimension 16
//DrawScreen crta na ekranu
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario) {
	int i, j, x = 0, y = 0;
	SDL_Rect rect = { 0,0,x,y };
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			//Belo nebo
			if (map->map_Matrix[i][j] == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			//Crn pod
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			x += 16;
		}
		x = 0;
		y += 16;
	}
	SDL_RenderPresent(renderer);
}
//igranje igre
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *Mario) {
	Map *mapa;
	mapa = malloc(sizeof(map));
	int i, j, x = 0, y = 0;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++) {
			if (i == 9)
				mapa->map_Matrix[i][j] = 0;
			else
				mapa->map_Matrix[i][j] = 1;
		}

	//Running for game loop
	int Running = 1;
	SDL_Event event;
	while (Running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					Running = 0;
					return  0;
					break;
				}
			case SDL_KEYUP:
			default: {}
			}
			drawScreen(window, renderer, mapa, mario);
		}
	}
}