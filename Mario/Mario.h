#ifndef mario_h
#define mario_h
#include "ai.h"
#include "map.h"
#include "all.h"

/*!	\file mario.h
*	\brief Contains game playing declarations and Mario-related constants
*/

/*!	
*	\brief Maximum value for Mario jump timer
*/
#define MAX_JUMP 25

/*!
*	\brief Maximum value for Mario immoratility timer
*/
#define MAX_IMORTAL 150

/*!
*	\brief Maximum value for Mario x speed
*/
#define MAXSPEED 8

/*!
*	\brief Maximum value for Mario's projectile timer
*/
#define PROJECTILE_TIMER 25
/*!
*	\brief Reduction in % for Mario's y size
*/
#define MARIO_SHRINK 80

/*!
*	\brief Reduction in % for Mario's x size
*/
#define MARIO_SHRINK_X 80

/*!
*	\brief Value of gravitational acceleration
*/
#define G 1

int updateMario(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario,Pair_xy update, SDL_Texture *block_Texture[AI_NUMBER][5]);
#endif
