#ifndef map_h
#define map_h
#include "SDL.h"
#include "all.h"
/*!	\file map.h
*	\brief Contains declarations and constants for map
*/


//Izrazeno u % po bloku
#define PIPE_WIDTH 80
#define PIPE_HEIGHT 20
#define PLANTIE_POS 50

//IZMENA!Zamenio sam floor sa ground jer je pravio problem sa fjom floor iz math.h,zamenio sam i u map.c
enum mapId { sky, ground, basic, question, hidden, pipetunnel, pipe, flag, castle, pikes, mario_id, projectile, shroom, star, turtle, devil, plantie };
//Gravity defying blocks
static int gravity_Blocks[] = { ground, question, hidden, basic, pipe, pikes };
static int ai_id[] = { projectile, shroom, star, turtle, devil, plantie };
//enum aiId {Brick, Question, Hidden, Projectile, Shroom, Star, Turtle, Devil, Plantie};



Map* initMap(SDL_Texture *block_Texture[AI_NUMBER][5]);
//Citanje sacuvane mape
Map* LoadMap();

int updateMapItems(Map *map);
void  destroyMap(Map *map);
int spawnShroom(Map *map, Pair_xy coord, SDL_Texture *block_Texture[AI_NUMBER][5], int lifes);
int spawnProjectile(Map *map, Pair_xy coord, int orientation, int speed);
int spawnCoin(Map *map, Pair_xy coord, SDL_Texture *block_Texture[AI_NUMBER][5]);




#endif

