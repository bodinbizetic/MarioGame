#include <stdio.h>
#include <stdlib.h>
#include "main_menu.h"
#include <SDL.h>
#include "map.h"
#include "Mario_man.h"
#define NUMBER_OF_OPTIONS 5
int main(int argc, char *argv[]) {
	int option;
	Map *map;
	Mario *mario;
	int Game_Running = 1;
	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Init window
	SDL_Window *window = SDL_CreateWindow("Procedural", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,	SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//Window error check
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Init Renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	//Renderer error check
	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return 0;
	}
	//game loop
	while (Game_Running) {

		option = show_menu(window, renderer);
		if (option == 0) {
		}
		if (option = NUMBER_OF_OPTIONS - 1)
			Game_Running = 0;
		SDL_RenderPresent(renderer);
		SDL_Delay(20);
	}

	//Destroying stuff
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}