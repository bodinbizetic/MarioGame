#ifndef ai_h
#define ai_h

/*!	\file ai.h
*	\brief Contains declarations and constants for AIs
*/

#include "SDL.h"
#include "map.h"
#include "mario.h"
#include "all.h"

/*!	
*	\brief Speed of the devil AI
*/
#define DEVIL_SPEED -2

/*!
*	\brief Speed of the turtle AI
*/
#define TURTLE_SPEED 2


/*!
*	\brief Score base for enemy kill
*/
#define ENEMY_KILL 100

/*!
*	\brief Score base for question pop
*/
#define QUESTION_POP 500

/*!
*	\brief Score base for brick kill
*/
#define BLOCK_KILL 100

/*!
*	\brief Turtle shell acceleration
*/
#define TURTLE_ACCELERATION 1
#define TURTLE_TIMER 20

/*!
*	\brief Speed of plantie AI
*/
#define PLANTIE_SPEED 2

/*!
*	\brief Maximum duration of plantie AI sleep timer 
*/
#define PLANTIE_SLEEP 100

#define PLANTIE_EPSILON -10

/*!
*	\brief Speed of shroom ai
*/
#define SHROOM_SPEED 6
/*!
*	\brief Score base for shroom pick-up
*/
#define SHROOM_SCORE 1000

/*!
*	\brief Speed of Mario's projectile
*/
#define PROJECTILE_SPEED 8

/*!
*	\brief Number of bounces for Mario's projectile before dissapearing
*/
#define PROJECTILE_BOUNCE 3

/*!
*	\brief Size of Mario's projectile in % relative to a block 
*/
#define PROJECTILE_SIZE 20

/*!
*	\brief Score base for hitting a hidden 
*/
#define HIDDEN_SCORE 200

/*!
*	\brief Size of pike in % relative to a block 
*/
#define PIKE_SHRINK 25

/*!
*	\brief Size of flag in % relative to a block
*/
#define FLAG_SHRINK 50

/*!
*	\brief Number of blocks flag goes up to
*/
#define FLAG_HEIGHT 12

int drawAI(SDL_Window *window, SDL_Renderer *renderer, Map *map);

int updateAI(Map *map, Mario *mario);
#endif
