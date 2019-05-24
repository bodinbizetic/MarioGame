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
int collision(Pair_xy dim1, Pair_xy coord1, Pair_xy dim2, Pair_xy coord2) {
	Pair_xy c1,c2;
	int dx, dy;
	c1.x = (coord1.x + dim1.x / 2);
	c1.y = (coord1.y + dim1.y / 2);
	c2.x = (coord2.x + dim2.x / 2);
	c2.y = (coord2.y + dim2.y / 2);
	dx = abs(c1.x - c2.x);
	dy = abs(c1.y - c2.y);
	if (dx <= (dim1.x + dim2.x) / 2 && dy <= (dim1.y + dim2.y) / 2)
		return 2;
	/*if (dy <= (dim1.y + dim2.y) / 2) {
		
			return 2;
	}*/
	return 0;
}
//DrawScreen crta na ekranu
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario) {

	
	int i, j, x = 0, y = 0;
	SDL_Rect rect = { x,y,TILE_SIZE,TILE_SIZE };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j <= MAP_WIDTH; j++) {
			rect.x = j * blok.x;
			rect.y = i * blok.y;
			rect.w = blok.x;
			rect.h = blok.y;
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = mario->coordinates.x;
			new_coordinates.y = mario->coordinates.y + mario->speed.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				// ground 
				SDL_Surface *brick = IMG_Load("Slike/ground.png");
				if (brick == NULL) {
					printf("%s\n", SDL_GetError());
					exit(1);
				}
				SDL_Texture *object = SDL_CreateTextureFromSurface(renderer, brick);
				SDL_FreeSurface(brick);
				SDL_RenderCopy(renderer, object, NULL, &rect);
				SDL_DestroyTexture(object);
				/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);*/
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255);
				SDL_RenderFillRect(renderer, &rect);
				break;
			}
			case question: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255);
				SDL_RenderFillRect(renderer, &rect);
				break;
			}
			case hidden: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255);
				SDL_RenderFillRect(renderer, &rect);
				break;
			}
			default:
				break;
			}




		}
	/*for (i = 0; i < MAP_HEIGHT; i++) {
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
			else if (map->map_Matrix[i][j] == basic) {
				SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			
		}
	}*/
	
}
//igranje igre
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario) {
	blok.x = SCREEN_WIDTH / MAP_WIDTH;
	blok.y = SCREEN_HEIGHT / MAP_HEIGHT;

	Map *mapa;
	Mario *probni_mario;
	Pair_xy update = { 0,0 };
	probni_mario = malloc(sizeof(Mario));
	probni_mario->size.x = blok.x;
	probni_mario->size.y = 2*blok.y;
	probni_mario->coordinates.x = 3* blok.x;
	probni_mario->coordinates.y = 3*blok.y;
	probni_mario->speed.x = 0;
	probni_mario->speed.y = 0;
	probni_mario->lives = 2;


	// mario animations - nazalost moralo je sve rucno...
	{
		probni_mario->animation_Stage = 0;
		probni_mario->facing = 0;
		probni_mario->time = 0;

		// red mario
		SDL_Surface *surface = IMG_Load("Slike/marioStandRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[0][0][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/marioMoveRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[0][0][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/marioJumpRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[0][0][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/marioStandLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[0][1][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/marioMoveLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[0][1][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/marioJumpLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[0][1][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// green mario
		surface = IMG_Load("Slike/gmarioStandRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[1][0][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/gmarioMoveRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[1][0][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/gmarioJumpRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[1][0][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/gmarioStandLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[1][1][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/gmarioMoveLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[1][1][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/gmarioJumpLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[1][1][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

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
	SDL_Event eventgame;
	while (Running) {
		while (SDL_PollEvent(&eventgame)) {
			switch (eventgame.type) {
			case SDL_QUIT:
				Running = 0;
				return NUMBER_OF_OPTIONS;
			case SDL_KEYDOWN:
			{
				switch (eventgame.key.keysym.sym) {
				case SDLK_ESCAPE:
					Running = 0;
					break;
					//return  0; zbog ovog je curila memorija??		
				case SDLK_p:
					pause_game();
					break;
				}
				break;
			}
			case SDL_KEYUP: {
				break;
			}
			default:{}
			}
		}
		Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_UP]) {
			update.y = 1;
		}
		else
			update.y = 2;
		if (state[SDL_SCANCODE_LEFT]) {
			update.x = 1;
			probni_mario->facing = 1;
		}
		else if (state[SDL_SCANCODE_RIGHT]) {
			update.x = 0;
			probni_mario->facing = 0;
		}
		else
			update.x = 2;

	
		drawScreen(window, renderer, mapa, probni_mario);
		updateMario(window,renderer,mapa,probni_mario,update);
		updateAI(mapa);
		drawAI(window, renderer, mapa);
		SDL_RenderPresent(renderer);

	}

	// free memory 
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 3; k++)
				SDL_DestroyTexture(probni_mario->animation[i][j][k]);
	free(probni_mario);
	// treba AI free da se doda !!!
	// mapa - pomocna mapa , treba da se zameni u free(map)
	destroyMap(mapa);
	return 0;
}