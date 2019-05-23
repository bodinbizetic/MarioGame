#ifndef map_h
#define map_h

/*!	\file map.h
*	\brief Contains declarations and constants for map
*/

#define MAP_HEIGHT 15
#define MAP_WIDTH 15
#define MAP_SEGMENTS_NUMBER 10


#define AI_NUMBER 17
#define AI_MAX_NUMBER 50
//Ako je malo slovo - podrazumeva mapId, a veliko aiId
//IZMENA!Zamenio sam floor sa ground jer je pravio problem sa fjom floor iz math.h,zamenio sam i u map.c
enum mapId { sky, ground, basic, question, hidden, pipetunnel, pipe, flag, castle, pikes, mario_id, projectile, shroom, star, turtle, devil, plantie };
//Gravity defying blocks
static int gravity_Blocks[] = { ground, basic, question, hidden };
static int ai_id[] = { projectile, shroom, star, turtle, devil, plantie };
//enum aiId {Brick, Question, Hidden, Projectile, Shroom, Star, Turtle, Devil, Plantie};

/*!
*		\brief Main structure that cantains all active AI's and all blocks on the map
*/
typedef struct {
	void *ai_Matrix[AI_NUMBER][AI_MAX_NUMBER];
	int map_Matrix[MAP_HEIGHT][MAP_WIDTH * MAP_SEGMENTS_NUMBER];
	int ai_counter[AI_NUMBER];
	int score;
}Map;

Map* initMap();
//Citanje sacuvane mape
Map* LoadMap();

void  destroyMap(Map *map);




#endif

