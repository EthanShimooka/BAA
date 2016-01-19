#pragma once
#include "RenderManager.h"
#include "SDL.h"

using namespace std;

RenderManager RenderManager::renderManager;

RenderManager::RenderManager(){}

RenderManager* RenderManager::getRenderManager()
{
	return &renderManager;
}

bool RenderManager::init(unsigned int width, unsigned int height, bool fullScreen, char* WindowTitle){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "Error: Could not initialize SDL Render" << endl;
		return false;
	}
	if (fullScreen){
		//NOTE: hardcoded window to appear at (0,0) on desktop for now
		SDL_Window* renderWindow = SDL_CreateWindow(WindowTitle, 0, 0, width, height, fullScreen);
		if (!renderWindow){
			//there was an error creating the window
			return false;
		}
		//would be nice to have a variable here to get init data for debugging
	}
	return true;
}
