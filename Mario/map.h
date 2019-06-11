#ifndef map_h
#define map_h
#include "SDL.h"
#include "all.h"
/*!	\file map.h
*	\brief Contains declarations and constants for map
*/


//Izrazeno u % po bloku

/*!	
*	\brief Relative x dimension for pipe in %
*/
#define PIPE_WIDTH 80

/*!
*	\brief Relative y dimension for pipe in %
*/
#define PIPE_HEIGHT 20

/*!
*	\brief Relative position of plantie in %
*/
#define PLANTIE_POS 50

/*!
*	\brief Enum of all types of blocks and AIs
*/
enum mapId { sky, ground, basic, question, hidden, pipetunnel, pipe, flag, castle, pikes, mario_id, projectile, shroom, star, turtle, devil, plantie };

/*!
*	\brief Enum of all gravity-collidable objects
*/
static int gravity_Blocks[] = { ground, question, hidden, basic, pipe, pikes, flag };

/*!
*	\brief Enum of all AIs
*/
static int ai_id[] = { projectile, shroom, star, turtle, devil, plantie, flag };
//enum aiId {Brick, Question, Hidden, Projectile, Shroom, Star, Turtle, Devil, Plantie};



Map* initMap(SDL_Texture *block_Texture[AI_NUMBER][5], int demo);
//Citanje sacuvane mape
Map* LoadMap();

int updateMapItems(Map *map);

void  destroyMap(Map *map);

int spawnShroom(Map *map, Pair_xy coord, SDL_Texture *block_Texture[AI_NUMBER][5], int lifes);

int spawnProjectile(Map *map, Pair_xy coord, int orientation, int speed, SDL_Texture *block_Texture[AI_NUMBER][5]);

int spawnCoin(Map *map, Pair_xy coord, SDL_Texture *block_Texture[AI_NUMBER][5]);

int spawnDeathDevil(Map *map, Pair_xy coord, SDL_Texture *animation);

#endif

