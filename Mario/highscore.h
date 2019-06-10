#ifndef settings_h
#define settings_h
#define MAX_NAME 13
#define MAP_SDL_LETTERS(x) ((x) - SDLK_a + 'a')
#define MAP_SDL_NUMBERS(x) ((x) - SDLK_0 + '0')
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

#endif