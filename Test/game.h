/**
*  Game.h
*  Authors:
*  Date 4/2/2016
*  Description :
Main Game Loop goes here. run() should take in a list of players from steam, as well as their appropriate class
configurations.

*/


#pragma once

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED



#include "include\SquadIO.h"
#include "include\network\NetIncludes.h"
#include "include\LogManager.h"
#include "include\AudioManager.h"
#include "include\EngineObject.h"
#include "include\ResourceManager.h"
#include "include\RenderManager.h"
#include "include\RenderResource.h"
#include "include\sdl2\SDL.h"
#include "include\sdl2\SDL_image.h"
#include "include\AnimationLibrary.h"
#include <iostream>
#include <tchar.h>


#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <list>



#include "GameObject.h"
#include "GameWorld.h"
#include "PlayerObjectFactory.h"
#include "MinionObjectFactory.h"
#include "FeatherObjectFactory.h"
#include "UIObjectFactory.h"
#include "PlatformObjectFactory.h"
#include "PhysicsListener.h"

#include "SystemInputUpdater.h"
#include "SystemRenderUpdater.h"
#include "SystemGameObjectQueue.h"
#include "SystemUIObjectQueue.h"
#include "SystemLogicUpdater.h"
#include "SystemNetworkUpdater.h"
#include "SystemPhysicsUpdater.h"
#include "SystemUIUpdater.h"
#include "lobby.h"
#include "start.h"

class game
{
public:
	game();
	~game();

	int run();
	// int run ( std::list playerlist);


};

#endif