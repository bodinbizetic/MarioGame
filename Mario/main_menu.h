#ifndef main_menu_h
#define main_menu_h
#include <SDL.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

#define MENU_WIDTH 600
#define MENU_HEIGHT 480
#define NUMBER_OF_OPTIONS 5
#define OPTION_HEIGHT 80
#define OPTION_WIDTH 300

int show_menu(SDL_Window *window, SDL_Renderer *renderer);
void pause_game();
#endif 