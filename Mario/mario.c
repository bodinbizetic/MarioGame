#include <stdio.h>
#include <stdlib.h>
#include "SDL_ttf.h"
#include "map.h"
#include <SDL.h>
#include "ai.h"
#include "main_menu.h"
#include "mario.h"
#include "game.h" 
#include "sound.h"

/*!	\file mario.c
*	\brief Contains functions that control Marios movements
*/
extern short marioCharacter;
extern short backFromBlack;
/*!	
*	\brief If == 1, enables flying
*/
int fly_cheat = 0;

/*!
*	\brief If == 1, enables immortality (cant get hit by enemies)
*/
int immortality_cheat = 0;

/*!
*	\brief Zero speed vector 
*/
Pair_xy zeroSpeed = { 0,0 };

/*!
*	\brief Reduces Mario's life by one. Also shrinks Mario.
*	\param mario Address of active Mario struct
*/
void lose_Life(Mario *mario) {
	if (mario->immortality_timer == 0) {
		if (mario->lives > 1) {
			mario->lives --;
			playLoseLife();
			marioCharacter = backFromBlack;
			if (mario->lives == 1) {
				mario->size.y = blok.y * MARIO_SHRINK / 100;
				mario->coordinates.y += blok.y + (1 - MARIO_SHRINK) * blok.y / 100;
				mario->dimension.y = 2 * blok.y * MARIO_SHRINK / 100;
			}
				
			mario->immortality_timer = MAX_IMORTAL;
		}
		else
			if (mario->lives == 1) {
				mario->lives = 0;
				playMarioDie();
			}
	}
	//return 0;
}

/*!
*	\brief Increses Mario's life by one. Also magnifies Mario.
*	\param mario Address of active Mario struct
*/
void gainLife(Mario *mario) {
	if (mario->lives < 3) {
		playPowerUp();
		mario->lives++;
		if (mario->lives == 2) {
			mario->coordinates.y -= mario->size.y ;
			mario->size.y = 2 * mario->size.y;
		}
		else if (mario->lives == 3) marioCharacter = 2;
	}
	mario->immortality_timer = MAX_IMORTAL;

}

