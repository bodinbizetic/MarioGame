#include "SDL.h"
#include "ai.h"
#include "game.h"
#include "main_menu.h"
extern Pair_xy zeroSpeed;
int detectGravityCollideAi(Map *map, Pair_xy coord, Pair_xy dim, Pair_xy speed) {
	for (int j = 0; j < sizeof(gravity_Blocks) / sizeof(gravity_Blocks[0]); j++)
		for (int i = 0; i < map->ai_counter[gravity_Blocks[j]]; i++) {

			Pair_xy new_coordinates;
			new_coordinates.x = coord.x;
			new_coordinates.y = coord.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) == 2)
					return g->coordinate.y;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) == 2)
					return g->coordinate.y;
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) == 2)
					return g->coordinate.y;
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) == 2)
					return g->coordinate.y;
				break;
			}
			case pipe: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) == 2)
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
			new_coordinates.x = coord.x;
			new_coordinates.y = coord.y;
			switch (gravity_Blocks[j])
			{
			case ground: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) > 2)
					return g->coordinate.x;
				break;
			}
			case basic: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[gravity_Blocks[j]][i];
				int t;
				if (t = collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed), t > 2)
					return g->coordinate.x;
				break;
			}
			case question: {
				ai_Question *g = (ai_Question *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) > 2)
					return g->coordinate.x;
				break;
			}
			case hidden: {
				ai_Hidden *g = (ai_Hidden *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) > 2)
					return g->coordinate.x;
				break;
			}
			case pipe: {
				Ground *g = (Ground *)map->ai_Matrix[gravity_Blocks[j]][i];
				if (collision(dim, new_coordinates, g->dimension, g->coordinate, speed, zeroSpeed) > 2)
					return g->coordinate.x;
				break;
			}
			default:
				break;
			}




		}

	return -1;
}

