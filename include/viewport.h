#pragma once
#include "gamestructs.h"

void CalculateViewportpos(viewport &viewport, player player1, player player2);

void CalculateViewportSize(viewport &viewport, player player1, player player2);

void CalculateScale(viewport &viewport);

void CorrectViewport(viewport &viewport, player player1, player player2);

void LockViewportToLowestPlayer(viewport &viewport, player player1, player player2);

void SetYCameraOffset(stage &s, viewport &v);

void UpdateViewport(viewport &viewport, player player1, player player2, stage s);