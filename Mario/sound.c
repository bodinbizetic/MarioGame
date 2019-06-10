#include <Windows.h>
#include "all.h"

void playMainTheme() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
	PlaySound(TEXT("Zvuci/main_sound"), NULL, SND_LOOP | SND_ASYNC);
}

void playJump() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_jump"), NULL,SND_FILENAME || SND_ASYNC);
}

void playBreakBlock() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_breakblock"), NULL, SND_FILENAME || SND_ASYNC);
}

void playFlagPole() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_flagpole"), NULL, SND_FILENAME || SND_ASYNC);
}

void playMarioDie() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_mariodie"), NULL, SND_FILENAME || SND_ASYNC);
}

void playPowerUpAppears() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_powerup_appears"), NULL, SND_FILENAME || SND_ASYNC);
}

void playFireball() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_fireball"), NULL, SND_FILENAME || SND_ASYNC);
}

void playLoseLife() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_lost_a_life"), NULL, SND_FILENAME || SND_ASYNC);
}

void playPowerUp() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smw_power-up"), NULL, SND_FILENAME || SND_ASYNC);
}
void playEndGame(){
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_stage_clear"), NULL, SND_FILENAME || SND_ASYNC);
}

void playCoin() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/smb_coin"), NULL, SND_FILENAME || SND_ASYNC);
}

void playKill() {
	PlaySound(NULL, NULL, SND_ASYNC);
	if (music)
		PlaySound(TEXT("Zvuci/stomp"), NULL, SND_FILENAME || SND_ASYNC);
}