#pragma once
#include "gamestructs.h"

void SFX_player2walk(player &player2);
void SFX_player1walk(player &player1);
void SFX_player2land(player &player2);
void SFX_player1land(player &player1);
void SFX_player2getshit(player &player2);
void SFX_player1getshit(player &player1);
void SFX_player2death(player &player2);
void SFX_player1death(player &player1);
void SFX_jump(player &player1);
void SFX_parry(player &player2);
void SFX_entrance(Mix_Chunk* entrancesfx);