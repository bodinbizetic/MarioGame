#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <SDL.h>
#include "ai.h"
#include "main_menu.h"
#include "mario.h"

enum col{NO_COLLISION, YES_COLLISION};

int detectGravityCollide(Map *map, Mario *mario) {
	for(int j=0; j<sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
	for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

		Pair_xy new_coordinates;
		new_coordinates.x = mario->coordinates.x + mario->speed.x;
		new_coordinates.y = mario->coordinates.y + mario->speed.y;
		switch (gravity_Blocks[j])
		{
		case ground: {
			Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate) == 2)
				return g->coordinate.y;
			break;
		}
		case basic: {
			ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate) == 2)
				return g->coordinate.y;
			break;
		}
		case question: {
			ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate) == 2)
				return g->coordinate.y;
			break;
		}
		case hidden: {
			ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
			if (collision(mario->size, new_coordinates, g->dimension, g->coordinate) == 2)
				return g->coordinate.y;
			break;
		}
		default:
			break;
		}
		
		
		
		
	}
	return NO_COLLISION;
}

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
	int collision_Check = detectGravityCollide(map, mario);
	if (collision_Check > 0) {
		if (mario->speed.y > 0)
			mario->speed.y = 0;
		mario->coordinates.y = collision_Check - mario->size.y;
	}
	else
		mario->speed.y += G;
	
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
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(renderer, &rect);
}