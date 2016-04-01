#pragma once
#ifndef LOBBY_H
#define LOBBY_H

#include "main.h"
#include "UIObject.h"
#include "WorldObjectFactory.h"
// Component Includes
#include "Component.h"
#include "UIRenderComponent.h"
#include "UIInputComponent.h"
#include "UIComponent.h"

class Lobby
{
public:
	Lobby();
	~Lobby();

	void runLobby();
};

#endif