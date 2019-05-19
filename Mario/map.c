#include <stdio.h>
#include <stdlib.h>
#include "map.h"

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
	return map;
}
Map* LoadMap() {
	;
}

/*!
*		\brief Deletes Map structure
*		\param Map map Addres of map
*/
void  destroyMap(Map *map) {
	free(map);
}