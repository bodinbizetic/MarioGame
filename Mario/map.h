#ifndef map_h
#define map_h

/*!	\file map.h
*	\brief Contains declarations and constants for map
*/

#define MAP_HEIGHT 15
#define MAP_WIDTH 15
#define MAP_SEGMENTS_NUMBER 10

#define AI_NUMBER 9
#define AI_MAX_NUMBER 10
//Ako je malo slovo - podrazumeva mapId, a veliko aiId
enum mapId { sky, floor, basic, question, hidden, pipetunnel, pipe, flag, castle, pikes, mario, projectile, shroom, star, turtle, devil, plantie };

enum aiId {Brick, Question, Hidden, Projectile, Shroom, Star, Turtle, Devil, Plantie};

/*!
*		\brief Main structure that cantains all active AI's and all blocks on the map
*/
typedef struct MAP {
	void *ai_Matrix[AI_NUMBER][AI_MAX_NUMBER];
	int map_Matrix[MAP_HEIGHT][MAP_WIDTH * MAP_SEGMENTS_NUMBER];
}Map;

Map* initMap();

void  destroyMap(Map *map);

#endif