/*!
*	\brief Detects and regulates collide between Mario and other AIs
*	\param mario Address of active Mario struct
*	\param map Address of map structure on which the game is played
*	\return returns 0 if there is no error
*/
int detectAiCollide(Map *map, Mario *mario) {
	for (int j = 1; j < sizeof(ai_id) / sizeof(ai_id[0]); j++)
		for (int i = 0; i < map->ai_counter[ai_id[j]]; i++) {
			switch (ai_id[j])
			{
			case shroom: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				if (collision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed) > 0 || simpleCollision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed)) {
					playKill();
					map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
					g->isAlive = 0;
					free(g);
					map->score += SHROOM_SCORE;
					gainLife(mario);

				}

				break;
			}
			case star: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				

				break;
			}
			case turtle: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				int t;
				if (t = collision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed), t > 0 || simpleCollision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed)) {
					if (g->isAlive) {
						if (mario->coordinates.y + mario->size.y - mario->speed.y <= g->coordinate.y) {
							playKill();
							g->isAlive = 0;
							g->speed.x = 0;
							g->animation_Stage = 4;
							map->score += ENEMY_KILL;
							mario->speed.y *= -1;
						}
						else lose_Life(mario);
					}
					else if (g->speed.x != 0) {

						if(g->type == 0)
							lose_Life(mario);
						//mario->speed.y *= -1;
					}
					else {
						if(mario->speed.y != 0 || mario->speed.x != 0)
						g->speed.x = (abs(mario->speed.x) + 5 * TURTLE_SPEED) * ((mario->speed.x >= 0) ? 1 : -1);
						//mario->speed.y *= -1;
					}
				}
				break;
			}
			case devil: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				if (collision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed) > 0 || simpleCollision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed)) {
					if (mario->coordinates.y + mario->size.y - mario->speed.y <= g->coordinate.y) {
						playKill();
						map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
						g->isAlive = 0;
						spawnDeathDevil(map, g->coordinate, g->animation[2]);
						/*g->animation_Stage = 2; ne radi ovo kad umre
						if(g->time%50==0)*/
						free(g);
						map->score += ENEMY_KILL;
						mario->speed.y *= -1;
					}
					else lose_Life(mario);
				}
				break;
			}
			case plantie: {
				ai_Plantie *g = (ai_Plantie *)map->ai_Matrix[ai_id[j]][i];
				
				if (collision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed) > 0 || simpleCollision(g->dimension, g->coordinate, mario->size, mario->coordinates, g->speed, mario->speed)) {
					if (mario->coordinates.y + mario->size.y - mario->speed.y + g->speed.y <= g->coordinate.y && g->isAlive == 1 && mario->speed.y > 0) {
						playKill();
						map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
						g->isAlive = 0;
						free(g);
						map->score += ENEMY_KILL;
						mario->speed.y *= -1;
					}
					else lose_Life(mario);
				}
				break;
			}case flag: {
				Ground *g = (Ground *)map->ai_Matrix[ai_id[j]][i];

				if (collision(g->dimension, g->coordinate, mario->size, mario->coordinates,zeroSpeed, mario->speed) > 0 || simpleCollision(g->dimension, g->coordinate, mario->size, mario->coordinates, zeroSpeed, mario->speed)) {
					mario->speed.x = 0;
					mario->coordinates.x = g->coordinate.x - blok.x * FLAG_SHRINK / 200;
					return -1;
				}
				
				break;

			}
			default:
				break;
			}




		}
	for (int i = 0; i < map->ai_counter[pikes]; i++) {
		ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[pikes][i];
		if (simpleCollision(g->dimension, g->coordinate, mario->size, mario->coordinates, zeroSpeed, mario->speed) > 0 )
			lose_Life(mario);

	}
	return 0;
}

/*!
*	\brief Detects and regulates bottom collide between Mario and blocks
*	\param mario Address of active Mario struct
*	\param map Address of map structure on which the game is played
*	\return returns y coordinate of the collision between Mario and block
*/
int detectGravityCollide(Map *map, Mario *mario) {
	for(int j=0; j<sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
	for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

		Pair_xy new_coordinates;
		new_coordinates.x = mario->coordinates.x;
		new_coordinates.y = mario->coordinates.y;
		switch (gravity_Blocks[j])
		{
		case ground: {
			Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 2)
				return g->coordinate.y;
			break;
		}
		case basic: {
			ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 2)
					return g->coordinate.y;
			break;
		}
		case question: {
			ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 2)
					return g->coordinate.y;
			break;
		}
		case hidden: {
			ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 2)
					return g->coordinate.y;
			break;
		}
		case pipe: {
			Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 2)
					return g->coordinate.y;
			break;
		}
		default:
			break;
		}
		
		
		
		
	}
	return NO_COLLISION;
}

/*!
*	\brief Detects and regulates side collide between Mario and blocks
*	\param mario Address of active Mario struct
*	\param map Address of map structure on which the game is played
*	\return returns x coordinate of the collision between Mario and block
*/
int detectSideCollide(Map *map, Mario *mario) {
	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = mario->coordinates.x;
			new_coordinates.y = mario->coordinates.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed), t > 2)
					return ((t == 3) ? g->coordinate.x - mario->size.x - EPSILON : g->coordinate.x + g->dimension.x + EPSILON);
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed), t > 2)
					return ((t == 3) ? g->coordinate.x - mario->size.x - EPSILON : g->coordinate.x + g->dimension.x + EPSILON);
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed), t > 2)
					return ((t == 3) ? g->coordinate.x - mario->size.x - EPSILON : g->coordinate.x + g->dimension.x + EPSILON);
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed), t > 2)
					return ((t == 3) ? g->coordinate.x - mario->size.x - EPSILON : g->coordinate.x + g->dimension.x + EPSILON);
				break;
			}
			case pipe: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed), t > 2)
					return ((t == 3) ? g->coordinate.x - mario->size.x - EPSILON : g->coordinate.x + g->dimension.x + EPSILON);
				break;
			}
			default:
				break;
			}




		}
	return NO_COLLISION;
}