int projectileCollision(Map *map, Pair_xy coord, Pair_xy dim, Pair_xy speed) {
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
				if (collision(dim, coord, g->dimension, g->coordinate, speed, g->speed) > 0) {
					if (g->isAlive) {
						
							map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
							g->isAlive = 0;
							free(g);
							map->score += ENEMY_KILL;
						
					}
					return 1;
				}
				
				break;
			}
			case devil: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				if (collision(dim, coord, g->dimension, g->coordinate, speed, g->speed) > 0) {
					map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
					g->isAlive = 0;
					free(g);
					map->score += ENEMY_KILL;
					return 1;
				}
				
				break;
			}
			case plantie: {
				ai_Plantie *g = (ai_Plantie *)map->ai_Matrix[ai_id[j]][i];
				if (collision(dim, coord, g->dimension, g->coordinate, speed, g->speed) > 0)  {
					if (g->isAlive) {

						map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
						g->isAlive = 0;
						free(g);
						map->score += ENEMY_KILL;

					}
					return 1;
				}
				
				break;
			}
			default:
				break;
			}




		}
	return 0;
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
					rect.x = g->coordinate.x+ map->x_passed;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			case shroom: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x+ map->x_passed;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				break;
			}
			case star: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x+ map->x_passed;
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
					rect.x = g->coordinate.x+ map->x_passed;
					rect.y = g->coordinate.y;
					SDL_RenderCopy(renderer, g->animation[g->animation_Stage], NULL, &rect);
					/*SDL_SetRenderDrawColor(renderer, 0, 210, 30, 255);
					SDL_RenderFillRect(renderer, &rect);*/
				}
				else {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x+ map->x_passed;
					rect.y = g->coordinate.y;
					SDL_RenderCopy(renderer, g->animation[g->animation_Stage], NULL, &rect);
					/*SDL_SetRenderDrawColor(renderer, 0, 210, 100, 255);
					SDL_RenderFillRect(renderer, &rect);*/
				}

				break;
			}
			case devil: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x+ map->x_passed;
					rect.y = g->coordinate.y;
					SDL_RenderCopy(renderer, g->animation[g->animation_Stage], NULL, &rect);
					/*SDL_SetRenderDrawColor(renderer, 210, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);*/
				}

				break;
			}
			case plantie: {
				ai_Plantie *g = (ai_Plantie *)map->ai_Matrix[ai_id[j]][i];
				if (g->isAlive) {
					rect.h = g->dimension.y;
					rect.w = g->dimension.x;
					rect.x = g->coordinate.x+ map->x_passed;
					rect.y = g->coordinate.y;
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				for (int i = 0; i < map->ai_counter[pipe]; i++) {
					Ground *g = (Ground *)map->ai_Matrix[pipe][i];
					rect.x = g->coordinate.x + map->x_passed;
					rect.y = g->coordinate.y;
					rect.w = g->dimension.x;
					rect.h = g->dimension.y;
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
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

int updateAI(Map *map, Mario *mario) {
	for (int j = 0; j < sizeof(ai_id) / sizeof(ai_id[0]); j++)
		for (int i = 0; i < map->ai_counter[ai_id[j]]; i++) {
			Pair_xy new_coordinates;
			SDL_Rect rect;
			switch (ai_id[j])
			{
			case projectile: {
				ai_Projectile *g = (ai_Projectile *)map->ai_Matrix[ai_id[j]][i];
				int temp_col = detectGravityCollideAi(map, g->coordinate, g->dimension, g->speed);
				if (temp_col > 0) {
					g->speed.y *= -1;
					g->coordinate.y = temp_col - g->dimension.y;
					g->nubmer_Of_Bounces--;
				}
				else g->speed.y += G;

				temp_col = detectSideCollideAi(map, g->coordinate, g->dimension, g->speed);
				if (temp_col > 0 || g->nubmer_Of_Bounces == 0) {
					map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
					g->isAlive = 0;
					free(g);
				}
				temp_col = projectileCollision(map, g->coordinate, g->dimension, g->speed);
				
				g->coordinate.x += g->speed.x;
				g->coordinate.y += g->speed.y;
				if (temp_col) {
					map->ai_Matrix[ai_id[j]][i] = map->ai_Matrix[ai_id[j]][--map->ai_counter[ai_id[j]]];
					g->isAlive = 0;
					free(g);
				}

				break;
			}
			case shroom: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];
				if (g->coordinate.x >= mario->coordinates.x - SCREEN_WIDTH - g->dimension.x && g->coordinate.x <= mario->coordinates.x + SCREEN_WIDTH) {
					int temp_col = detectGravityCollideAi(map, g->coordinate, g->dimension, g->speed);
					if (temp_col > 0) {
						g->speed.y = 0;
						g->coordinate.y = temp_col - g->dimension.y;
					}
					else g->speed.y += G;

					temp_col = detectSideCollideAi(map, g->coordinate, g->dimension, g->speed);
					if (temp_col > 2)
						g->speed.x *= -1;
					g->time++;
					if (g->time % 8 == 0)
						if (g->animation_Stage == 0) g->animation_Stage = 1;
						else g->animation_Stage = 0;
					g->coordinate.x += g->speed.x;
					g->coordinate.y += g->speed.y;
				}
				break;
			}
			case star: {
				ai_Shroom *g = (ai_Shroom *)map->ai_Matrix[ai_id[j]][i];

				break;
			}
			case turtle: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				if (g->coordinate.x >= mario->coordinates.x - SCREEN_WIDTH - g->dimension.x && g->coordinate.x <= mario->coordinates.x + SCREEN_WIDTH) {
					int temp_col = detectGravityCollideAi(map, g->coordinate, g->dimension, g->speed);				
					if (temp_col > 0) {
						g->speed.y = 0;
						g->coordinate.y = temp_col - g->dimension.y;
					}
					else g->speed.y += G;

					temp_col = detectSideCollideAi(map, g->coordinate, g->dimension, g->speed);
					if (temp_col > 2) {
						g->speed.x *= -1;
						g->type = 0;
						if (g->animation_Stage != 4)
							if(g->animation_Stage==0 || g->animation_Stage==1)
							g->animation_Stage = 2;
							else g->animation_Stage = 0;
					}
					else {
						g->time++;
						if (g->time % 8 == 0 && g->isAlive!=0)
								if (g->animation_Stage == 0) g->animation_Stage = 1;
								else if (g->animation_Stage == 1) g->animation_Stage = 0;
								else if (g->animation_Stage == 2) g->animation_Stage = 3;
								else g->animation_Stage = 2;
					}
					if (g->speed.x == 0 && g->speed.y == 0)
						g->type = 1;
					static int turtle_timer = 0;
					if (g->isAlive == 0) {
						turtle_timer++;
						turtle_timer %= TURTLE_TIMER + 1;
					}

					if (g->isAlive == 0 && g->speed.x != 0) {
						projectileCollision(map, g->coordinate, g->dimension, g->speed);

						if (turtle_timer == TURTLE_TIMER)
							if (g->speed.x > 0) {
								g->speed.x -= TURTLE_ACCELERATION;
							}
							else g->speed.x += TURTLE_ACCELERATION;

					}
					g->coordinate.x += g->speed.x;
					g->coordinate.y += g->speed.y;
				}
				break;
			}
			case devil: {
				ai_Devil *g = (ai_Devil *)map->ai_Matrix[ai_id[j]][i];
				if (g->coordinate.x >= mario->coordinates.x - SCREEN_WIDTH  - g->dimension.x && g->coordinate.x <= mario->coordinates.x + SCREEN_WIDTH ) {
					int temp_col = detectGravityCollideAi(map, g->coordinate, g->dimension, g->speed);
					if (temp_col > 0) {
						g->speed.y = 0;
						g->coordinate.y = temp_col - g->dimension.y;
					}
					else g->speed.y += G;

					temp_col = detectSideCollideAi(map, g->coordinate, g->dimension, g->speed);
					if (temp_col > 2)
						g->speed.x *= -1;
					g->time++;
					if (g->time % 8 == 0)
						if (g->animation_Stage == 0) g->animation_Stage = 1;
						else g->animation_Stage = 0;
					g->coordinate.x += g->speed.x;
					g->coordinate.y += g->speed.y;
				}
				break;
			}
			case plantie: {
				ai_Plantie *g = (ai_Plantie *)map->ai_Matrix[ai_id[j]][i];
				if (g->coordinate.x >= mario->coordinates.x - SCREEN_WIDTH - g->dimension.x && g->coordinate.x <= mario->coordinates.x + SCREEN_WIDTH) {
					if (g->timer_Sleep != 0)
						g->timer_Sleep--;
					else {
						if (g->isAlive == 0) {
							g->isAlive = 1;
							g->coordinate.y -= 30;
						}
						if (-g->additional_Height >= 2 * blok.y) {
							g->speed.y *= -1;
						}
						else if (-g->additional_Height < 0) {
							g->speed.y *= -1;
							g->timer_Sleep = PLANTIE_SLEEP;
							g->isAlive = 0;
							g->coordinate.y += 30;
						}
						g->coordinate.y += g->speed.y;
						g->additional_Height += g->speed.y;
					}
				}
				
				break;
			}
			default:
				break;
			}

		}
}