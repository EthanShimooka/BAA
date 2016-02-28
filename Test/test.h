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
#include "include\sdl2\SDL.h"
#include "include\sdl2\SDL_image.h"
#include "include\ButtonManager.h"
#include <iostream>
#include <tchar.h>


#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <vld.h>
#include <list>

<<<<<<< HEAD
#include "Square.h"
#include "InputListener.h"
=======
#include "GameObject.h"
#include "PlayerObjectFactory.h"
#include "MinionObjectFactory.h"

#include "SystemInputUpdater.h"
#include "SystemRenderUpdater.h"
#include "SystemGameObjectQueue.h"
#include "SystemLogicUpdater.h"
#include "SystemNetworkUpdater.h"
#include "SystemPhysicsUpdater.h"
>>>>>>> e92658aa754a438a0e316638606a678a7092268c

class test
{
public:

	test();
	~test();
};

#endif