/*!
*	\brief Detects and regulates side collide between Mario and blocks
*	\param mario Address of active Mario struct
*	\param map Address of map structure on which the game is played
*	\param blockTextures SDL_Textures for all AIs
*	\return returns y coordinate of the collision between Mario and block
*/
int detectCellingCollide(Map *map, Mario *mario, SDL_Texture *block_Texture[AI_NUMBER][5]) {
	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = mario->coordinates.x;

			new_coordinates.y = mario->coordinates.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1)
						return new_coordinates.y;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1) {

					if (mario->lives > 1 && mario->speed.y < 0) {
						playBreakBlock();
						map->ai_Matrix[gravity_Blocks[j]][i] = map->ai_Matrix[gravity_Blocks[j]][--map->ai_counter[gravity_Blocks[j]]];
						free(g);
						map->score += BLOCK_KILL;
						
					}
					else {
						g->coordinate.y -= 15;
					}
					return new_coordinates.y;
				}
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1) {

					if(g->storage > 0)
						map->score += QUESTION_POP;
						Pair_xy temp_coord;
						temp_coord.x = g->coordinate.x;
						temp_coord.y = g->coordinate.y - g->dimension.y;
						if (g->storage == 1) {
							playPowerUpAppears();
							spawnShroom(map, temp_coord,block_Texture,mario->lives);
							g->storage--;
						
					}
						g->animation_Stage = 1;
					return new_coordinates.y;
				}
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1) {
					if (g->coins_Left) {
						map->score += HIDDEN_SCORE;
						g->coins_Left--;
						Pair_xy temp_coord;
						temp_coord.x = g->coordinate.x;
						temp_coord.y = g->coordinate.y - g->dimension.y;
						playCoin();
						spawnCoin(map, temp_coord, block_Texture);
					}
					if (g->coins_Left == 0)
						g->animation_Stage = 1;
					return new_coordinates.y;
				}
					
					
				break;
			}
			case pipe: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1)
						return new_coordinates.y;
				break;
			}
			default:
				break;
			}




		}
	return NO_COLLISION;
}

/*!
*	\brief Detects and regulates side collide between Mario and blocks. Visits map in reverse order
*	\param mario Address of active Mario struct
*	\param map Address of map structure on which the game is played
*	\param blockTextures SDL_Textures for all AIs
*	\return returns y coordinate of the collision between Mario and block
*/
int detectReverseCellingCollide(Map *map, Mario *mario, SDL_Texture *block_Texture[AI_NUMBER][5]) {
	for (int j = sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0])-1; j >=0; j--)
		for (int i = map->ai_counter[gravity_Blocks[j]]-1; i >=0 && map->ai_counter[gravity_Blocks[j]]; i--) {

			Pair_xy new_coordinates;
			new_coordinates.x = mario->coordinates.x;

			new_coordinates.y = mario->coordinates.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1)
					return new_coordinates.y;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1) {

					if (mario->lives > 1 && mario->speed.y < 0) {
						//playBreakBlock();
						map->ai_Matrix[gravity_Blocks[j]][i] = map->ai_Matrix[gravity_Blocks[j]][--map->ai_counter[gravity_Blocks[j]]];
						free(g);
						map->score += BLOCK_KILL;
					}
					return new_coordinates.y;
				}
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1) {

					if(g->storage > 0)
					map->score += QUESTION_POP;
					Pair_xy temp_coord;
					temp_coord.x = g->coordinate.x;
					temp_coord.y = g->coordinate.y - g->dimension.y;
					if (g->storage == 1) {
						playPowerUpAppears();
						spawnShroom(map, temp_coord, block_Texture, mario->lives);
						g->storage--;

					}
					g->animation_Stage = 1;
					return new_coordinates.y;
				}
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1) {
					if (g->coins_Left) {
						map->score += HIDDEN_SCORE;
						g->coins_Left--;
					}
					if (g->coins_Left == 0)
						g->animation_Stage = 1;
					return new_coordinates.y;
				}


				break;
			}
			case pipe: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed, zeroSpeed) == 1)
					return new_coordinates.y;
				break;
			}
			default:
				break;
			}




		}
	return NO_COLLISION;
}

