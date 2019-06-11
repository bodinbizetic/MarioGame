#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_ttf.h>

#include "map.h"
#include "mario.h"
#include "main_menu.h"
#include "highscore.h"

/*!	\file highscore.c
*	\brief Contains declarations and constants for higscore and end game menu
*/

/*!
*	\brief Maximum number of players that can have a highscore
*/
#define NUMBER_OF_BEST_PLAYERS 5
#define MAX 50
#define OPTION_WIDTH2 500
/*!
*	\brief Prints the final score screen and input of name for the highscore
*	\param currScore final score which will be saved
*	\param name name of the player
*	\param nameSave if name should be saved has value 1, otherwise 0
*/
void finalScoreScreen(int currScore, char * name, int * nameSave, SDL_Renderer *renderer) {
	int currPos = 0, finalScoreActive = 1, i;
	SDL_Event event;
	SDL_Rect rect;
	SDL_Surface *surface;
	SDL_Texture *tex;
	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 80);
	SDL_Color white = { 255, 255, 255 };
	char buffer[10], string[50] = "CONGRADULATIONS! YOUR FINAL SCORE IS: ";

	_itoa_s(currScore, buffer, 10, 10);
	strcat_s(string, 50, buffer);
	surface = TTF_RenderText_Blended(font, string, white);
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	rect.x = SCREEN_WIDTH / 15;
	rect.y = 4 * (SCREEN_HEIGHT / 40);
	rect.w = SCREEN_WIDTH / 2;
	rect.h = SCREEN_HEIGHT / 12;
	SDL_RenderCopy(renderer, tex, NULL, &rect);
	SDL_DestroyTexture(tex);

	rect.x = SCREEN_WIDTH / 15;
	rect.y = 10 * (SCREEN_HEIGHT / 40);
	rect.w = SCREEN_WIDTH / 5;
	rect.h = SCREEN_HEIGHT / 12;
	SDL_RenderCopy(renderer, finalScoreTextureManager.typeInYourNameTexture, NULL, &rect);

	rect.y = 14 * (SCREEN_HEIGHT / 40);
	rect.w = SCREEN_WIDTH / 24;
	rect.h = SCREEN_HEIGHT / 10;
	/*for (i = currPos; i <= MAX_NAME - 1; i++) {
		rect.x = SCREEN_WIDTH / 18 + i * SCREEN_WIDTH / 10 + 1;
		SDL_RenderFillRect(renderer, &rect);
		if (i != MAX_NAME - 1)
			SDL_RenderCopy(renderer, finalScoreTextureManager.blankTexture, NULL, &rect);
	}*/
	extern int Game_Running;
	while (finalScoreActive) {
		for (i = currPos; i <= MAX_NAME - 2; i++) {
			rect.x = SCREEN_WIDTH / 18 + i * (SCREEN_WIDTH / 24 + 1);
			SDL_RenderFillRect(renderer, &rect);
			if (i != MAX_NAME - 1)
				SDL_RenderCopy(renderer, finalScoreTextureManager.blankTexture, NULL, &rect);
		}
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_KEYDOWN:
				rect.x = SCREEN_WIDTH / 18 + currPos * SCREEN_WIDTH / 24;
				switch (event.key.keysym.sym) {
				case SDLK_BACKSPACE:
					name[currPos] = '\0';
					currPos = currPos ? currPos - 1 : currPos;
					break;
				case SDLK_RETURN:
					finalScoreActive = 0;
					break;
				case SDLK_ESCAPE:
					finalScoreActive = 0;
					*nameSave = 0;
					break;
				default:
					if (currPos < MAX_NAME - 1) {
						if (event.key.keysym.sym <= SDLK_9 && event.key.keysym.sym >= SDLK_0) {
							name[currPos++] = MAP_SDL_NUMBERS(event.key.keysym.sym);
							//SDL_RenderFillRect(renderer, &rect);
							SDL_RenderCopy(renderer, finalScoreTextureManager.characterTextures[name[currPos - 1]], NULL, &rect);
						}
						else if (event.key.keysym.sym <= SDLK_z && event.key.keysym.sym >= SDLK_a) {
							name[currPos++] = MAP_SDL_LETTERS(event.key.keysym.sym) + 'A' - 'a';
							//SDL_RenderFillRect(renderer, &rect);
							SDL_RenderCopy(renderer, finalScoreTextureManager.characterTextures[name[currPos - 1]], NULL, &rect);

						}
					}
					break;
				}


				break;

			case SDL_QUIT:
				Game_Running = 0;
				return;
			}
		}
		SDL_RenderPresent(renderer);
	}
	name[currPos] = '\0';
	TTF_CloseFont(font);
	return;
}

/*!
*	\brief Initializes the textures for the final score screen
*/
void initFinalScoreTextures(SDL_Renderer *renderer) {
	char temp[2], c;
	extern FinalScoreTextures finalScoreTextureManager;

	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 80);
	SDL_Color white = { 255, 255, 255 };
	SDL_Color yellow = { 255, 255, 0 };
	SDL_Surface * tempSurface;
	int i = 0;
	temp[1] = '\0';
	for (c = '0'; c <= '9'; c++) {
		temp[0] = c;
		tempSurface = TTF_RenderText_Solid(font, temp, white);
		finalScoreTextureManager.characterTextures[c] = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}
	for (c = 'A'; c <= 'Z'; c++) {
		temp[0] = c;
		tempSurface = TTF_RenderText_Solid(font, temp, white);
		finalScoreTextureManager.characterTextures[c] = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}
	tempSurface = SDL_LoadBMP("Slike/blankChar.bmp");
	finalScoreTextureManager.blankTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = TTF_RenderText_Solid(font, "TYPE IN YOUR NAME:", white);
	finalScoreTextureManager.typeInYourNameTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	TTF_CloseFont(font);
	return;
}

