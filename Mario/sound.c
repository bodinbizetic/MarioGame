#include <Windows.h>
#include "all.h"

/*!	\file sound.c
*	\brief Contains functions for playing sounds
*/

/*!	
*	\brief Plays main Mario theme
*/
void playMainTheme() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
	PlaySound(TEXT("Zvuci/main_sound"), NULL, SND_LOOP | SND_ASYNC);
}

/*!
*	\brief Plays Mario jump sfx
*/
void playJump() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_jump"), NULL,SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays sound of Mario breaking blocks
*/
void playBreakBlock() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_breakblock"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays sound of Mario sliding down the flag
*/
void playFlagPole() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_flagpole"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound of Mario dieing
*/
void playMarioDie() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_mariodie"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound when Shroom appears
*/
void playPowerUpAppears() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_powerup_appears"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound when Mario fires
*/
void playFireball() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_fireball"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound when Mario gets hit
*/
void playLoseLife() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_lost_a_life"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound of Mario picking up the shroom
*/
void playPowerUp() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_power-up"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound when Mario winning the game
*/
void playEndGame(){
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_stage_clear"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound of Mario hitting full hidden
*/
void playCoin() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_coin"), NULL, SND_FILENAME || SND_ASYNC);
}

/*!
*	\brief Plays the sound when Mario kill enemie
*/
void playKill() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/stomp"), NULL, SND_FILENAME || SND_ASYNC);
}