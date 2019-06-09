#ifndef ai_h
#define ai_h

/*!	\file ai.h
*	\brief Contains declarations and constants for AIs
*/
#include "SDL.h"
#include "map.h"
#include "mario.h"
#include "all.h"
#define DEVIL_SPEED -2
#define TURTLE_SPEED 2

#define ENEMY_KILL 100//score za enemija
#define QUESTION_POP 500
#define BLOCK_KILL 100

#define TURTLE_ACCELERATION 1
#define TURTLE_TIMER 20

#define PLANTIE_SPEED 2
#define PLANTIE_SLEEP 100
#define PLANTIE_EPSILON -10

#define SHROOM_SPEED 6
#define SHROOM_SCORE 1000

#define PROJECTILE_SPEED 8
#define PROJECTILE_BOUNCE 3
#define PROJECTILE_SIZE 20

#define HIDDEN_SCORE 200

#define PIKE_SHRINK 25

#define FLAG_SHRINK 50
#define FLAG_HEIGHT 12

int drawAI(SDL_Window *window, SDL_Renderer *renderer, Map *map);

int updateAI(Map *map, Mario *mario);
#endif
