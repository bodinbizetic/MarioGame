#ifndef mario_h
#define mario_h
#include "ai.h"
typedef struct {
	
	Pair_xy coordinates, size, speed;
	int direction;
	int lives;
	int immortality;
	int projectileTimer;
	int animation_Stage;
}Mario;
#endif