/*!
*	\brief Function that updates Marios movement, and handles interactions between Mario and other objects 
*	\param window Address of current active SDL_Window 
*	\param renderer Address of main SDL_Renderer
*	\param mario Address of active Mario struct
*	\param map Address of map structure on which the game is played
*	\param update Code of Mario's movement update
*	\param blockTextures SDL_Textures for all AIs
*	\return returns y coordinate of the collision between Mario and block
*/
int updateMario(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario,Pair_xy update, SDL_Texture *block_Texture[AI_NUMBER][5]) {
	SDL_Rect rect;
	rect.h = mario->size.y;
	rect.w = mario->size.x;
	//update gleda strelicu
	//0 je desno
	if (update.x == 0) {
		//direction 1 desno
		//x=0 ide desno
		mario->direction = 1;
		if (mario->speed.x <= 16)
			mario->speed.x += 2;
	}
	//1 je levo
	//x=1 ide levo
	else if (update.x == 1) {
		mario->direction = 0;
		if (mario->speed.x >= -16)
			mario->speed.x -= 2;
	}
	else if (update.x == 2) {
		if (mario->speed.x > 0)
			mario->speed.x -= 2;
		else if (mario->speed.x < 0)
			mario->speed.x += 2;
	}
	//y=1  je gore
	if (update.y == 1 && mario->jump_timer < MAX_JUMP) {
		if (mario->jump_timer == 0)
			playJump();
		if (fly_cheat == 0) 
			mario->jump_timer += 1;
		
		if (mario->speed.y >= -16)
			mario->speed.y -= 2;

		
	}
	//y=0 je dole 
	else if (update.y == 0) {
		if (mario->speed.y <= 16)
			mario->speed.y += 2;
		
	}
	/*else if (update.y == 2) {
		if (mario->speed.y > 0)
			mario->speed.y -= 2;
		else if (mario->speed.y < 0)
			mario->speed.y += 2;
	}*/
	if (immortality_cheat) {
		if (mario->immortality_timer != 0)
			mario->immortality_timer--;
		else
			mario->immortality_timer = MAX_IMORTAL;
	}
	else
	if (mario->immortality_timer)
		mario->immortality_timer--;
	if (mario->projectileTimer != 0)
		mario->projectileTimer++;
	if (mario->projectileTimer % PROJECTILE_TIMER == 0)
		mario->projectileTimer = 0;

	int collision_Check = 0;
	int ai_check = detectAiCollide(map, mario);
	if (ai_check == -1) return 1;
	int side_Check = detectSideCollide(map, mario);
	//ide u desno ili u levo i udara u block
	if (side_Check > 0) {

		mario->speed.x = 0;
		if (mario->speed.x == 0)
			mario->coordinates.x = side_Check;

	}

	int celling_Check = detectCellingCollide(map, mario, block_Texture);
	detectReverseCellingCollide(map, mario,block_Texture);
	if (celling_Check > 0) {
		if (mario->speed.y < 0) {
			mario->speed.y *= -1;
			mario->coordinates.y = celling_Check;
		}
		
		
	}
	
	

	

	static int gravity_Check; 
	gravity_Check = detectGravityCollide(map, mario);
	/*if (gravity_Check > 0 && mario->speed.y >= 0)
		gravity_Check2 = gravity_Check;
	else {
		gravity_Check = 0;
	}*/
	if (gravity_Check > 0) {
		//gravity_Check = gravity_Check2;
		mario->jump_timer = 0;
		if (mario->speed.y > 0) {
			mario->speed.y = 0;
			mario->coordinates.y = gravity_Check - mario->size.y;
		}
		
	}
	else
		mario->speed.y += G;

	
	//Ogranicavanje brzine 
	if (mario->speed.y < -MAXSPEED)
		mario->speed.y = -MAXSPEED;
	if (mario->speed.x < -MAXSPEED)
		mario->speed.x = -MAXSPEED;
	if (mario->speed.x > MAXSPEED)
		mario->speed.x = MAXSPEED;
	
	mario->coordinates.y += mario->speed.y;
	mario->coordinates.x += mario->speed.x;
	if (map->x_score < mario->coordinates.x - (SCREEN_WIDTH / 2 + 2 * blok.x))
		map->x_score = mario->coordinates.x - (SCREEN_WIDTH / 2 + 2 * blok.x);
	if (mario->coordinates.x < blok.x)
		mario->coordinates.x = blok.x;
	if (mario->coordinates.x > SCREEN_WIDTH*MAP_SEGMENTS_NUMBER - blok.x)
		mario->coordinates.x = SCREEN_WIDTH*MAP_SEGMENTS_NUMBER - blok.x;
	/*if (mario->coordinates.x > SCREEN_WIDTH - mario->size.x)
		mario->coordinates.x = SCREEN_WIDTH - mario->size.x;*/
	if (mario->coordinates.y < 0)
		mario->coordinates.y = 0;
	/*if (mario->coordinates.y > SCREEN_HEIGHT - mario->size.x)
		mario->coordinates.y = SCREEN_HEIGHT - mario->size.x;*/
	if (mario->coordinates.x > SCREEN_WIDTH / 2 + blok.x && mario->coordinates.x<SCREEN_WIDTH*MAP_SEGMENTS_NUMBER -SCREEN_WIDTH/2-blok.x/8)
	map->x_passed = - mario->coordinates.x+SCREEN_WIDTH/2;
	/*if (mario->coordinates.x + mario->size.x <= SCREEN_WIDTH && mario->speed.x>0)
		mario->coordinates.x += mario->speed.x;
	if (mario->coordinates.x >=0 && mario->speed.x<0)

		mario->coordinates.x += mario->speed.x;
	if (mario->coordinates.y + mario->size.y <= SCREEN_HEIGHT && mario->speed.y>0)
		mario->coordinates.y += mario->speed.y;
	if (mario->coordinates.y >= 0 && mario->speed.y<0)
		mario->coordinates.y += mario->speed.y;*/
	rect.x = mario->coordinates.x + map->x_passed - blok.x * (100 - MARIO_SHRINK_X) / 200;
	rect.y = mario->coordinates.y;
	rect.w = mario->dimension.x;
	rect.h = mario->size.y;
	// swaping animation - ovo smenjuje animacije
	mario->time++;
	if (gravity_Check == 0 ) mario->animation_Stage = 2;
	else if (mario->speed.x == 0) mario->animation_Stage = 0;
	else if (mario->time % 5 == 0) {
		if (mario->speed.x != 0 && mario->speed.y == 0) {
			if (mario->animation_Stage == 0) mario->animation_Stage = 1;
			else mario->animation_Stage = 0;
		}
	}

	// drawing mario - crtanje maria (kao slika ne kao kockica)
	if(mario->immortality_timer % 8 != 1)
	SDL_RenderCopy(renderer, mario->animation[marioCharacter][mario->facing][mario->animation_Stage], NULL, &rect);
	return 0;
	/*SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(renderer, &rect);*/
}