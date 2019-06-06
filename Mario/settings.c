//#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include<SDL_image.h>
//#include <SDL_ttf.h> 

//#include "map.h"
//#include "mario.h"    // msm da nam je samo main menu potreban ovde 
#include "main_menu.h"
//#include "settings.h"

//za settings
#define NUMBER_OF_SETTINGS_OPTIONS 3 
short sound = 1; // GAME SOUND
short marioCharacter = 0; // green or red character
short selectedBackground = 0;

int showSettings(SDL_Renderer *renderer) {
	if (TTF_Init() < 0) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}

	// options for settings
	char *text[NUMBER_OF_SETTINGS_OPTIONS] = { "Sound","Character","Background" };
	// TTF init
	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 80);
	if (font == NULL) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}

	// colors
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Red = { 255,0,0 };

	SDL_Surface* surfaceMessage = NULL;
	SDL_Texture* Message = NULL;

	// menu 
	SDL_Rect menu_square, options[NUMBER_OF_SETTINGS_OPTIONS];
	menu_square.x = SCREEN_WIDTH / 2 - MENU_WIDTH / 2;
	menu_square.y = SCREEN_HEIGHT / 2 - MENU_HEIGHT / 2;
	menu_square.h = MENU_HEIGHT;
	menu_square.w = MENU_WIDTH;
	// options             u main menu moze ovo da se izbaci iz for petlje cisto da ga ne izracunava bezpotrebno uvek
	for (int i = 0; i < NUMBER_OF_SETTINGS_OPTIONS; i++) {
		options[i].x = SCREEN_WIDTH / 2 - OPTION_WIDTH;
		options[i].y = SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - i - 1)*(OPTION_HEIGHT + 15) + 150;
		options[i].h = OPTION_HEIGHT;
		options[i].w = OPTION_WIDTH;
	}

	// selected option
	int selected[NUMBER_OF_SETTINGS_OPTIONS] = { 0 };
	selected[0] = 1;
	int index_Selected = 0;

	// ON_OFF -> ON/OFF for sound
	SDL_Rect ON_OFF;
	ON_OFF.x = SCREEN_WIDTH / 2 + OPTION_WIDTH / 2;
	ON_OFF.y = SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - 1)*(OPTION_HEIGHT + 15) + 150;
	ON_OFF.w = 100;
	ON_OFF.h = OPTION_HEIGHT;

	char *ON_OFF_text[] = { "ON","OFF" };
	short sound_status = 0;
	
	// character select
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface *mRed = IMG_Load("Slike/MarioRed.png");
	SDL_Surface *mGreen = IMG_Load("Slike/MarioGreen.png");
	if (mRed == NULL && mGreen==NULL)
	{
		printf("%s\n", SDL_GetError());
	}
	SDL_Texture *character[2];
	character[0] = SDL_CreateTextureFromSurface(renderer, mRed);
	character[1] = SDL_CreateTextureFromSurface(renderer, mGreen);
	short selectedCharacter = 0;
	SDL_FreeSurface(mRed);
	SDL_FreeSurface(mGreen);

	SDL_Rect characterRect = { SCREEN_WIDTH / 2 + OPTION_WIDTH / 2,SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - 2)*(OPTION_HEIGHT + 15) + 150, 70,60 };

	//background select
	SDL_Surface *back1 = IMG_Load("Slike/background1.png");
	SDL_Surface *back2 = IMG_Load("Slike/background2.png");
	if (back1 == NULL || back2 == NULL) {
		printf("%s\n", SDL_GetError());
	}
	SDL_Texture *background[2];
	background[0] = SDL_CreateTextureFromSurface(renderer, back1);
	background[1] = SDL_CreateTextureFromSurface(renderer, back2);
	SDL_FreeSurface(back1);
	SDL_FreeSurface(back2);

	SDL_Rect backgroundRect= { SCREEN_WIDTH / 2 + OPTION_WIDTH / 2,SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - 3)*(OPTION_HEIGHT + 15) + 150 ,100,100 };


	// event
	SDL_Event event;

	/* RUN SETTINGS */
	int settingsRunning = 1;
	while (settingsRunning != 0) {
		// input 
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:       // escape - go back to main menu
					settingsRunning = 0;
					break;
				case SDLK_UP:     // key_up - select up option
					if (index_Selected != 0) {
						selected[index_Selected--] = 0;
						selected[index_Selected] = 1;
					}
					break;
				case SDLK_DOWN:   // key_down - select down option
					if (index_Selected != NUMBER_OF_SETTINGS_OPTIONS - 1) {
						selected[index_Selected++] = 0;
						selected[index_Selected] = 1;
					}
					break;
				case SDLK_RETURN:  // return - change selected setting
					if (index_Selected == 0) {      // change on of
						if (sound_status == 1) sound = sound_status = 0;
						else sound = sound_status = 1;
					}
					else if(index_Selected==1){  // promeniti u else if ako se dodaje jos neka opcija u settings
						if (selectedCharacter == 0) marioCharacter=selectedCharacter = 1;
						else marioCharacter=selectedCharacter = 0;
					}
					else if (index_Selected == 2) {
						if (selectedBackground == 0) selectedBackground = 1;
						else selectedBackground = 0;
					}
					break;
				}
			}
		}

		// menu background color
		SDL_SetRenderDrawColor(renderer, 0, 200, 200, 255);
		SDL_RenderFillRect(renderer, &menu_square);

		// options color, possition and drawing
		for (int i = 0; i < NUMBER_OF_SETTINGS_OPTIONS; i++) {
			// draw options
			surfaceMessage = TTF_RenderText_Blended(font, text[i], selected[i] ? Red : White);
			Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			SDL_RenderCopy(renderer, Message, NULL, &options[i]);
			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(Message);
		}
		// draw sound status 
		surfaceMessage = TTF_RenderText_Blended(font, ON_OFF_text[sound_status], selected[0] ? Red : White);
		Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_RenderCopy(renderer, Message, NULL, &ON_OFF);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);

		// draw character
		SDL_RenderCopy(renderer, character[selectedCharacter], NULL, &characterRect); // draw SDL texture

		// draw selected background
		SDL_RenderCopy(renderer, background[selectedBackground], NULL, &backgroundRect);
		

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(character[0]);
	SDL_DestroyTexture(character[1]);
	SDL_DestroyTexture(background[0]);
	SDL_DestroyTexture(background[1]);
	TTF_CloseFont(font);
	TTF_Quit();
	return 0;
}