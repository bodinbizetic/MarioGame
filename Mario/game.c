#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "map.h"
#include "mario.h"
#include "main_menu.h"

#define TILE_SIZE 16
//blok sluzi kao jedan blok cije se dimenzije racunaju prema ekranu
Pair_xy blok;
//DrawScreen crta na ekranu
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario) {

	
	int i, j, x = 0, y = 0;
	SDL_Rect rect = { x,y,TILE_SIZE,TILE_SIZE };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j <= MAP_WIDTH; j++) {
			//Belo nebo
			rect.x = j*blok.x;
			rect.y = i*blok.y;
			rect.w = blok.x;
			rect.h = blok.y;
			if (map->map_Matrix[i][j] == sky) {
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			//Crn pod
			else if(map->map_Matrix[i][j] == ground)  {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			/*if (x == mario->coordinates.x && y == mario->coordinates.y) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
				SDL_RenderFillRect(renderer, &rect);
				
			}*/
		}
	}
	SDL_RenderPresent(renderer);
}
//igranje igre
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario) {
	blok.x = SCREEN_WIDTH / MAP_WIDTH;
	blok.y = SCREEN_HEIGHT / MAP_HEIGHT;

	Map *mapa;
	Mario *probni_mario;
	int update = 0;;
	probni_mario = malloc(sizeof(Mario));
	probni_mario->size.x = blok.x;
	probni_mario->size.y = blok.y;
	probni_mario->coordinates.x = 3* blok.x;
	probni_mario->coordinates.y = 3*blok.y;
	probni_mario->speed.x = 0;
	probni_mario->speed.y = 0;
	//postoji funkcija koja inicijalizuje mapu
	mapa = initMap();
	
	int i, j, x = 0, y = 0;
	/*for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++) {
			if (i == 9)
				mapa->map_Matrix[i][j] = 0;
			else
				mapa->map_Matrix[i][j] = 1;
		}*/

	//Running for game loop
	int Running = 1;
	drawScreen(window, renderer, mapa, probni_mario);
	SDL_Event eventgame;
	while (Running) {
		while (SDL_PollEvent(&eventgame)) {
			switch (eventgame.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				switch (eventgame.key.keysym.sym) {
				case SDLK_RIGHT:
					update = 0;
					break;
				case SDLK_LEFT:
					update = 1;
					break;
				/*case SDLK_UP:
					update = 2;
					break;*/
				case SDLK_ESCAPE:
					Running = 0;
					return  0;
					break;
				}
			case SDL_KEYUP: {
				update = 3;
				break;
			}
			default: {}
			}
		}
		updateMario(window,renderer,mapa,probni_mario,update);
	}
}