#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "map.h"
#include "mario.h"
#include "main_menu.h"
#include "highscore.h"
//ispis Highscore,vraca 0 za povratak u meni,5
#define NUMBER_OF_BEST_PLAYERS 5
#define MAX 50
int showHighscore(SDL_Renderer *renderer) {
	if (TTF_Init() < 0) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}

	// menu
	SDL_Rect menu_square;
	menu_square.x = SCREEN_WIDTH / 2 - MENU_WIDTH / 2;
	menu_square.y = SCREEN_HEIGHT / 2 - MENU_HEIGHT / 2;
	menu_square.h = MENU_HEIGHT;
	menu_square.w = MENU_WIDTH;
	//SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 200, 200, 255);
	SDL_RenderFillRect(renderer, &menu_square);

	// load scores and player names from file
	char text[NUMBER_OF_BEST_PLAYERS][MAX];
	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 80);
	if (font == NULL) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}

	FILE *load;
	fopen_s(&load, "Highscore.txt", "r");
	for (int i = 0; i < NUMBER_OF_BEST_PLAYERS; i++) {
		fgets(text[i], MAX, load);
	}

	// rect for scores and players
	SDL_Rect drawScore[NUMBER_OF_BEST_PLAYERS];
	for (int i = 0; i < NUMBER_OF_BEST_PLAYERS; i++) {
		drawScore[i].x = SCREEN_WIDTH / 2 - OPTION_WIDTH + 25;
		drawScore[i].y = SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - i - 1)*(OPTION_HEIGHT + 15) + 150;
		drawScore[i].h = OPTION_HEIGHT;
		drawScore[i].w = OPTION_WIDTH;
	}

	// draw on screen
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Color White = { 255,255,255 };
	for (int i = 0; i < NUMBER_OF_BEST_PLAYERS; i++) {
		
		surface = TTF_RenderText_Blended(font, text[i], White);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, &drawScore[i]);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
	SDL_RenderPresent(renderer);

	SDL_Event event;
	int highScoreRunning = 1;
	while (highScoreRunning != 0) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:       // escape - go back to main menu
					highScoreRunning = 0;
					break;
				}
			}
		}
	}

	TTF_CloseFont(font);
	TTF_Quit();
	return 0;
}