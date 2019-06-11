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
#include "highscore.h"
#include "sound.h"
#define MAX_MAP_WIDTH 100000

/*!	\file game.c
*	\brief Contains game loop, save/load and encypt functions
*/
extern int fly_cheat;
extern int immortality_cheat;

int isFileOK(char *Name2) {
	int XOR_2 = 0;
	int c,d = 0;
	int e = 0,f=0;
	int brojac = 0;
	FILE *saved = fopen(Name2, "r");
	fseek(saved, 0, SEEK_SET);
	while ( fscanf(saved, "%d", &d) >0) {
		XOR_2 ^= f;
		brojac++;
		f = e;
		e = d;
	}
	fclose(saved);
	brojac -= 2;
	if (e == XOR_2 && f == brojac)
		return 0;
	return 1;
}

Map* loadMap(Mario *mario, Map *map, char *Name2, SDL_Texture *block_Texture[AI_NUMBER][5], SDL_Renderer *renderer) {
	map = malloc(sizeof(Map));
	FILE *saved = fopen(Name2, "r");
	fseek(saved, 0, SEEK_SET);
	int i, j, n, m, XOR = 0, XOR_IN;
	if (saved == NULL)
		return 0;
	fscanf(saved, "%d", &n);
	XOR ^= n;
	for (i = 0; i < n; i++) {
		if (i == ground || i == basic || i == question || i == hidden || i == pipe || i == pikes || i == turtle || i == devil || i == plantie || i==flag || i== shroom)
			fscanf(saved, "%d", &m);
		else
			m = 0;
		XOR ^= m;
		map->ai_counter[i] = m;
		for (j = 0; j < m; j++) {
			if (i == ground) {
				Ground *temp = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				map->ai_Matrix[ground][j] = temp;
			}
			if (i == basic) {
				ai_Shroom *temp = malloc(sizeof(ai_Shroom));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->newCordinate.y);
				XOR ^= temp->newCordinate.y;

				map->ai_Matrix[basic][j] = temp;
			}
			if (i == question) {
				ai_Question *temp = malloc(sizeof(ai_Question));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->storage);
				XOR ^= temp->storage;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;

				temp->animation[0] = block_Texture[question][0];
				temp->animation[1] = block_Texture[question][1];

				map->ai_Matrix[question][j] = temp;
			}
			if (i == hidden) {
				ai_Hidden *temp = malloc(sizeof(ai_Hidden));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->coins_Left);
				XOR ^= temp->coins_Left;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				temp->animation[0] = block_Texture[basic][0];
				temp->animation[1] = block_Texture[question][1];

				map->ai_Matrix[hidden][j] = temp;
			}
			if (i == pipe) {
				Ground *temp = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				temp->animation = block_Texture[pipe][0];

				map->ai_Matrix[pipe][j] = temp;

				j++;
				Ground *temp2 = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp2->coordinate.x);
				XOR ^= temp2->coordinate.x;
				fscanf(saved, "%d", &temp2->coordinate.y);
				XOR ^= temp2->coordinate.y;
				fscanf(saved, "%d", &temp2->dimension.x);
				XOR ^= temp2->dimension.x;
				fscanf(saved, "%d", &temp2->dimension.y);
				XOR ^= temp2->dimension.y;
				temp2->animation = block_Texture[pipe][1];

				map->ai_Matrix[pipe][j] = temp2;

			}
			if (i == pikes) {
				ai_Hidden *temp = malloc(sizeof(ai_Hidden));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				temp->animation[0] = block_Texture[pikes][0];
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				map->ai_Matrix[pikes][j] = temp;
			}
			if (i == turtle) {
				ai_Devil *temp = malloc(sizeof(ai_Devil));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->type);
				XOR ^= temp->type;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;
				fscanf(saved, "%d", &temp->time);
				XOR ^= temp->time;
				for (int k = 0; k < 5; k++)
					temp->animation[k] = block_Texture[turtle][k];
				map->ai_Matrix[turtle][j] = temp;
			}
			if (i == devil) {
				ai_Devil *temp = malloc(sizeof(ai_Devil));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->type);
				XOR ^= temp->type;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;
				fscanf(saved, "%d", &temp->time);
				XOR ^= temp->time;
				for (int k = 0; k < 3; k++)
					temp->animation[k] = block_Texture[devil][k];
				map->ai_Matrix[devil][j] = temp;
			}
			if (i == plantie) {
				ai_Plantie *temp = malloc(sizeof(ai_Plantie));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;

				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;
				fscanf(saved, "%d", &temp->timer_Sleep);
				XOR ^= temp->timer_Sleep;
				fscanf(saved, "%d", &temp->additional_Height);
				XOR ^= temp->additional_Height;
				fscanf(saved, "%d", &temp->time);
				XOR ^= temp->time;
				temp->animation[0] = block_Texture[plantie][0];
				temp->animation[1] = block_Texture[plantie][1];
				map->ai_Matrix[plantie][j] = temp;
			}
			if (i == flag) {
				Ground *temp = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				temp->animation = block_Texture[flag][0];
				map->ai_Matrix[flag][j] = temp;
			}
			if (i == shroom) {
				ai_Shroom *temp = malloc(sizeof(ai_Shroom));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->type);
				XOR ^= temp->type;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;

					temp->animation = block_Texture[shroom][0];
				map->ai_Matrix[shroom][j] = temp;
			}
		}
	}
	/*
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH * MAP_SEGMENTS_NUMBER; j++) {
			fscanf(saved, "%d", &map->map_Matrix[i][j]);
			XOR = XOR ^ map->map_Matrix[i][j];
		}
	}
	*/
	fscanf(saved, "%d", &map->x_score);
	XOR = XOR ^ map->x_score;
	fscanf(saved, "%d", &map->score);
	XOR = XOR ^ map->score;
	fscanf(saved, "%d", &map->x_passed);
	XOR = XOR ^ map->x_passed;
	fscanf(saved, "%d", &map->timer);
	XOR = XOR ^ map->timer;

	fclose(saved);
	return map;
}

