#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "ai.h"
#include "main_menu.h"
#include "game.h"
#include "map_Segments.h"
/*!
*		\brief Initializes Map structure, fills it with "sky" and adds one leyer of floor
*/

Map* initMap() {
	Map *map = malloc(sizeof(Map));
	if (!map)
		printf_s("Failed to Initialize Map");
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH * MAP_SEGMENTS_NUMBER; j++)
			map->map_Matrix[i][j] = (i == MAP_HEIGHT - 1) ? ground : sky;
	for (int i = 0; i < AI_NUMBER; i++) map->ai_counter[i] = 0;
	srand(time(0));
	generate_Map(map);
	for(int i=0; i< MAP_HEIGHT; i++)
		for (int j = 0; j <= MAP_WIDTH; j++) {
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
				map->ai_Matrix[devil][map->ai_counter[devil]++] = temp;
			}
		}

	
	/*for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++)
			printf_s("%d ", map_Segment[0][i][j]);
		putchar('\n');
	}*/
	map->score = 0;
	return map;
}
Map* LoadMap() {
	;
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
	for (int i = 0; i < MAP_SEGMENTS_NUMBER; i++) {
		int rand_num = rand();
		rand_num = rand_num % MAP_SEGMENTS_PREDEFINED_NUMBER;
		copy_Map(map, MAP_WIDTH * i, rand_num);
	}
}

/*!
*		\brief Deletes Map structure
*		\param Map map Addres of map
*/
void  destroyMap(Map *map) {
	free(map);
}