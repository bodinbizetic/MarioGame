#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

/*!	\file main_menu.c
*	\brief Contains functions which show main menu
*/

/*!	
*	\brief Width of the window
*/
#define SCREEN_WIDTH 1024

/*!
*	\brief Height of the window
*/
#define SCREEN_HEIGHT 720

/*!
*	\brief Width of the menu
*/
#define MENU_WIDTH 600

/*!
*	\brief Height of the menu
*/
#define MENU_HEIGHT 650

/*!
*	\brief Numver of menu options
*/
#define NUMBER_OF_OPTIONS 6

/*!
*	\brief Height of the single option
*/
#define OPTION_HEIGHT 80

/*!
*	\brief Width of the single option
*/
#define OPTION_WIDTH 300

/*!
*	\brief Function that show main menu on the screen
*	\param window Address of current active SDL_Window
*	\param renderer Address of main SDL_Renderer
*	\return returns id of selected menu option
*/
int show_menu(SDL_Window *window, SDL_Renderer *renderer) {
	//Init TTF
	if (TTF_Init() < 0) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}

	SDL_Surface *surface = IMG_Load("Slike/backgoundmenu.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	
	SDL_Texture *menuBackground = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//Menu square init
	int i,Menu_Running=1;
	char *text[NUMBER_OF_OPTIONS] = { "Demo", "New game", "Continue",  "High Score", "Settings",  "Quit" };
	//Settings for TTF text
	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 80);
	TTF_Font* font2 = TTF_OpenFont("Acme-Regular.ttf", 90);
	if (font == NULL) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}
	//Selected and not-selected color
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0,0,0 };
	SDL_Color Red = { 255,0,0, 100};

	//Surface for TTF text
	SDL_Surface* surfaceMessage = NULL;
	SDL_Texture* Message = NULL;

	//Text back rectangle
	SDL_Rect menu_square, options[NUMBER_OF_OPTIONS];
	/*menu_square.x = SCREEN_WIDTH / 2 - MENU_WIDTH / 2;
	menu_square.y = SCREEN_HEIGHT / 2 - MENU_HEIGHT / 2;
	menu_square.h = MENU_HEIGHT;
	menu_square.w = MENU_WIDTH;*/
	menu_square.x = 0;
	menu_square.y = 0;
	menu_square.w = SCREEN_WIDTH;
	menu_square.h = SCREEN_HEIGHT;

	int selected[NUMBER_OF_OPTIONS] = { 0 };
	selected[0] = 1;
	int index_Selected = 0;

	for (i = 0; i < NUMBER_OF_OPTIONS; i++) {
		options[i].x = SCREEN_WIDTH / 2 - OPTION_WIDTH / 2;
		options[i].y = SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - i - 1)*(OPTION_HEIGHT + 15) + 150;
		options[i].h = OPTION_HEIGHT;
		options[i].w = OPTION_WIDTH;
	}
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
					SDL_DestroyTexture(menuBackground);
					return  NUMBER_OF_OPTIONS;
					break;
				case SDLK_RETURN:
					Menu_Running = 0;
					SDL_DestroyTexture(menuBackground);
					return index_Selected+1;
					break;
				}
			case SDL_KEYUP:


			default: {}
			}
		}
		SDL_RenderClear(renderer);
		//Draw rect && text	
		//SDL_SetRenderDrawColor(renderer, 0, 200, 200, 255);
		//SDL_RenderFillRect(renderer, &menu_square);
		SDL_RenderCopy(renderer, menuBackground, NULL, &menu_square);
		
		for (i = 0; i < NUMBER_OF_OPTIONS; i++) {

			surfaceMessage = TTF_RenderText_Blended(font2, text[i], Black);
			Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			SDL_FreeSurface(surfaceMessage);

			SDL_Rect temp = options[i];
			temp.x -= 10;
			temp.w += 20;
			temp.y -= 5;
			temp.h += 10;

			SDL_RenderCopy(renderer, Message, NULL, &temp);
			SDL_DestroyTexture(Message);

			surfaceMessage = TTF_RenderText_Blended(font, text[i], selected[i] ? Red : White);
			Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			SDL_FreeSurface(surfaceMessage);
			SDL_RenderCopy(renderer, Message, NULL, &options[i]);
			SDL_DestroyTexture(Message);

		}
		//render_game(renderer, &game);
		//Drawing everything
		SDL_RenderPresent(renderer);
	}
	
	TTF_CloseFont(font);
	TTF_Quit();
}

// pause game

/*!
*		\brief pauses the game when you press p and if you want to unpause press p again
*		\return no return
*/


void pause_game() // pauzira igricu pritiskom na p 
{
	SDL_Event event;
	int pause_runing = 1;
	while (pause_runing) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym) {
				case SDLK_p:
					pause_runing = 0;
					break;
				}
				break;
			}
			case SDL_KEYUP: {
				break;
			}
			default: {}
			}
		}
	}
	IMG_Quit();
}