Mario* loadMario(Mario *mario, Map *mapa, char *Name2, SDL_Texture *block_Texture[AI_NUMBER][5], SDL_Renderer *renderer) {
	mario = malloc(sizeof(Mario));
	Map *map = malloc(sizeof(Map));
	FILE *saved = fopen(Name2, "r");
	fseek(saved, 0, SEEK_SET);
	int i, j, n, m, XOR = 0, XOR_IN;
	if (saved == NULL)
		return 0;
	fscanf(saved, "%d", &n);
	XOR ^= n;
	for (i = 0; i < n; i++) {
		if (i == ground || i == basic || i == question || i == hidden || i == pipe || i == pikes || i == turtle || i == devil || i == plantie || i == flag || i== shroom)
			fscanf(saved, "%d", &m);
		else
			m = 0;
		XOR ^= m;
		map->ai_counter[i] = m;
		for (j = 0; j < m; j++) {
			if (i == ground) {
				Ground *temp = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				map->ai_Matrix[ground][j] = temp;
			}
			if (i == basic) {
				ai_Shroom *temp = malloc(sizeof(ai_Shroom));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->newCordinate.y);
				XOR ^= temp->newCordinate.y;

				map->ai_Matrix[basic][j] = temp;
			}
			if (i == question) {
				ai_Question *temp = malloc(sizeof(ai_Question));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->storage);
				XOR ^= temp->storage;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;

				temp->animation[0] = block_Texture[question][0];
				temp->animation[1] = block_Texture[question][1];

				map->ai_Matrix[question][j] = temp;
			}
			if (i == hidden) {
				ai_Hidden *temp = malloc(sizeof(ai_Hidden));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->coins_Left);
				XOR ^= temp->coins_Left;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				temp->animation[0] = block_Texture[basic][0];
				temp->animation[1] = block_Texture[question][1];

				map->ai_Matrix[hidden][j] = temp;
			}
			if (i == pipe) {
				Ground *temp = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				temp->animation = block_Texture[pipe][0];

				map->ai_Matrix[pipe][j] = temp;

				j++;
				Ground *temp2 = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp2->coordinate.x);
				XOR ^= temp2->coordinate.x;
				fscanf(saved, "%d", &temp2->coordinate.y);
				XOR ^= temp2->coordinate.y;
				fscanf(saved, "%d", &temp2->dimension.x);
				XOR ^= temp2->dimension.x;
				fscanf(saved, "%d", &temp2->dimension.y);
				XOR ^= temp2->dimension.y;
				temp2->animation = block_Texture[pipe][1];

				map->ai_Matrix[pipe][j] = temp2;

			}
			if (i == pikes) {
				ai_Hidden *temp = malloc(sizeof(ai_Hidden));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				temp->animation[0] = block_Texture[pikes][0];
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				map->ai_Matrix[pikes][j] = temp;
			}
			if (i == turtle) {
				ai_Devil *temp = malloc(sizeof(ai_Devil));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->type);
				XOR ^= temp->type;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;
				fscanf(saved, "%d", &temp->time);
				XOR ^= temp->time;
				for (int k = 0; k < 5; k++)
					temp->animation[k] = block_Texture[turtle][k];
				map->ai_Matrix[turtle][j] = temp;
			}
			if (i == devil) {
				ai_Devil *temp = malloc(sizeof(ai_Devil));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->type);
				XOR ^= temp->type;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;
				fscanf(saved, "%d", &temp->time);
				XOR ^= temp->time;
				for (int k = 0; k < 3; k++)
					temp->animation[k] = block_Texture[devil][k];
				map->ai_Matrix[devil][j] = temp;
			}
			if (i == plantie) {
				ai_Plantie *temp = malloc(sizeof(ai_Plantie));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;

				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;
				fscanf(saved, "%d", &temp->timer_Sleep);
				XOR ^= temp->timer_Sleep;
				fscanf(saved, "%d", &temp->additional_Height);
				XOR ^= temp->additional_Height;
				fscanf(saved, "%d", &temp->time);
				XOR ^= temp->time;
				temp->animation[0] = block_Texture[plantie][0];
				temp->animation[1] = block_Texture[plantie][1];
				map->ai_Matrix[plantie][j] = temp;
			}
			if (i == flag) {
				Ground *temp = malloc(sizeof(Ground));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				temp->animation = block_Texture[flag][0];
				map->ai_Matrix[flag][j] = temp;
			}
			if (i == shroom) {
				ai_Shroom *temp = malloc(sizeof(ai_Shroom));
				fscanf(saved, "%d", &temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fscanf(saved, "%d", &temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fscanf(saved, "%d", &temp->dimension.x);
				XOR ^= temp->dimension.x;
				fscanf(saved, "%d", &temp->dimension.y);
				XOR ^= temp->dimension.y;
				fscanf(saved, "%d", &temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fscanf(saved, "%d", &temp->isAlive);
				XOR ^= temp->isAlive;
				fscanf(saved, "%d", &temp->type);
				XOR ^= temp->type;
				fscanf(saved, "%d", &temp->speed.x);
				XOR ^= temp->speed.x;
				fscanf(saved, "%d", &temp->speed.y);
				XOR ^= temp->speed.y;
					temp->animation = block_Texture[shroom][0];
				map->ai_Matrix[shroom][j] = temp;
			}
		}
	}
	/*
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH * MAP_SEGMENTS_NUMBER; j++) {
			fscanf(saved, "%d", &map->map_Matrix[i][j]);
			XOR = XOR ^ map->map_Matrix[i][j];
		}
	}
	*/
	fscanf(saved, "%d", &map->x_score);
	XOR = XOR ^ map->x_score;
	fscanf(saved, "%d", &map->score);
	XOR = XOR ^ map->score;
	fscanf(saved, "%d", &map->x_passed);
	XOR = XOR ^ map->x_passed;
	fscanf(saved, "%d", &map->timer);
	XOR = XOR ^ map->timer;

	//Mario load
	fscanf(saved, "%d", &mario->coordinates.x);
	XOR ^= mario->coordinates.x;
	fscanf(saved, "%d", &mario->coordinates.y);
	XOR ^= mario->coordinates.y;
	fscanf(saved, "%d", &mario->size.x);
	XOR ^= mario->size.x;
	fscanf(saved, "%d", &mario->size.y);
	XOR ^= mario->size.y;
	fscanf(saved, "%d", &mario->speed.x);
	XOR ^= mario->speed.x;
	fscanf(saved, "%d", &mario->speed.y);
	XOR ^= mario->speed.y;
	fscanf(saved, "%d", &mario->dimension.x);
	XOR ^= mario->dimension.x;
	fscanf(saved, "%d", &mario->dimension.y);
	XOR ^= mario->dimension.y;

	fscanf(saved, "%d", &mario->direction);
	XOR ^= mario->direction;
	fscanf(saved, "%d", &mario->lives);
	XOR ^= mario->lives;
	fscanf(saved, "%d", &mario->immortality_timer);
	XOR ^= mario->immortality_timer;
	fscanf(saved, "%d", &mario->projectileTimer);
	XOR ^= mario->projectileTimer;
	fscanf(saved, "%d", &mario->animation_Stage);
	XOR ^= mario->animation_Stage;
	fscanf(saved, "%d", &mario->facing);
	XOR ^= mario->facing;
	fscanf(saved, "%d", &mario->time);
	XOR ^= mario->time;
	fscanf(saved, "%d", &mario->jump_timer);
	XOR ^= mario->jump_timer;

	// red mario
	SDL_Surface *surface = IMG_Load("Slike/marioStandRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[0][0][0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/marioMoveRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[0][0][1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/marioJumpRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[0][0][2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/marioStandLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[0][1][0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/marioMoveLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[0][1][1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/marioJumpLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[0][1][2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// green mario
	surface = IMG_Load("Slike/gmarioStandRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[1][0][0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/gmarioMoveRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[1][0][1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/gmarioJumpRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[1][0][2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/gmarioStandLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[1][1][0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/gmarioMoveLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[1][1][1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/gmarioJumpLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[1][1][2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// black mario

	surface = IMG_Load("Slike/bmarioStandRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[2][0][0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/bmarioMoveRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[2][0][1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/bmarioJumpRight.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[2][0][2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/bmarioStandLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[2][1][0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/bmarioMoveLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[2][1][1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("Slike/bmarioJumpLeft.png");
	if (surface == NULL)
	{
		printf("%s\n", SDL_GetError());
		exit(1);
	}
	mario->animation[2][1][2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	extern sound, marioCharacter, selectedBackground, backFromBlack;
	fscanf(saved, "%d ", &sound);
	XOR ^= sound;
	fscanf(saved, "%d ", &marioCharacter);
	XOR ^= marioCharacter;
	fscanf(saved, "%d ", &selectedBackground);
	XOR ^= selectedBackground;
	fscanf(saved, "%d ", &backFromBlack);
	XOR ^= backFromBlack;

	//ovo mora jer sam stavio da pise i brojac
	fscanf(saved, "%d", &XOR_IN);
	fscanf(saved, "%d", &XOR_IN);

	fclose(saved);
	return mario;
}

void saveGame(Mario *mario, Map *map, char *Name2) {
	int i, j, n, XOR = 0,counter=0;
	FILE *saved = fopen(Name2, "w");
	//MAP save
	fprintf(saved, "%d\n", AI_NUMBER);
	counter++;
	XOR ^= AI_NUMBER;
	for (i = 0; i < AI_NUMBER; i++) {
		if (i == ground || i == basic || i == question || i == hidden || i == pipe || i == pikes || i == turtle || i == devil || i == plantie || i==flag || i== shroom) {
			n = map->ai_counter[i];
			fprintf(saved, "%d\n", n);
			counter++;
		}
		else
			n = 0;
		XOR ^= n;
		for (j = 0; j < n; j++) {
			if (i == ground) {
				Ground *temp = map->ai_Matrix[ground][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				counter += 4;
				fprintf(saved, "\n");
			}
			if (i == basic) {
				ai_Shroom *temp = map->ai_Matrix[basic][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				fprintf(saved, "%d ", temp->newCordinate.y);
				XOR ^= temp->newCordinate.y;
				counter += 5;
				fprintf(saved, "\n");
			}
			
			if (i == question) {
				ai_Question *temp = map->ai_Matrix[question][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				fprintf(saved, "%d ", temp->storage);
				XOR ^= temp->storage;
				fprintf(saved, "%d ", temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				counter += 6;
				fprintf(saved, "\n");

			}
			if (i == hidden) {
				ai_Hidden *temp = map->ai_Matrix[hidden][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				fprintf(saved, "%d ", temp->coins_Left);
				XOR ^= temp->coins_Left;
				fprintf(saved, "%d ", temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				counter += 6;
				fprintf(saved, "\n");

			}
			if (i == pipe) {
				Ground *temp = map->ai_Matrix[pipe][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				j++;
				counter += 4;
				Ground *temp2 = map->ai_Matrix[pipe][j];
				fprintf(saved, "%d ", temp2->coordinate.x);
				XOR ^= temp2->coordinate.x;
				fprintf(saved, "%d ", temp2->coordinate.y);
				XOR ^= temp2->coordinate.y;
				fprintf(saved, "%d ", temp2->dimension.x);
				XOR ^= temp2->dimension.x;
				fprintf(saved, "%d ", temp2->dimension.y);
				XOR ^= temp2->dimension.y;
				fprintf(saved, "\n");
				counter += 4;
			}
			if (i == pikes) {
				ai_Hidden *temp = map->ai_Matrix[pikes][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				fprintf(saved, "%d ", temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				counter += 5;
				fprintf(saved, "\n");
			}
			if (i == turtle) {
				ai_Devil *temp = map->ai_Matrix[turtle][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				fprintf(saved, "%d ", temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fprintf(saved, "%d ", temp->isAlive);
				XOR ^= temp->isAlive;
				fprintf(saved, "%d ", temp->type);
				XOR ^= temp->type;
				fprintf(saved, "%d ", temp->speed.x);
				XOR ^= temp->speed.x;
				fprintf(saved, "%d ", temp->speed.y);
				XOR ^= temp->speed.y;
				fprintf(saved, "%d ", temp->time);
				XOR ^= temp->time;
				counter += 10;
				fprintf(saved, "\n");

			}
			if (i == devil) {
				ai_Devil *temp = map->ai_Matrix[devil][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				fprintf(saved, "%d ", temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fprintf(saved, "%d ", temp->isAlive);
				XOR ^= temp->isAlive;
				fprintf(saved, "%d ", temp->type);
				XOR ^= temp->type;
				fprintf(saved, "%d ", temp->speed.x);
				XOR ^= temp->speed.x;
				fprintf(saved, "%d ", temp->speed.y);
				XOR ^= temp->speed.y;
				fprintf(saved, "%d ", temp->time);
				XOR ^= temp->time;
				counter += 10;
				fprintf(saved, "\n");

			}
			if (i == plantie) {
				ai_Plantie *temp = map->ai_Matrix[plantie][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;

				fprintf(saved, "%d ", temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fprintf(saved, "%d ", temp->isAlive);
				XOR ^= temp->isAlive;
				fprintf(saved, "%d ", temp->speed.x);
				XOR ^= temp->speed.x;
				fprintf(saved, "%d ", temp->speed.y);
				XOR ^= temp->speed.y;
				fprintf(saved, "%d ", temp->timer_Sleep);
				XOR ^= temp->timer_Sleep;
				fprintf(saved, "%d ", temp->additional_Height);
				XOR ^= temp->additional_Height;
				fprintf(saved, "%d ", temp->time);
				XOR ^= temp->time;

				counter += 11;
				fprintf(saved, "\n");

			}
			if (i == flag) {
				Ground *temp = map->ai_Matrix[flag][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				counter += 4;
				fprintf(saved, "\n");
			}
			if (i == shroom) {
				ai_Shroom *temp= map->ai_Matrix[shroom][j];
				fprintf(saved, "%d ", temp->coordinate.x);
				XOR ^= temp->coordinate.x;
				fprintf(saved, "%d ", temp->coordinate.y);
				XOR ^= temp->coordinate.y;
				fprintf(saved, "%d ", temp->dimension.x);
				XOR ^= temp->dimension.x;
				fprintf(saved, "%d ", temp->dimension.y);
				XOR ^= temp->dimension.y;
				fprintf(saved, "%d ", temp->animation_Stage);
				XOR ^= temp->animation_Stage;
				fprintf(saved, "%d ", temp->isAlive);
				XOR ^= temp->isAlive;
				fprintf(saved, "%d ", temp->type);
				XOR ^= temp->type;
				fprintf(saved, "%d ", temp->speed.x);
				XOR ^= temp->speed.x;
				fprintf(saved, "%d ", temp->speed.y);
				XOR ^= temp->speed.y;
				counter += 9;
				fprintf(saved, "\n");
			}
		}
	}
	fprintf(saved, "%d\n", map->x_score);
	XOR = XOR ^ map->x_score;
	fprintf(saved, "%d\n", map->score);
	XOR = XOR ^ map->score;
	fprintf(saved, "%d\n", map->x_passed);
	XOR = XOR ^ map->x_passed;
	fprintf(saved, "%d\n", map->timer);
	XOR = XOR ^ map->timer;
	counter += 4;

	//Mario save
	fprintf(saved, "%d\n", mario->coordinates.x);
	XOR ^= mario->coordinates.x;
	fprintf(saved, "%d\n", mario->coordinates.y);
	XOR ^= mario->coordinates.y;
	fprintf(saved, "%d\n", mario->size.x);
	XOR ^= mario->size.x;
	fprintf(saved, "%d\n", mario->size.y);
	XOR ^= mario->size.y;
	fprintf(saved, "%d\n", mario->speed.x);
	XOR ^= mario->speed.x;
	fprintf(saved, "%d\n", mario->speed.y);
	XOR ^= mario->speed.y;
	fprintf(saved, "%d\n", mario->dimension.x);
	XOR ^= mario->dimension.x;
	fprintf(saved, "%d\n", mario->dimension.y);
	XOR ^= mario->dimension.y;
	counter += 8;

	fprintf(saved, "%d\n", mario->direction);
	XOR ^= mario->direction;
	fprintf(saved, "%d\n", mario->lives);
	XOR ^= mario->lives;
	fprintf(saved, "%d\n", mario->immortality_timer);
	XOR ^= mario->immortality_timer;
	fprintf(saved, "%d\n", mario->projectileTimer);
	XOR ^= mario->projectileTimer;
	fprintf(saved, "%d\n", mario->animation_Stage);
	XOR ^= mario->animation_Stage;
	fprintf(saved, "%d\n", mario->facing);
	XOR ^= mario->facing;
	fprintf(saved, "%d\n", mario->time);
	XOR ^= mario->time;
	fprintf(saved, "%d\n", mario->jump_timer);
	XOR ^= mario->jump_timer;
	counter += 8;
	extern sound,marioCharacter,selectedBackground,backFromBlack;
	fprintf(saved, "%d ", sound);
	XOR ^= sound;
	fprintf(saved, "%d ", marioCharacter);
	XOR ^= marioCharacter;
	fprintf(saved, "%d ", selectedBackground);
	XOR ^= selectedBackground;
	fprintf(saved, "%d ", backFromBlack);
	XOR ^= backFromBlack;
	counter += 4;

	fprintf(saved, "%d ", counter);
	XOR ^= counter;
	fprintf(saved, "%d ", XOR);
	fclose(saved);
}


/*!	
*	\brief Dimensions of one block in world
*/
Pair_xy blok;

/*!	
*	\brief Function that detects collision in next frame
*	\param dim1 Dimension of the first object
*	\param coord1 Coordinates of the first object
*	\param dim2 Dimension of the second object
*	\param coord2 Coordinates of the second object
*	\param speed1 Speed vector of the first object
*	\param speed2 Speed vector of the second object
*	\return In respect to the first object returns 2 for bottom collision, 1 for top collision, 3 for right collision, 4 for left collision and 0 for no collision
*/
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

		if (relSpeed.y < 0 && tiles_bottom <= coord1.y && coord1.y + relSpeed.y <= tiles_bottom && dx < (dim1.x + dim2.x + EPSILON))
			//top
			return 1;
		if (relSpeed.x >= 0 && player_right <= coord2.x && player_right + relSpeed.x >= coord2.x && dy < (dim1.y + dim2.y))
			//right 
			return 3;
		if (relSpeed.x <= 0 && coord1.x >= tiles_right && coord1.x + relSpeed.x <= tiles_right && dy < (dim1.y + dim2.y))
			//left 
			return 4;
		if (dx <= (dim1.x + dim2.x + EPSILON) && dy <= (dim1.y + dim2.y) - EPSILON)
			return 2;
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

/*!
*	\brief Function that detects overlapping between objects
*	\param dim1 Dimension of the first object
*	\param coord1 Coordinates of the first object
*	\param dim2 Dimension of the second object
*	\param coord2 Coordinates of the second object
*	\param speed1 Speed vector of the first object
*	\param speed2 Speed vector of the second object
*	\return Returns 1 if there is collision, otherwise returns 0
*/
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

/*!
*	\brief Function that draws blocks on screen
*	\param window Address of current active SDL_Window
*	\param renderer Address of main SDL_Renderer
*	\param map Address of map structure on which the game is played
*	\param mario Address of active Mario struct
*	\param blockTextures SDL_Textures for all AIs
*/
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
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x+ map->x_passed;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				if (g->animation_Stage == 0)//nije skroz ispraznjen
					SDL_RenderCopy(renderer, g->animation[g->animation_Stage], NULL, &rect);
				else if(g->animation_Stage==1)
					SDL_RenderCopy(renderer, g->animation[g->animation_Stage], NULL, &rect);
				//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					//SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
				
				//SDL_RenderFillRect(renderer, &rect);
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
			case pikes: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x + map->x_passed;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				SDL_RenderCopy(renderer, g->animation[g->animation_Stage], NULL, &rect);
				/*SDL_SetRenderDrawColor(renderer, 250, 200, 200, 255);
				SDL_RenderFillRect(renderer, &rect);*/
				break;
			}
			case flag: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				rect.x = g->coordinate.x + map->x_passed;
				rect.y = g->coordinate.y;
				rect.w = g->dimension.x;
				rect.h = g->dimension.y;
				SDL_RenderCopy(renderer, g->animation, NULL, &rect);
				/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);*/
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
extern int backFromBlack;

/*!
*	\brief Function that draws blocks on screen
*	\param window Address of current active SDL_Window
*	\param renderer Address of main SDL_Renderer
*	\param map Address of map structure on which the game is played
*	\param mario Address of active Mario struct
*	\param new Code for new game <---------------------------
*	\param demo if == 1 it will play demo game, otherwise it will play normal game
*	\return returns 0
*/
int Game(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario, int New, int demo,char *Name2) {
	//FILE *demo_Command = fopen("demo.txt", "w");
	int demo_counter = 0;
	int victory = 0;
	int loaded = 0;
	blok.x = SCREEN_WIDTH / MAP_WIDTH;
	blok.y = SCREEN_HEIGHT / MAP_HEIGHT;

	SDL_Texture *block_Texture[AI_NUMBER][5]; // 5 animacija ili manje (zavisi od AI-a)

	Map *mapa;
	Mario *probni_mario=malloc(sizeof(Mario));

	Pair_xy update = { 0,0 };
	/*map->x_passed = blok.x;
	map->score = 0;*/
	immortality_cheat = 0;
	fly_cheat = 0;
	int deathAnimation = 1;

	// mario animations - nazalost moralo je sve rucno...
	if (New==0 || New==1) {
		{

				probni_mario->size.x = blok.x * (MARIO_SHRINK_X) / 100;
				probni_mario->size.y = 2 * blok.y * MARIO_SHRINK / 100;
				probni_mario->dimension.x = blok.x;//dimension samo sluzi za iscrtavanje
				probni_mario->dimension.y = 2 * blok.y * MARIO_SHRINK / 100;
				probni_mario->coordinates.x = SCREEN_WIDTH / 2 + 2 * blok.x + blok.x * (100 - MARIO_SHRINK_X) / 200;
				probni_mario->coordinates.y = 3 * blok.y + (100 - MARIO_SHRINK) * blok.y / 100;
				probni_mario->speed.x = 0;
				probni_mario->speed.y = 0;
				probni_mario->lives = 2;
				probni_mario->jump_timer = 0;
				probni_mario->immortality_timer = 0;
				probni_mario->projectileTimer = 0;
				probni_mario->jump_sound = 0;
			
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

		// black mario

		surface = IMG_Load("Slike/bmarioStandRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[2][0][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/bmarioMoveRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[2][0][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/bmarioJumpRight.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[2][0][2] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/bmarioStandLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[2][1][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/bmarioMoveLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[2][1][1] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("Slike/bmarioJumpLeft.png");
		if (surface == NULL)
		{
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		probni_mario->animation[2][1][2] = SDL_CreateTextureFromSurface(renderer, surface);
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

		// hidden block - same as basic[0] and question[1]

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

		//  pike
		surface = IMG_Load("Slike/pike.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[pikes][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// projectile 
		surface = IMG_Load("Slike/fire.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[projectile][0] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// flag
		surface = IMG_Load("Slike/flag.png");
		if (surface == NULL) {
			printf("%s\n", SDL_GetError());
			exit(1);
		}
		block_Texture[flag][0] = SDL_CreateTextureFromSurface(renderer, surface);
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
}
	//postoji funkcija koja inicijalizuje mapu
mapa = NULL;
if (New == 0 && isFileOK(Name2) == 1) {
	mapa = loadMap(probni_mario, mapa, Name2, block_Texture, renderer);
	probni_mario = loadMario(probni_mario, mapa, Name2, block_Texture, renderer);

}
else
mapa = initMap(block_Texture, demo);
	
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
				exit(0);
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
					saveGame(probni_mario, mapa, Name2);
					Running = 0;
					deathAnimation = 0;
					break;
					//return  0; zbog ovog je curila memorija??		
				case SDLK_p: { 
					pause_game();
					break;
				}
				
				case SDLK_SPACE: {
					if (probni_mario->lives > 2 && !demo) {
						Pair_xy coord;
						coord.x = probni_mario->coordinates.x + (!probni_mario->direction ? 0 : probni_mario->size.x);
						coord.y = probni_mario->coordinates.y + probni_mario->size.y / 2;
						if (probni_mario->projectileTimer == 0) {
							playFireball();
							spawnProjectile(mapa, coord, !probni_mario->direction, probni_mario->speed.x, block_Texture);
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
		if(!demo)
		if (state[SDL_SCANCODE_UP]) {
			update.y = 1;
			probni_mario->jump_sound = 1;
		}
		else {
			update.y = 2;
			probni_mario->jump_sound = 0;
		}
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
		updateAI(mapa, probni_mario);
		//fprintf(demo_Command, "{%d, %d}, ", update.x, update.y);
		if (demo) {
			update = demo_Comand[demo_counter];
			if (demo_counter < sizeof(demo_Comand) / sizeof(demo_Comand[0]))
				demo_counter++;
			else update.x = 2;
		}
		int update_mario_succes = updateMario(window,renderer,mapa,probni_mario,update,block_Texture);
		drawAI(window, renderer, mapa);
		SDL_RenderPresent(renderer);
		if (update_mario_succes) {
			deathAnimation = 0;
			victory = 1;
			break;
		}

	}
	/*if (Running == 1)
		saveMap(probni_mario, map);*/

	//fclose(demo_Command);


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

		int speed = 1;
		while (rect.y != SCREEN_HEIGHT) {
			rect.y += speed;

			drawScreen(window, renderer, mapa, probni_mario, block_Texture);
			drawAI(window, renderer, mapa);
			SDL_RenderCopy(renderer, death, NULL, &rect);

			SDL_RenderPresent(renderer);
		}
		SDL_DestroyTexture(death);
	}
	else if(victory == 1) {//victory
		SDL_Rect rect = { probni_mario->coordinates.x + mapa->x_passed + blok.x * FLAG_SHRINK / 200,probni_mario->coordinates.y,probni_mario->size.x,probni_mario->size.y };
		SDL_Surface *sur = NULL;
		if (marioCharacter == 0) sur = IMG_Load("Slike/marioDeathRed.png");
		else if(marioCharacter==1) sur = IMG_Load("Slike/marioDeathGreen.png");
		else sur = IMG_Load("Slike/marioDeathBlack.png");
		SDL_Texture *death = SDL_CreateTextureFromSurface(renderer, sur);
		SDL_FreeSurface(sur);
		playFlagPole();
		int gravity_Check = 0;
		while (!gravity_Check) {
			gravity_Check = detectGravityCollide(mapa, probni_mario);
			if (gravity_Check > 0) {
				//gravity_Check = gravity_Check2;
				probni_mario->jump_timer = 0;
				if (probni_mario->speed.y > 0) {
					probni_mario->speed.y = 0;
					probni_mario->coordinates.y = gravity_Check - probni_mario->size.y;
				}

			}
			else
				probni_mario->speed.y += G;
			probni_mario->coordinates.y += probni_mario->speed.y;
			drawScreen(window, renderer, mapa, probni_mario, block_Texture);
			drawAI(window, renderer, mapa);

			rect.y = probni_mario->coordinates.y;
			SDL_RenderCopy(renderer, death, NULL, &rect);

			SDL_RenderPresent(renderer);
		}
		if (!demo) {
			char name[MAX_NAME] = { 0 };
			int a = 1;
			initFinalScoreTextures(renderer);
			playEndGame();
			finalScoreScreen(mapa->score + mapa->x_score / 10, name, &a, renderer);
			SDL_DestroyTexture(death);
			extern FinalScoreTextures finalScoreTextureManager;
			destroyFinalScoreTextures(finalScoreTextureManager);
			// update highscore.txt
			updateHighscore(mapa->score + mapa->x_score / 10, name, a);
		}
	}

	// free memory 

	// free mario textures
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 3; k++)
				SDL_DestroyTexture(probni_mario->animation[i][j][k]);
	// free ai and block textures
	for (int i = 0; i < AI_NUMBER; i++) {
		if (i == devil) {
			for (int j = 0; j < 3; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
		else if (i == turtle) {
			for (int j = 0; j < 5; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
		else if (i == plantie) {
			for (int j = 0; j < 2; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
		else if (i == shroom) {
			for (int j = 0; j < 3; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
		else if (i == basic) {
			SDL_DestroyTexture(block_Texture[i][0]);
		}
		else if (i == ground) {
			SDL_DestroyTexture(block_Texture[i][0]);
		}
		else if (i == question) {
			for (int j = 0; j < 2; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
		else if (i == pipe) {
			for (int j = 0; j < 2; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
		else if (i == pikes) {
			SDL_DestroyTexture(block_Texture[i][0]);
		}
		else if (i == projectile) {
			SDL_DestroyTexture(block_Texture[i][0]);
		}
		else if (i == flag) {
			SDL_DestroyTexture(block_Texture[i][0]);
		}
		else if (i == sky) {
			for (int j = 0; j < 2; j++) SDL_DestroyTexture(block_Texture[i][j]);
		}
	}
	//SDL_DestroyTexture(block_Texture[sky][0]);
	//SDL_DestroyTexture(block_Texture[sky][1]);
	//SDL_DestroyTexture(block_Texture[ground][0]);
	//SDL_DestroyTexture(block_Texture[basic][0]); // ovo ubaciti gore u for kad se naprave svi blokovi i ai-ovi
	//SDL_DestroyTexture(block_Texture[question][0]);
	/*SDL_DestroyTexture(block_Texture[shroom][0]);
	SDL_DestroyTexture(block_Texture[shroom][1]);
	SDL_DestroyTexture(block_Texture[shroom][2]);*/
	/*SDL_DestroyTexture(block_Texture[pipe][0]);
	SDL_DestroyTexture(block_Texture[pipe][1]);*/
	//SDL_DestroyTexture(block_Texture[pikes][0]);
	/*SDL_DestroyTexture(block_Texture[flag][0]);
	SDL_DestroyTexture(block_Texture[projectile][0]);*/


	// free ai
	/*
	for (int i = 0; i < AI_NUMBER; i++) {
		if (i == ground) {
			for (int j = 0; j < mapa->ai_counter[ground]; j++) free(mapa->ai_Matrix[ground][j]); 
		}
		if (i == basic) {
			for (int j = 0; j < mapa->ai_counter[basic]; j++) free(mapa->ai_Matrix[basic][j]);
		}
		if (i == devil) {
			for (int j = 0; j < mapa->ai_counter[devil]; j++) free(mapa->ai_Matrix[devil][j]);
		}
		if (i == turtle) {
			for (int j = 0; j < mapa->ai_counter[turtle]; j++) free(mapa->ai_Matrix[turtle][j]);
		}
		if (i == pipe) {
			for (int j = 0; j < mapa->ai_counter[pipe]; j++) free(mapa->ai_Matrix[pipe][j]);
		}
		if (i == plantie) {
			for (int j = 0; j < mapa->ai_counter[plantie]; j++) free(mapa->ai_Matrix[plantie][j]);
		}
		if (i == question) {
			for (int j = 0; j < mapa->ai_counter[question]; j++) free(mapa->ai_Matrix[question][j]);
		}
		if (i == hidden) {
			for (int j = 0; j < mapa->ai_counter[hidden]; j++) free(mapa->ai_Matrix[hidden][j]);
		}
		if (i == pikes) {
			for (int j = 0; j < mapa->ai_counter[pikes]; j++) free(mapa->ai_Matrix[pikes][j]);
		}
		if (i == flag) {
			for (int j = 0; j < mapa->ai_counter[flag]; j++) free(mapa->ai_Matrix[flag][j]);
		}
	}*/
	
	// free mario
	free(probni_mario);
	//SDL_DestroyTexture(object_Ground);
	// treba AI free da se doda !!!
	// mapa - pomocna mapa , treba da se zameni u free(map)
	// free map
	marioCharacter = 0;
	selectedBackground = 0;
	backFromBlack = 0;
	destroyMap(mapa);
	return 0;
}