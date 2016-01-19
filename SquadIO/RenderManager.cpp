#pragma once
#include "RenderManager.h"
#include "SDL.h"
#include <list>

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

bool RenderManager::update(){
	//check to see if escape key was pushed (paused) or 
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT: return false;
			case SDL_KEYDOWN:{
				if (event.key.keysym.sym == SDLK_ESCAPE)return false;
			}
		}
	}
	//clear screen
	SDL_FillRect(renderWindow, 0, SDL_MapRGB(renderWindow->format, 0, 0, 0));
	renderAllObjects();
	SDL_RendererFlip(renderWindow);
	return true;
}

void RenderManager::renderAllObjects(){
	//NOTE: this list might need to be changed to be pointers
	std::list<SDLRenderObject>::iterator iter;
	for (iter = renderObjects.begin(); iter != renderObjects.end(); iter++){
		if (iter->visible){
			iter->update();
			SDL_Rect pos;
			pos.x = int(iter->posX);
			pos.y = int(iter->posY);
			SDL_BlitSurface(iter->renderResource->mSurface, &iter->renderRect, renderWindow, &pos);
		}
	}
}