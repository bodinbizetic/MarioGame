#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "ai.h"
#include "main_menu.h"
#include "game.h"
#include "map_Segments.h"
#include "camera.h"
/*!
*		\brief Initializes Map structure, fills it with "sky" and adds one leyer of floor
*/

Map* initMap(SDL_Texture *block_Texture[AI_NUMBER][5], int demo) {
	Map *map = malloc(sizeof(Map));
	if (!map)
		printf_s("Failed to Initialize Map");

	map->x_passed = 0;
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH * MAP_SEGMENTS_NUMBER; j++)
			map->map_Matrix[i][j] = (i == MAP_HEIGHT - 1) ? ground : sky;
	for (int i = 0; i < AI_NUMBER; i++) map->ai_counter[i] = 0;

	srand(time(0));
	if(demo){
		generate_Demo_Map(map);
	}
	else generate_Map(map);
	for(int i=0; i< MAP_HEIGHT; i++)
		for (int j = 0; j <= MAP_WIDTH * MAP_SEGMENTS_NUMBER; j++) {
			if (map->map_Matrix[i][j] == ground) {
				Ground *temp = malloc(sizeof(Ground));
				temp->coordinate.x = j*blok.x;
				temp->coordinate.y = i*blok.y;
				temp->dimension = blok;
				map->ai_Matrix[ground][map->ai_counter[ground]++] = temp;
			}
			else if (map->map_Matrix[i][j] == basic) {
				ai_Shroom *temp = malloc(sizeof(ai_Shroom));
				temp->coordinate.x = j * blok.x;
				temp->coordinate.y = i * blok.y;
				temp->dimension = blok;
				temp->newCordinate.y = temp->coordinate.y;
				map->ai_Matrix[basic][map->ai_counter[basic]++] = temp;
			}
			else if (map->map_Matrix[i][j] == devil) {
				ai_Devil *temp = malloc(sizeof(ai_Devil));
				temp->coordinate.x = j * blok.x;
				temp->coordinate.y = i * blok.y;
				temp->dimension = blok;
				temp->animation_Stage = 0;
				temp->isAlive = 1;
				temp->type = 1;
				temp->speed.x = DEVIL_SPEED;
				temp->speed.y = 0;
				for (int k = 0; k < 3; k++)
					temp->animation[k] = block_Texture[devil][k];
				temp->time = 0;
				map->ai_Matrix[devil][map->ai_counter[devil]++] = temp;
			}
			else if (map->map_Matrix[i][j] == turtle) {
				ai_Devil *temp = malloc(sizeof(ai_Devil));
				temp->coordinate.x = j * blok.x;
				temp->coordinate.y = i * blok.y;
				temp->dimension = blok;
				temp->animation_Stage = 0;
				temp->isAlive = 1;
				temp->type = 1;
				temp->speed.x = TURTLE_SPEED;
				temp->speed.y = 0;
				for (int k = 0; k < 5; k++)
					temp->animation[k] = block_Texture[turtle][k];
				temp->time = 0;
				map->ai_Matrix[turtle][map->ai_counter[turtle]++] = temp;
			}
			else if (map->map_Matrix[i][j] == pipe) {
				//Pipe se sastoji iz dva dela: cevka i onaj poklopac
				Ground *temp = malloc(sizeof(Ground));
				temp->coordinate.x = j * (blok.x) + blok.x * PIPE_WIDTH / 400;
				temp->coordinate.y = (i-1) * blok.y;
				temp->dimension.x = 2 * blok.x * PIPE_WIDTH / 100;
				temp->dimension.y = 2 * blok.y;
				temp->animation = block_Texture[pipe][0];
				map->ai_Matrix[pipe][map->ai_counter[pipe]++] = temp;
				Ground *temp2 = malloc(sizeof(Ground));
				temp2->coordinate.x = j * blok.x;
				temp2->coordinate.y = (i - 1) * blok.y;
				temp2->dimension.x = 2 * blok.x;
				temp2->animation = block_Texture[pipe][1];
				temp2->dimension.y = 2 * blok.y * PIPE_HEIGHT / 100;
				map->ai_Matrix[pipe][map->ai_counter[pipe]++] = temp2;
			}
			else if (map->map_Matrix[i][j] == plantie) {
				ai_Plantie *temp = malloc(sizeof(ai_Plantie));
				temp->coordinate.x = j * blok.x + blok.x * PLANTIE_POS * 3/ 200;
				temp->coordinate.y = i * blok.y;
				temp->dimension.x = blok.x * PLANTIE_POS / 100;
				temp->dimension.y = blok.y * 2;
				temp->animation_Stage = 0;
				temp->isAlive = 1;
				temp->speed.y = -PLANTIE_SPEED;
				temp->speed.x = 0;
				temp->timer_Sleep = PLANTIE_SLEEP;
				temp->additional_Height = 0;
				temp->animation[0] = block_Texture[plantie][0];
				temp->animation[1] = block_Texture[plantie][1];
				temp->time = 0;
				map->ai_Matrix[plantie][map->ai_counter[plantie]++] = temp;
			}
			else if (map->map_Matrix[i][j] == question) {
				ai_Question *temp = malloc(sizeof(ai_Question));
				temp->coordinate.x = j * blok.x;
				temp->coordinate.y = i * blok.y;
				temp->dimension = blok;
				temp->storage = 1;
				temp->animation_Stage = 0;
				temp->animation[0] = block_Texture[question][0];
				temp->animation[1] = block_Texture[question][1];
				map->ai_Matrix[question][map->ai_counter[question]++] = temp;
			}
			else if (map->map_Matrix[i][j] == hidden) {
				ai_Hidden *temp = malloc(sizeof(ai_Hidden));
				temp->coordinate.x = j * blok.x;
				temp->coordinate.y = i * blok.y;
				temp->dimension = blok;
				temp->coins_Left = 10;
				temp->animation_Stage = 1;
				map->ai_Matrix[hidden][map->ai_counter[hidden]++] = temp;
			}
			else if (map->map_Matrix[i][j] == pikes) {
				ai_Hidden *temp = malloc(sizeof(ai_Hidden));
				temp->coordinate.x = j * blok.x;
				temp->coordinate.y = i * blok.y + (100 - PIKE_SHRINK ) * blok.y/ 100;
				temp->dimension.x = blok.x;
				temp->dimension.y = blok.y * PIKE_SHRINK / 100;
				
				map->ai_Matrix[pikes][map->ai_counter[pikes]++] = temp;
			}
			else if (map->map_Matrix[i][j] == flag) {
				Ground *temp = malloc(sizeof(Ground));
				temp->coordinate.x = j * blok.x ;
				temp->coordinate.y = (i - FLAG_HEIGHT + 1) * blok.y ;
				temp->dimension.x = blok.x * FLAG_SHRINK / 100;
				temp->dimension.y = blok.y * FLAG_HEIGHT;
				map->ai_Matrix[flag][map->ai_counter[flag]++] = temp;
			}
			map->map_Matrix[i][j] = sky;
		}

	
	/*for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++)
			printf_s("%d ", map_Segment[0][i][j]);
		putchar('\n');
	}*/
	map->score = 0;
	return map;
}

