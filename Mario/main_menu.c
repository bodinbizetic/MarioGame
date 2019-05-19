#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

#define MENU_WIDTH 600
#define MENU_HEIGHT 480
#define NUMBER_OF_OPTIONS 5
#define OPTION_HEIGHT 80
#define OPTION_WIDTH 300
//Vraca koju opciju smo uzeli,da bismo to mogli da koristimo u main.c
int show_menu(SDL_Window *window, SDL_Renderer *renderer) {
	//Init TTF
	if (TTF_Init() < 0) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}

	//Menu square init
	int i,Menu_Running=1;
	char *text[NUMBER_OF_OPTIONS] = { "New game", "Continue",  "High Score", "Settings",  "Quit" };
	//Settings for TTF text
	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 80);
	if (font == NULL) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}
	//Selected and not-selected color
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Red = { 255,0,0 };

	//Surface for TTF text
	SDL_Surface* surfaceMessage = NULL;
	SDL_Texture* Message = NULL;

	//Text back rectangle
	SDL_Rect menu_square, options[NUMBER_OF_OPTIONS];
	menu_square.x = SCREEN_WIDTH / 2 - MENU_WIDTH / 2;
	menu_square.y = SCREEN_HEIGHT / 2 - MENU_HEIGHT / 2;
	menu_square.h = MENU_HEIGHT;
	menu_square.w = MENU_WIDTH;

	int selected[NUMBER_OF_OPTIONS] = { 0 };
	selected[0] = 1;
	int index_Selected = 0;

	//Event init
	//vraca NUMBER_OF_OPTIONS-1 AKO JE KRAJ PROGRAMA (EXIT,QUIT)
	SDL_Event event;
	while (Menu_Running != 0) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				Menu_Running = 0;
				return  NUMBER_OF_OPTIONS;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					if (index_Selected != 0) {
						selected[index_Selected--] = 0;
						selected[index_Selected] = 1;
					}
					break;
				case SDLK_DOWN:
					if (index_Selected != NUMBER_OF_OPTIONS - 1) {
						selected[index_Selected++] = 0;
						selected[index_Selected] = 1;
					}
					break;
				case SDLK_ESCAPE:
					Menu_Running = 0;
					return  NUMBER_OF_OPTIONS;
					break;
				case SDLK_RETURN:
					Menu_Running = 0;
					return index_Selected+1;
					break;
				}
			case SDL_KEYUP:


			default: {}
			}
		}

		//Draw rect && text	
		SDL_SetRenderDrawColor(renderer, 0, 200, 200, 255);
		SDL_RenderFillRect(renderer, &menu_square);

		for (i = 0; i < NUMBER_OF_OPTIONS; i++) {
			options[i].x = SCREEN_WIDTH / 2 - OPTION_WIDTH / 2;
			options[i].y = SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - i - 1)*(OPTION_HEIGHT + 15) + 150;
			options[i].h = OPTION_HEIGHT;
			options[i].w = OPTION_WIDTH;


			surfaceMessage = TTF_RenderText_Blended(font, text[i], selected[i] ? Red : White);
			Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			SDL_RenderCopy(renderer, Message, NULL, &options[i]);
			SDL_DestroyTexture(Message);
			SDL_FreeSurface(surfaceMessage);


		}
		//render_game(renderer, &game);
		//Drawing everything
		SDL_RenderPresent(renderer);
		SDL_Delay(20);
	}
	TTF_CloseFont(font);
	TTF_Quit();
}