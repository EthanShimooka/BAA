#pragma once
#ifndef PLAYERUICOMPONENT_H_INCLUDED
#define PLAYERUICOMPONENT_H_INCLUDED
#include "UIComponent.h"
#include "PlayerComponentIncludes.h"
class PlayerUIComponent :
	public UIComponent
{
public:
	PlayerUIComponent(GameObject* player);
	~PlayerUIComponent();
	void Update();

	GameObject* gameObjectRef;

	SDLRenderObject* birdseedHUD;
	SDLRenderObject* chargeHUD;
	SDL_Rect defaultRect;
	SDL_Rect chargeRect;

	SDLRenderObject* timerHUD;

	int killHUDSize = 5;
	std::vector<std::pair<SDLRenderObject*, clock_t>> killHUD;

	/// adds to the queue of player kills
	void addToKillList(uint64_t killer, uint64_t victim);
	/// updates the queue of players
	void updateKillHUD();
	/// Boolean used to restrict input during gameplay. Only perform actions
	/// (i.e. jumping, shooting, moving) in game if true.

	/// Boolean used to say if this player is local or not
	//bool isLocal = false;
};
#endif
