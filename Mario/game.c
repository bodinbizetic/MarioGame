#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <string.h>
#include "map.h"
#include "mario.h"
#include "main_menu.h"
#include "game.h"

extern int fly_cheat;
extern int immortality_cheat;

#define MAX_MAP_WIDTH 100000
//blok sluzi kao jedan blok cije se dimenzije racunaju prema ekranu
Pair_xy blok;
int collision(Pair_xy dim1, Pair_xy coord1, Pair_xy dim2, Pair_xy coord2, Pair_xy speed1, Pair_xy speed2) {
	
	Pair_xy relSpeed;
	relSpeed.x = speed1.x - speed2.x;
	relSpeed.y = speed1.y - speed2.y;
	Pair_xy c1,c2;
	int dx, dy;
	c1.x = (2 * coord1.x + dim1.x + 2 * speed1.x);
	c1.y = (2 * coord1.y + dim1.y + 2 * speed1.y);
	c2.x = (2 * coord2.x + dim2.x + 2 * speed2.x);
	c2.y = (2 * coord2.y + dim2.y + 2 * speed2.y);
	//c1.x += relSpeed.x;
	//c1.y += relSpeed.y;
	dx = abs(c1.x - c2.x);
	dy = abs(c1.y - c2.y);
	if (dx <= (dim1.x + dim2.x + EPSILON) && dy <= (dim1.y + dim2.y)) {
		/*if (relSpeed.y < 0)
			return 2;
		if (relSpeed.y > 0)
			return 1;
		return 2;*/
		
		//return 2;
		int player_bottom = coord1.y + dim1.y;
		int tiles_bottom = coord2.y + dim2.y;
		int player_right = coord1.x + dim1.x;
		int tiles_right = coord2.x + dim2.x;

		int b_collision = tiles_bottom - coord1.y;
		int t_collision = player_bottom - coord2.y;
		int l_collision = player_right - coord2.x;
		int r_collision = tiles_right - coord1.x;

		if (relSpeed.y >= 0 && player_bottom <= coord2.y && player_bottom + relSpeed.y >= coord2.y && dx < (dim1.x + dim2.x + EPSILON))
			//bot
			return 2;

		if (relSpeed.y < 0 && tiles_bottom <= coord1.y && coord1.y + relSpeed.y < tiles_bottom && dx < (dim1.x + dim2.x + EPSILON))
			//top
			return 1;
		if (relSpeed.x >= 0 && player_right <= coord2.x && player_right + relSpeed.x > coord2.x && dy < (dim1.y + dim2.y))
			//right 
			return 3;
		if (relSpeed.x <= 0 && coord1.x >= tiles_right && coord1.x + relSpeed.x < tiles_right && dy < (dim1.y + dim2.y))
			//left 
			return 4;
		/*if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
		{
			//Left collision
			return 3;
		}
		if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
		{
			//Right collision
			return 4;
		}
		if (t_collision <= b_collision && t_collision <= l_collision && t_collision <= r_collision)
		{
			//Top collision
			return 2;
		}
		if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
		{
			//bottom collision
			return 1;
		}*/
		
		//return 5;
	
	}

	/*if (dy <= (dim1.y + dim2.y) / 2) {
		
			return 2;
	}*/
	return 0;
}

