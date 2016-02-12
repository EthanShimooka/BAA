#pragma once
#include "include\SquadIO.h"
#include "include\LogManager.h"
#include "include\EngineObject.h"
#include "include\ResourceManager.h"
#include "include\RenderManager.h"
#include "include\RenderResource.h"
#include "include\sdl2\SDL.h"
#include "include\sdl2\SDL_image.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>


#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <math.h>
#include <list>

class test
{
public:

	test();
	~test();

	void render();
	void update();
	long double getCurrentTime();

};