int spawnShroom(Map *map, Pair_xy coord, SDL_Texture *block_Texture[AI_NUMBER][5],int lifes) {
	ai_Shroom *temp = malloc(sizeof(ai_Shroom));
	temp->coordinate = coord;
	temp->coordinate.y += EPSILON;
	temp->dimension.y = blok.y - EPSILON;
	temp->dimension.x = blok.x * 2 / 3;
	// red or green shroom
	if (lifes == 1)
		temp->animation_Stage = 0;
	else 
		temp->animation_Stage = 1;
	temp->animation = block_Texture[shroom][temp->animation_Stage];
	temp->isAlive = 1;
	temp->type = 0;
	temp->speed.x = SHROOM_SPEED;
	temp->speed.y = 0;
	map->ai_Matrix[shroom][map->ai_counter[shroom]++] = temp;
	return 0;
}

int spawnProjectile(Map *map, Pair_xy coord, int orientation, int speed) {
	ai_Projectile *temp = malloc(sizeof(ai_Projectile));
	temp->coordinate = coord;
	temp->dimension.y = blok.y * PROJECTILE_SIZE / 100;
	temp->dimension.x = blok.x * PROJECTILE_SIZE / 100;
	temp->isAlive = 1;
	temp->speed.x = PROJECTILE_SPEED * (orientation ? -1 : 1) + speed;
	temp->speed.y = 0;
	temp->nubmer_Of_Bounces = PROJECTILE_BOUNCE;
	map->ai_Matrix[projectile][map->ai_counter[projectile]++] = temp;
	return 0;
}