int simpleCollision(Pair_xy dim1, Pair_xy coord1, Pair_xy dim2, Pair_xy coord2, Pair_xy speed1, Pair_xy speed2) {
	Pair_xy relSpeed;
	relSpeed.x = speed1.x - speed2.x;
	relSpeed.y = speed1.y - speed2.y;
	Pair_xy c1, c2;
	int dx, dy;
	c1.x = (2 * coord1.x + dim1.x + 2 * speed1.x);
	c1.y = (2 * coord1.y + dim1.y + 2 * speed1.y);
	c2.x = (2 * coord2.x + dim2.x + 2 * speed2.x);
	c2.y = (2 * coord2.y + dim2.y + 2 * speed2.y);
	//c1.x += relSpeed.x;
	//c1.y += relSpeed.y;
	dx = abs(c1.x - c2.x);
	dy = abs(c1.y - c2.y);
	if (dx <= (dim1.x + dim2.x + EPSILON) && dy <= (dim1.y + dim2.y))
		return 1;
	return 0;
}
//DrawScreen crta na ekranu
extern short selectedBackground;
void drawScreen(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario, SDL_Texture *block_Texture[AI_NUMBER][5]) {
	//Init TTF
	if (TTF_Init() < 0) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}
	//Surface for TTF text
	SDL_Surface* surfaceMessage = NULL;
	SDL_Texture* Message = NULL;
	SDL_Color White = { 255, 255, 255 };
	char text[30], text1[30] = "Score: ";
	_itoa((map->x_score/SCORE_COEF + map->score), text, 10);
	strcat(text1, text);
	//Text back rectangle
	TTF_Font* font = TTF_OpenFont("Acme-Regular.ttf", 50);
	SDL_Rect score_square;
	score_square.x = SCREEN_WIDTH / 80;
	score_square.y = SCREEN_HEIGHT / 80;
	score_square.h = SCORE_HEIGHT;
	score_square.w = SCORE_WIDTH;


	int i, j, x = 0, y = 0;
	SDL_Rect rect = { x,y,0, 0 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // ovo visak ?
	SDL_RenderClear(renderer);                       // ovo visak ?
	/*for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j <= MAP_WIDTH; j++) {
			rect.x = j * blok.x;
			rect.y = i * blok.y;
			rect.w = blok.x;
			rect.h = blok.y;
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}*/

	SDL_Rect background = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	SDL_RenderCopy(renderer, block_Texture[sky][selectedBackground], NULL, &background);

	surfaceMessage = TTF_RenderText_Blended(font, text1, White);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_RenderCopy(renderer, Message, NULL, &score_square);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(font);

	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = mario->coordinates.x + map->x_passed;
			new_coordinates.y = mario->coordinates.y + mario->speed.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x+ map->x_passed;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				// ground block
				SDL_RenderCopy(renderer, block_Texture[ground][0], NULL, &rect);
				/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);*/
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x+ map->x_passed;
				if (g->coordinate.y != g->newCordinate.y) g->coordinate.y++;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				// basic block
				SDL_RenderCopy(renderer, block_Texture[basic][0], NULL, &rect);
				/*SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255);
				SDL_RenderFillRect(renderer, &rect);*/
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x+ map->x_passed;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				SDL_RenderCopy(renderer, block_Texture[question][g->animation_Stage], NULL, &rect);
				/*SDL_SetRenderDrawColor(renderer, 255, 211, 0, 255);
				SDL_RenderFillRect(renderer, &rect);*/
				break;
			}
			case hidden: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x+ map->x_passed;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				if(g->animation_Stage == 1)//nije skroz ispraznjen
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				else
					SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
				
				SDL_RenderFillRect(renderer, &rect);
				break;
			}
			case pipe: {
				//Zovi kad budes iscrtavao pipe
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x+ map->x_passed;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				SDL_RenderCopy(renderer, block_Texture[pipe][0], NULL, &rect);
				//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				//SDL_RenderFillRect(renderer, &rect);
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
extern int marioCharacter;
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario) {
	blok.x = SCREEN_WIDTH / MAP_WIDTH;
	blok.y = SCREEN_HEIGHT / MAP_HEIGHT;

	SDL_Texture *block_Texture[AI_NUMBER][5]; // 5 animacija ili manje (zavisi od AI-a)

	Map *mapa;
	Mario *probni_mario;

	Pair_xy update = { 0,0 };
	probni_mario = malloc(sizeof(Mario));
	probni_mario->size.x = blok.x * (MARIO_SHRINK_X) / 100;
	probni_mario->size.y = 2*blok.y * MARIO_SHRINK / 100;
	probni_mario->dimension.x = blok.x ;//dimension samo sluzi za iscrtavanje
	probni_mario->dimension.y = 2 * blok.y * MARIO_SHRINK / 100;
	probni_mario->coordinates.x = SCREEN_WIDTH / 2 + 2*blok.x + blok.x * (100 - MARIO_SHRINK_X) / 200;
	probni_mario->coordinates.y = 3*blok.y + (100 - MARIO_SHRINK) * blok.y / 100;
	probni_mario->speed.x = 0;
	probni_mario->speed.y = 0;
	probni_mario->lives = 2;
	probni_mario->jump_timer = 0;
	probni_mario->immortality_timer = 0;
	probni_mario->projectileTimer = 0;

	/*map->x_passed = blok.x;
	map->score = 0;*/
	immortality_cheat = 0;
	fly_cheat = 0;
	int deathAnimation = 1;

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

		//	AI
		//turtle
		surface = IMG_Load("Slike/turtleStandRight.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[turtle][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/turtleMoveRight.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[turtle][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/turtleStandLeft.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[turtle][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/turtleMoveLeft.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[turtle][3] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/turtleShield.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[turtle][4] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/devil1.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[devil][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/devil2.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[devil][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/devilDeath.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[devil][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// plantie
		surface = IMG_Load("Slike/plantieClosed.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[plantie][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/plantieOpen.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[plantie][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// red shroom
		surface = IMG_Load("Slike/redShroom.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[shroom][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/greenShroom.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[shroom][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// coin
		surface = IMG_Load("Slike/coin.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[shroom][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

			// blocks 
		// basic
		surface = IMG_Load("Slike/basic.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[basic][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		
		// ground
		surface = IMG_Load("Slike/ground.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[ground][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// question block
		surface = IMG_Load("Slike/question.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[question][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/questionHit.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[question][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// pipe
		surface = IMG_Load("Slike/pipe.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[pipe][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/poklopac.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[pipe][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		//background
		surface = IMG_Load("Slike/background1.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[sky][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/background2.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[sky][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	//postoji funkcija koja inicijalizuje mapu
	mapa = initMap(block_Texture);
	
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
		if (probni_mario->lives == 0) break; 
		while (SDL_PollEvent(&eventgame)) {
			switch (eventgame.type) {
			case SDL_QUIT:
				Running = 0;
				return NUMBER_OF_OPTIONS;
			case SDL_KEYDOWN:
			{
				switch (eventgame.key.keysym.sym) {
				case SDLK_f:
					fly_cheat = !fly_cheat;
					break;
				case SDLK_i:
					immortality_cheat = !immortality_cheat;
					break;
				case SDLK_ESCAPE:
					Running = 0;
					deathAnimation = 0;
					break;
					//return  0; zbog ovog je curila memorija??		
				case SDLK_p: { 
					pause_game();
					break;
				}
				
				case SDLK_SPACE: {
					if (probni_mario->lives > 2) {
						Pair_xy coord;
						coord.x = probni_mario->coordinates.x + (!probni_mario->direction ? 0 : probni_mario->size.x);
						coord.y = probni_mario->coordinates.y + probni_mario->size.y / 2;
						if (probni_mario->projectileTimer == 0) {
 							spawnProjectile(mapa, coord, !probni_mario->direction, probni_mario->speed.x);
							probni_mario->projectileTimer++;
						}
					}
					break;
				}
				
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

		//updateMapItems(mapa);
		drawScreen(window, renderer, mapa, probni_mario, block_Texture);
		//SDL_Rendercopy(renderer, NULL, &map->camera, NULL);
		updateAI(mapa, probni_mario);
		updateMario(window,renderer,mapa,probni_mario,update,block_Texture);

		drawAI(window, renderer, mapa);
		SDL_RenderPresent(renderer);

	}
	// Save game
	/*FILE *save = fopen("Savegame.bin", "wb");
	if (save == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		exit(EXIT_FAILURE);
	}
	// save mario
	//fwrite(&probni_mario, sizeof(Mario), 1, save);
	// save map
	//fwrite(&mapa, sizeof(Map), 1, save);
	//fclose(save);*/

	// mario death
	if (deathAnimation) {
		SDL_Rect rect = { probni_mario->coordinates.x + mapa->x_passed,probni_mario->coordinates.y,probni_mario->size.x,probni_mario->size.y };
		SDL_Surface *sur = NULL;
		if (marioCharacter == 0) sur = IMG_Load("Slike/marioDeathRed.png");
		else sur = IMG_Load("Slike/marioDeathGreen.png");
		SDL_Texture *death = SDL_CreateTextureFromSurface(renderer, sur);
		SDL_FreeSurface(sur);


		while (rect.y != SCREEN_HEIGHT) {
			rect.y++;
			drawScreen(window, renderer, mapa, probni_mario, block_Texture);
			drawAI(window, renderer, mapa);
			SDL_RenderCopy(renderer, death, NULL, &rect);

			SDL_RenderPresent(renderer);
		}
		SDL_DestroyTexture(death);
	}


	// free memory 
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 3; k++)
				SDL_DestroyTexture(probni_mario->animation[i][j][k]);

	for (int i = 0; i < AI_NUMBER; i++) {
		if (i == devil) {
			for (int j = 0; j < 3; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
		else if (i == turtle) {
			for (int j = 0; j < 5; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
	}
	SDL_DestroyTexture(block_Texture[sky][0]);
	SDL_DestroyTexture(block_Texture[sky][1]);
	SDL_DestroyTexture(block_Texture[ground][0]);
	SDL_DestroyTexture(block_Texture[basic][0]); // ovo ubaciti gore u for kad se naprave svi blokovi i ai-ovi
	SDL_DestroyTexture(block_Texture[question][0]);
	SDL_DestroyTexture(block_Texture[shroom][0]);
	SDL_DestroyTexture(block_Texture[shroom][1]);

	free(probni_mario);
	//SDL_DestroyTexture(object_Ground);
	// treba AI free da se doda !!!
	// mapa - pomocna mapa , treba da se zameni u free(map)
	destroyMap(mapa);
	return 0;
}