#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "mario.h"
#include "main_menu.h"
#include "map.h"
#include "game.h"
#include "highscore.h"
#include "settings.h"

#define NUMBER_OF_OPTIONS 5
int main(int argc, char *argv[]) {
	//GameState,u kom smo stanju trenutno(0-meni,1-novoj igri,2-staroj igri,3-highscore,4-settings,5(NUMBER_OF_OPTIONS)-kraj programa)
	//Fje treba da vracaju u skladu sa ovim brojevima
	/*IMG_Init(IMG_INIT_PNG);
	SDL_Surface *surface = IMG_Load("mario.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		
	}*/

	char *Name = "Highscore.txt";
	FILE *file;
	int Game_State,Game_Running;
	Map *map=NULL;
	Mario *mario=NULL;
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
	Game_Running = 1;
	//Pocinje u meniju
	Game_State = 0;
	while (Game_Running ) {
		//Sa Game_State biramo gde idemo,sve funkcije ce biti int i lako cemo videti u koje stanje idemo
		if (Game_State == 0) 
			Game_State = show_menu(window, renderer);
		//Option New Game
		if (Game_State == 1) {
			//create map
			//map = initMap(); mapa mora da se init u game zbog ai-ova(textura) !
			//start new game
			Game_State=Game(window, renderer, map, mario,1);
		}
		//Option Continue Game
		if (Game_State == 2) {
			//Loading map
			//start game with
			Game_State=Game(window, renderer, map, mario,0);
		}
		if (Game_State == 3) {
			Game_State=showHighscore(renderer);
		}
		if (Game_State == 4) {
			Game_State=showSettings(renderer);

		}
		if (Game_State == 5) 
			Game_Running = 0;

	}
	
	//Destroying stuff
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 1;
}