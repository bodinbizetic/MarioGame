#ifndef all_h
#define all_h
#include "SDL.h"

/*!	\file all.h
*	\brief Contains declarations and constants for all structures
*/

/*!
*	\brief The smallest unit of mesurment
*/
#define EPSILON 1

/*!
*	\brief Width of score showing on the screen
*/
#define SCORE_WIDTH 100

/*!
*	\brief Heihgt of score showing on the screen
*/
#define SCORE_HEIGHT 60

/*!
*	\brief Number of blocks showing from the top to the bottom of the screen
*/
#define MAP_HEIGHT 15

/*!
*	\brief Number of blocks showing from the left to the right of screen
*/
#define MAP_WIDTH 15

/*!
*	\brief Number of segments which are dimension MAP_HEIGHT x MAP_WIDTH on the map
*/
#define MAP_SEGMENTS_NUMBER 20

/*!
*	\brief Number of demo map segment
*/
#define DEMO_MAP_SEGMENTS_NUMBER 5

/*!
*	\brief Number of all objects in the game
*/
#define AI_NUMBER 17
#define AI_MAX_NUMBER 1000

/*!
*	\brief Variable representing if game is running
*/
static int Game_Running = 1;

/*!
*	\brief Variable representing if music is on or off
*/
int music;

/*!
*	\brief Contains vector of 2d coordinates
*/
typedef struct PAIR_XY {
	int x;
	int y;
}Pair_xy;

/*!
*	\brief Structure representing Mario
*/
typedef struct {

	Pair_xy coordinates, size, speed, dimension;
	int direction;
	int lives;
	int immortality_timer;
	int projectileTimer;
	int animation_Stage;
	int facing;
	int time;
	int jump_timer;
	SDL_Texture *animation[4][2][3];
	int jump_sound;
} Mario;

/*!
*	\brief Structure representing Devil/Turtle AI
*/
typedef struct DEVIL {
	//Istovremeno Devil i Turtle
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int type;
	int animation_Stage;
	int time;
	SDL_Texture *animation[5];
}ai_Devil;

/*!
*	\brief Structure representing Plant AI
*/
typedef struct PLANTIE {
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int timer_Sleep;
	int animation_Stage;
	int additional_Height;
	int time;
	SDL_Texture *animation[2];
}ai_Plantie;

/*!
*	\brief Structure representing Mario projectile
*/
typedef struct PROJECTILE {
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int nubmer_Of_Bounces;
	SDL_Texture *animation;
}ai_Projectile;

/*!
*	\brief Structure representing Mushroom/Star/Coin/Brick
*/
typedef struct SHROOM {
	//Istovremeno Shroom, Star, Coin, Brick
	Pair_xy coordinate, speed, dimension, newCordinate;
	int isAlive;
	int type;
	int animation_Stage;
	int time; //za animacije
	SDL_Texture *animation;
}ai_Shroom;

/*!
*	\brief Structure representing Question block
*/
typedef struct QUESTION {
	Pair_xy coordinate, dimension;
	int storage;
	int animation_Stage;
	SDL_Texture *animation[2];
}ai_Question;

/*!
*	\brief Structure representing Hidden block
*/
typedef struct HIDDEN {
	Pair_xy coordinate, speed, dimension;
	int isAlive;
	int coins_Left;
	int animation_Stage;
	SDL_Texture *animation[2];
}ai_Hidden;
/*!
*	\brief Structure representing non-interactable ground
*/
typedef struct STOCK_FLOOR {
	//ground, pipe
	Pair_xy coordinate, dimension;
	SDL_Texture *animation;
}Ground;

/*!
*		\brief Main structure that cantains all active AI's and all blocks on the map
*/
typedef struct {
	void *ai_Matrix[AI_NUMBER][AI_MAX_NUMBER];
	int map_Matrix[MAP_HEIGHT][MAP_WIDTH * MAP_SEGMENTS_NUMBER];
	int ai_counter[AI_NUMBER];
	int x_score;
	int score;
	int x_passed;
	int timer;
}Map;

#endif // !all_h

