#include "SDL.h"
#include "ai.h"
#include "game.h"

int detectGravityCollideAi(Map *map, Pair_xy coord, Pair_xy dim, Pair_xy speed) {
	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = coord.x + speed.x;
			new_coordinates.y = coord.y + speed.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed) == 2)
					return g->coordinate.y;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed) == 2)
					return g->coordinate.y;
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed) == 2)
					return g->coordinate.y;
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed) == 2)
					return g->coordinate.y;
				break;
			}
			default:
				break;
			}




		}
	return NO_COLLISION;
}

int detectSideCollideAi(Map *map, Pair_xy coord, Pair_xy dim, Pair_xy speed) {
	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = coord.x + speed.x;
			new_coordinates.y = coord.y + speed.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed) > 2)
					return g->coordinate.x;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(dim, new_coordinates, g->dimension, g->coordinate, speed), t > 2)
					return g->coordinate.x;
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed) > 2)
					return g->coordinate.x;
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed) > 2)
					return g->coordinate.x;
				break;
			}
			default:
				break;
			}




		}
	return -1;
}
int drawAI(SDL_Window *window, SDL_Renderer *renderer, Map *map) {
	for (int j = 0; j < sizeof(ai_id) / sizeof(ai_id[0]); j++)
		for (int i = 0; i < map->ai_counter[ai_id[j]]; i++) {

			Pair_xy new_coordinates;
			SDL_Rect rect;
			switch (ai_id[j])
			{
			case projectile: {
				ai_Projectile *g = (ai_Projectile *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 210, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			case shroom: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 210, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			case star: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 210, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			case turtle: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 0, 210, 30, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				else {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			case devil: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 210, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			case plantie: {
				ai_Plantie *g = (ai_Plantie *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 210, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			default:
				break;
			}




		}
	return 0;
}
int updateAI(Map *map) {
	for (int j = 0; j < sizeof(ai_id) / sizeof(ai_id[0]); j++)
		for (int i = 0; i < map->ai_counter[ai_id[j]]; i++) {
			Pair_xy new_coordinates;
			SDL_Rect rect;
			switch (ai_id[j])
			{
			case projectile: {
				ai_Projectile *g = (ai_Projectile *)map->ai_Matrix[ai_id[j]][i];
				

				break;
			}
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
				int temp_col = detectGravityCollideAi(map, g->coordinate, g->dimension, g->speed);
				if (temp_col > 0) {
					g->speed.y = 0;
					g->coordinate.y = temp_col - g->dimension.y;
				}
				else g->speed.y += G;
				
				g->coordinate.x += g->speed.x;
				g->coordinate.y += g->speed.y;
				break;
			}
			case devil: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				int temp_col = detectGravityCollideAi(map, g->coordinate, g->dimension, g->speed);
				if (temp_col > 0) {
					g->speed.y = 0;
					g->coordinate.y = temp_col - g->dimension.y;
				}
				else g->speed.y += G;

				temp_col = detectSideCollideAi(map, g->coordinate, g->dimension, g->speed);
				if (temp_col > 2 )
					g->speed.x *= -1;
				//else if (temp_col == 4 && g->speed.x < 0)
					//g->speed.x *= -1;

				g->coordinate.x += g->speed.x;
				g->coordinate.y += g->speed.y;
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
}