#ifndef settings_h
#define settings_h

/*!	\file highscore.h
*	\brief Contains declarations and constants for highscore.h
*/

/*!
*	\brief Maximum number of letters in name
*/
#define MAX_NAME 13

/*!
*	\brief Maps SDLK letter constants to ASCII letter constants
*/
#define MAP_SDL_LETTERS(x) ((x) - SDLK_a + 'a')

/*!
*	\brief Maps SDLK number constants to ASCII number constants
*/
#define MAP_SDL_NUMBERS(x) ((x) - SDLK_0 + '0')

/*!
*	\brief Struct containing needed variables for final score textures
*/
typedef struct finalScoreTexturesStruct {
	SDL_Texture * typeInYourNameTexture;
	SDL_Texture * characterTextures[26];
	SDL_Texture * blankTexture;
}FinalScoreTextures;

static FinalScoreTextures finalScoreTextureManager;
int showHighscore(SDL_Renderer *renderer);
void finalScoreScreen(int currScore, char * name, int * nameSave, SDL_Renderer *renderer);
void initFinalScoreTextures(SDL_Renderer *renderer);
void destroyFinalScoreTextures();
void updateHighscore(int score, char *name, int a);

#endif