#ifndef main_menu_h
#define main_menu_h
#include <SDL.h>
#include <SDL_ttf.h>

/*!	\file main_menu.c
*	\brief Contains declarations and constants for main_menu
*/

/*!
*	\brief Width of the window
*/
#define SCREEN_WIDTH 1024

/*!
*	\brief Height of the window
*/
#define SCREEN_HEIGHT 720

/*!
*	\brief Width of the options menu
*/
#define MENU_WIDTH 600

/*!
*	\brief Height of the options menu
*/
#define MENU_HEIGHT 480

/*!
*	\brief Number of options menu options
*/
#define NUMBER_OF_OPTIONS 5

/*!
*	\brief Height of the single option
*/
#define OPTION_HEIGHT 80

/*!
*	\brief Width of the single option
*/
#define OPTION_WIDTH 300

/*!
*	\brief Function that show main menu on the screen
*	\param window Address of current active SDL_Window
*	\param renderer Address of main SDL_Renderer
*	\return returns id of selected menu option
*/

int show_menu(SDL_Window *window, SDL_Renderer *renderer);
void pause_game();
#endif 