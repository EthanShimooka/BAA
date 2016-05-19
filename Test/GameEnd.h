#pragma once
#ifndef GAMEEND_H_INCLUDED
#define GAMEEND_H_INCLUDED

#include "main.h"

class GameEnd
{
public:
	/// Constructor
	GameEnd(int localTeam, int purpleHealth, int yellowHealth) :
		localTeam(localTeam), purpleHealth(purpleHealth), yellowHealth(yellowHealth) {}
	/// Destructor
	~GameEnd();
	/// Displays respective win/loss screen then restarts GameSession
	int runGameEnd();
	/// For drawing win/loss text
	SDLRenderObject* textHUD;

private:
	int localTeam;
	int purpleHealth, yellowHealth;
};

#endif