int spawnCoin(Map *map, Pair_xy coord, SDL_Texture *block_Texture[AI_NUMBER][5])
{
	ai_Shroom *temp = malloc(sizeof(ai_Shroom));
	temp->coordinate = coord;
	temp->coordinate.y -= 20;
	temp->dimension.y = blok.y;
	temp->dimension.x = blok.x ;
	temp->animation = block_Texture[shroom][2];
	temp->isAlive = 1;

	map->ai_Matrix[shroom][map->ai_counter[shroom]++] = temp;
	return 0;
}


Map* LoadMap() {
	/*FILE *save = fopen("Savegame.bin", "rb");
	if (save == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		exit(EXIT_FAILURE);
	}
	// read map
	Map *mapa = malloc(sizeof(Map));
	if (mapa == NULL) {
		printf("Greska pri alociranju!\n");
		exit(EXIT_FAILURE);
	}
	fread(mapa, sizeof(Map), 1, save);
	fclose(save);
	return mapa;*/
}
/*!
*		\brief Function that copies map segment into map
*		\param Map map Addres of map that containts map_Matrix that is destination
*		\param int x Coordinate of top most left corner
*		\param int seg_id Id of source matrix in map_Segment matrix
*/
int copy_Map(Map *map, int x, int seg_id) {
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = x; j < x + MAP_WIDTH; j++)
			map->map_Matrix[i][j] = map_Segment[seg_id][i][j - x];
	return 0;
}

/*!
*		\brief Function that generetes whole
*		\param Map map Addres of map that containts map_Matrix that needs to be generated
*/
int generate_Map(Map *map) {
	int newSeg[MAP_SEGMENTS_PREDEFINED_NUMBER] = { 0 };
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map->map_Matrix[i][j] = map_Start_Segment[i][j];

	for (int i = 1; i < MAP_SEGMENTS_NUMBER - 1; i++) {
		int rand_num = rand();
		//while(rand_num = rand(), rand_num = rand_num % MAP_SEGMENTS_PREDEFINED_NUMBER, newSeg[rand_num]);
		rand_num = rand_num % MAP_SEGMENTS_PREDEFINED_NUMBER;
		//newSeg[rand_num] = 1;
		copy_Map(map, MAP_WIDTH * i, rand_num);
	}
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map->map_Matrix[i][j + (MAP_SEGMENTS_NUMBER - 1) * MAP_WIDTH] = map_Finish_Segment[i][j];

}

int generate_Demo_Map(Map *map) {
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map->map_Matrix[i][j] = map_Start_Segment[i][j];
	int demo_Map[DEMO_MAP_SEGMENTS_NUMBER] = { 0, 0, 1, 5, 0 };
	for (int i = 1; i < DEMO_MAP_SEGMENTS_NUMBER - 1; i++) {
		copy_Map(map, MAP_WIDTH * i, demo_Map[i]);
	}
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map->map_Matrix[i][j + (MAP_SEGMENTS_NUMBER - 1) * MAP_WIDTH] = map_Finish_Segment[i][j];
}

/*!
*		\brief Deletes Map structure
*		\param Map map Addres of map
*/
void  destroyMap(Map *map) {
	free(map);
}