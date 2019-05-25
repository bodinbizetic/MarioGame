#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <SDL.h>
#include "ai.h"
#include "main_menu.h"
#include "mario.h"
#include "game.h"

int lose_Life(Mario *mario) {
	if (mario->lives > 1) {
		mario->lives = 1;
		mario->size.y = blok.y;
		mario->coordinates.y += blok.y;
	}

	return 0;
}
int detectAiCollide(Map *map, Mario *mario) {
	for (int j = 1; j < sizeof(ai_id) / sizeof(ai_id[0]); j++)
		for (int i = 0; i < map->ai_counter[ai_id[j]]; i++) {
			switch (ai_id[j])
			{
			case shroom: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				

				break;
			}
			case star: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				

				break;
			}
			case turtle: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				int t;
				if (t = collision(g->dimension, g->coordinate, mario->size, mario->coordinates, mario->speed), t > 0) {
					if (g->isAlive) {
						if (mario->coordinates.y + mario->size.y - mario->speed.y <= g->coordinate.y) {
							g->isAlive = 0;
							g->speed.x = 0;
							map->score += ENEMY_KILL;
							mario->speed.y *= -1;
						}
						else lose_Life(mario);
					}
					else if (g->speed.x != 0) {

						
						//lose_Life(mario);
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
				if (collision(g->dimension, g->coordinate, mario->size, mario->coordinates, mario->speed) > 0) {
					if (mario->coordinates.y + mario->size.y - mario->speed.y <= g->coordinate.y) {
						map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
						g->isAlive = 0;
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

				break;
			}
			default:
				break;
			}




		}
	return 0;
}
int detectGravityCollide(Map *map, Mario *mario) {
	for(int j=0; j<sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
	for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

		Pair_xy new_coordinates;
		new_coordinates.x = mario->coordinates.x;
		new_coordinates.y = mario->coordinates.y + mario->speed.y;
		switch (gravity_Blocks[j])
		{
		case ground: {
			Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 2)
				if(g->coordinate.y > new_coordinates.y)
				return g->coordinate.y;
			break;
		}
		case basic: {
			ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 2)
				if (g->coordinate.y  > new_coordinates.y)
					return g->coordinate.y;
			break;
		}
		case question: {
			ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 2)
				if (g->coordinate.y > new_coordinates.y)
					return g->coordinate.y;
			break;
		}
		case hidden: {
			ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 2)
				if (g->coordinate.y > new_coordinates.y)
					return g->coordinate.y;
			break;
		}
		case pipe: {
			Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 2)
				if (g->coordinate.y > new_coordinates.y)
					return g->coordinate.y;
			break;
		}
		default:
			break;
		}
		
		
		
		
	}
	return NO_COLLISION;
}

int detectSideCollide(Map *map, Mario *mario) {
	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = mario->coordinates.x + mario->speed.x;
			new_coordinates.y = mario->coordinates.y ;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed), t > 2)
					if (g->coordinate.y > new_coordinates.y)
						return t;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed), t > 2)
					return ((t == 3) ? g->coordinate.x - mario->size.x : g->coordinate.x + g->dimension.x);
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed), t > 2)
					if (g->coordinate.y > new_coordinates.y)
						return t;
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed), t > 2)
					if (g->coordinate.y > new_coordinates.y)
						return g->coordinate.x * ((t == 3) ? -1 : 1);
				break;
			}
			case pipe: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed), t > 2)
					return ((t == 3) ?  g->coordinate.x - mario->size.x: g->coordinate.x + g->dimension.x);
				break;
			}
			default:
				break;
			}




		}
	return NO_COLLISION;
}
//Detektuje udarac u plafon i vraca kordinate udarca po y osi
int detectCellingCollide(Map *map, Mario *mario) {
	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = mario->coordinates.x;
			new_coordinates.y = mario->coordinates.y + mario->speed.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 1)
					if (g->coordinate.y < new_coordinates.y)
						return new_coordinates.y;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 1)
					if (g->coordinate.y <= new_coordinates.y) {
						if (mario->lives > 1) {
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
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 1)
					if (g->coordinate.y < new_coordinates.y)
						return new_coordinates.y;
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 1)
					if (g->coordinate.y < new_coordinates.y)
						return new_coordinates.y;
				break;
			}
			case pipe: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(mario->size, new_coordinates, g->dimension, g->coordinate, mario->speed) == 1)
					
						return new_coordinates.y;
				break;
			}
			default:
				break;
			}




		}
	return NO_COLLISION;
}

extern short marioCharacter;
void updateMario(SDL_Window *window, SDL_Renderer *renderer, Map *map, Mario *mario,Pair_xy update) {
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
	if (update.y == 1) {
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
	detectAiCollide(map, mario);
	int collision_Check = detectCellingCollide(map, mario);
	detectCellingCollide(map, mario);
	if (collision_Check > 0) {
		if (mario->speed.y < 0)
			mario->speed.y *= -1;
		mario->coordinates.y = collision_Check;
		

	}
	
	collision_Check = detectSideCollide(map, mario);
	//ide u desno ili u levo i udara u block
	if (collision_Check > 0) {
		//if (mario->speed.x < 0)
			mario->speed.x = 0;
		if (mario->speed.x == 0)
			mario->coordinates.x = collision_Check;
		
	}

	collision_Check = detectGravityCollide(map, mario);
	if (collision_Check > 0) {
		if (mario->speed.y > 0)
			mario->speed.y = 0;
		mario->coordinates.y = collision_Check - mario->size.y + 1;
		
	}
	else
		mario->speed.y += G;

	//Da ne izlazi sa ekrana: Samo za debugovanje
	if (mario->coordinates.x < 0)
		mario->coordinates.x = 0;
	if (mario->coordinates.x > SCREEN_WIDTH - mario->size.x)
		mario->coordinates.x = SCREEN_WIDTH - mario->size.x;
	
	mario->coordinates.y += mario->speed.y;
	mario->coordinates.x += mario->speed.x;
	/*if (mario->coordinates.x + mario->size.x <= SCREEN_WIDTH && mario->speed.x>0)
		mario->coordinates.x += mario->speed.x;
	if (mario->coordinates.x >=0 && mario->speed.x<0)
		mario->coordinates.x += mario->speed.x;
	if (mario->coordinates.y + mario->size.y <= SCREEN_HEIGHT && mario->speed.y>0)
		mario->coordinates.y += mario->speed.y;
	if (mario->coordinates.y >= 0 && mario->speed.y<0)
		mario->coordinates.y += mario->speed.y;*/
	rect.x = mario->coordinates.x;
	rect.y = mario->coordinates.y;

	// swaping animation - ovo smenjuje animacije
	mario->time++;
	if (collision_Check == 0 ) mario->animation_Stage = 2;
	else if (mario->speed.x == 0) mario->animation_Stage = 0;
	else if (mario->time % 5 == 0) {
		if (mario->speed.x != 0 && mario->speed.y == 0) {
			if (mario->animation_Stage == 0) mario->animation_Stage = 1;
			else mario->animation_Stage = 0;
		}
	}

	// drawing mario - crtanje maria (kao slika ne kao kockica)
	SDL_RenderCopy(renderer, mario->animation[marioCharacter][mario->facing][mario->animation_Stage], NULL, &rect);

	/*SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(renderer, &rect);*/
}