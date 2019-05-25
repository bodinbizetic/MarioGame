#ifndef ai_h
#define ai_h

/*!	\file ai.h
*	\brief Contains declarations and constants for AIs
*/
#include "SDL.h"
#include "map.h"


#define DEVIL_SPEED -2
#define TURTLE_SPEED 2
#define ENEMY_KILL 100//score za enemija
#define BLOCK_KILL 100
#define TURTLE_ACCELERATION 1
#define TURTLE_TIMER 20

/*!
*	\brief Contains pair of 2d coordinates
*/
typedef struct PAIR_XY {
	int x;
	int y;
}Pair_xy;

/*!
*	\brief Structure representing Devil/Turtle AI
*/
typedef struct DEVIL {
	//Istovremeno Devil i Turtle
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int type;
	int animation_Stage;
}ai_Devil;

/*!
*	\brief Structure representing Plant AI
*/
typedef struct PLANTIE {
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int timer_Sleep;
	int animation_Stage;
}ai_Plantie;

/*!
*	\brief Structure representing Mario projectile
*/
typedef struct PROJECTILE {
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int nubmer_Of_Bounces;
}ai_Projectile;

/*!
*	\brief Structure representing Mushroom/Star/Coin/Brick 
*/
typedef struct SHROOM {
	//Istovremeno Shroom, Star, Coin, Brick
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int type;
	int animation_Stage;
}ai_Shroom;

/*!
*	\brief Structure representing Question block
*/
typedef struct QUESTION {
	Pair_xy coordinate, dimension;
	int storage; 
	int animation_Stage;
}ai_Question;

/*!
*	\brief Structure representing Hidden block
*/
typedef struct HIDDEN {
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int coins_Left;
	int animation_Stage;
}ai_Hidden;
/*!
*	\brief Structure representing non-interactable ground
*/
typedef struct STOCK_FLOOR {
	//ground, pipe
	Pair_xy coordinate, dimension;
}Ground;

int drawAI(SDL_Window *window, SDL_Renderer *renderer, Map *map);

int updateAI(Map *map);
#endif