/*!
*	\brief Destroys all end game textures
*/
void destroyFinalScoreTextures() {
	char c;
	extern FinalScoreTextures finalScoreTextureManager;
	for (c = '0'; c <= '9'; c++) {
		SDL_DestroyTexture(finalScoreTextureManager.characterTextures[c]);
	}
	for (c = 'A'; c <= 'Z'; c++) {
		SDL_DestroyTexture(finalScoreTextureManager.characterTextures[c]);
	}
	SDL_DestroyTexture(finalScoreTextureManager.blankTexture);
	SDL_DestroyTexture(finalScoreTextureManager.typeInYourNameTexture);
}

/*!
*		\brief checks for file corruption
*		\return No return
*/

int scoreOK()
{
	FILE *XORBIVSI = fopen("xor.txt", "r");
	FILE *score = fopen("highscore.txt", "r");
	int index = 0;
	char ime[5][20];
	int poeni[5];

	int XOR = 0;
	for (int i = 0; i < 5; i++) {
		fscanf(score, "%d %s %d", &index, ime[i], &poeni[i]);
		XOR ^= index;
		XOR ^= ime[i][0];
		XOR ^= poeni[i];
	}

	int XOR2 = 0;
	fscanf(XORBIVSI, "%d", &XOR2);
	fclose(XORBIVSI);
	fclose(score);


	if (XOR2 == XOR) return 1;
	return 0;
}

/*!
*		\brief Update highscore text document after the game if the player scored enough points
*		\param score Player score after the game
*		\param name Name of the player 
*		\param a check if the escape button is pressed and if it is pressed then dont update highscore text document 
*		\return returns 0
*/
void updateHighscore(int score, char *name, int a)
{
	if (a)
	{
		int XOR = 0;
		FILE *provera = fopen("Highscore.txt", "r");
		if (provera == NULL) {
			printf("Greska pri otvaranju datoteke!\n");
			exit(EXIT_FAILURE);
		}
		int red;
		char ime[5][20];
		int poeni[5];
		for (int i = 0; i < 5; i++) {
			fscanf(provera, "%d %s %d", &red, ime[i], &poeni[i]);
		}
		int index = 5;
		for (int i = 0; i < 5; i++) {
			if (score > poeni[i]) {
				index = i;
				break;
			}
		}
		fclose(provera);
		// <5 treba azuriranje
		if (index < 5)
		{
			if (strlen(name) == 0) strcpy(name, "noName\0");
			for (int i = 4; i > index; i--) {
				poeni[i] = poeni[i - 1];
				strcpy(ime[i], ime[i - 1]);
			}
			poeni[index] = score;
			strcpy(ime[index], name);

			// upis novih u datoteku
			FILE *upis = fopen("Highscore.txt", "w");
			if (upis == NULL) {
				strerror(errno);
				exit(EXIT_FAILURE);
			}
			for (int i = 0; i < 5; i++)
			{
				fprintf(upis, "%d %s %d\n", i + 1, ime[i], poeni[i]);
			}
			fclose(upis);

			FILE *xorf = fopen("Highscore.txt", "r");
			if (xorf == NULL) {
				printf("Greska!\n");
				exit(EXIT_FAILURE);
			}

			for (int i = 0; i < 5; i++) {
				fscanf(xorf, "%d %s %d", &index, ime[i], &poeni[i]);
				XOR ^= index;
				XOR ^= ime[i][0];
				XOR ^= poeni[i];
			}
			fclose(xorf);
			FILE *xorout = fopen("xor.txt", "w");
			if (xorout == NULL) {
				printf("Greska!\n");
				exit(EXIT_FAILURE);
			}
			fprintf(xorout, "%d", XOR);
			fclose(xorout);
		}
	}
}


/*!
*		\brief show highscore of top 5 players
*		\param renderer for drawing on screen
*		\return returns 0
*/
int showHighscore(SDL_Renderer *renderer) {
	if (scoreOK() == 0) {
		FILE *ispis = fopen("Highscore.txt", "w");
		if (ispis == NULL) {
			printf("Greska!\n");
			exit(EXIT_FAILURE);
		}


		for (int i = 0; i < 5; i++) {
			fprintf(ispis, "%d %s %d\n", i + 1, "noName", 0);
		}
		fclose(ispis);
	}

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

	FILE *load = fopen("Highscore.txt", "r");
	for (int i = 0; i < NUMBER_OF_BEST_PLAYERS; i++) {
		fgets(text[i], MAX, load);
	}

	fclose(load);
	// rect for scores and players
	SDL_Rect drawScore[NUMBER_OF_BEST_PLAYERS];
	for (int i = 0; i < NUMBER_OF_BEST_PLAYERS; i++) {
		drawScore[i].x = SCREEN_WIDTH / 2 - OPTION_WIDTH2 / 2 + 25;
		drawScore[i].y = SCREEN_HEIGHT / 2 - (NUMBER_OF_OPTIONS - i - 1)*(OPTION_HEIGHT + 15) + 150;
		drawScore[i].h = OPTION_HEIGHT;
		drawScore[i].w = OPTION_WIDTH2;
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