#pragma once
#ifndef GAMEEND_H_INCLUDED
#define GAMEEND_H_INCLUDED

#include "GameSession.h"

class GameEnd
{
public:
	/// Constructor
	GameEnd();
	/// Destructor
	~GameEnd();
	/// Displays respective win/loss screen then restarts GameSession
	void runGameEnd(int localTeam, GameObject* leftBase, GameObject* rightBase);
	/// For drawing win/loss text
	SDLRenderObject* textHUD;
};

#endif