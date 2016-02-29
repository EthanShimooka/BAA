#pragma once
#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "include\SquadIO.h"
#include "include\network\NetIncludes.h"
#include "include\LogManager.h"
#include "include\EngineObject.h"
#include "include\ResourceManager.h"
#include "include\RenderManager.h"
#include "include\RenderResource.h"
#include "include\ButtonManager.h"
#include "include\sdl2\SDL.h"
#include "include\sdl2\SDL_image.h"
<<<<<<< HEAD
#include "include\ButtonManager.h"
=======
#include "include\AnimationLibrary.h"
>>>>>>> 885913855ad500a2205f6813483d20ceaf9112cb
#include <iostream>
#include <tchar.h>


#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <list>

#include "GameObject.h"
#include "PlayerObjectFactory.h"
#include "MinionObjectFactory.h"
#include "FeatherObjectFactory.h"

#include "SystemInputUpdater.h"
#include "SystemRenderUpdater.h"
#include "SystemGameObjectQueue.h"
#include "SystemLogicUpdater.h"
#include "SystemNetworkUpdater.h"
#include "SystemPhysicsUpdater.h"

class test
{
public:

	test();
	~test();
};

#endif