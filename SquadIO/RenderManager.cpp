#pragma once
#include "RenderManager.h"

using namespace std;

RenderManager RenderManager::renderManager;

RenderManager::RenderManager(){}

RenderManager* RenderManager::getRenderManager()
{
	return &renderManager;
}

bool RenderManager::init(unsigned int width, unsigned int height, bool fullScreen, char* WindowTitle){
	SDL_Window* renderWindow = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "Error: Could not initialize SDL Render" << endl;
		return false;
	}
	else if (fullScreen){
		//NOTE: hardcoded window to appear at (0,0) on desktop for now
		renderWindow = SDL_CreateWindow(WindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, fullScreen);
		if (!renderWindow){
			//there was an error creating the window
			return false;
		}
		//would be nice to have a variable here to get init data for debugging
	}
	else {
		cout << "not full" << endl;
		renderWindow = SDL_CreateWindow(WindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, fullScreen);
		if (!renderWindow){
			//there was an error creating the window
			return false;
		}
	}
	//Get window surface
	screenSurface = SDL_GetWindowSurface(renderWindow);
	//Fill the surface white 
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) ); 
	//Update the surface 
	SDL_UpdateWindowSurface(renderWindow);
	SDL_Delay(2000);
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
//TODO: this function is necessary, but we need a resource manager first
gameResource* RenderManager::loadResourceFromXML(tinyxml2::XMLElement *elem){
	if (elem){
		//TODO: book says to use RenderResource constructor
		gameResource* resource = new gameResource(); //this compiles atleast
		//gameResource* resource = new RenderResource();
		for (const tinyxml2::XMLAttribute* elementAttrib = elem->FirstAttribute(); elementAttrib; elementAttrib = elementAttrib->Next()){
			string AttribName = elementAttrib->Name();
			string AttribValue = elementAttrib->Value();
			if (AttribName == "UID"){
				resource->m_ResourceID = atoi(AttribValue.c_str());
			}
			if (AttribName == "filename"){
				resource->m_Filename = AttribValue;
			}
			if (AttribName == "scenescope"){
				resource->m_Scope = atoi(AttribValue.c_str());
			}
		}
		return resource;
	}
	return NULL;
}


void RenderManager::renderAllObjects(){
	//NOTE: this list might need to be changed to be pointers
	std::list<SDLRenderObject*>::iterator iter;
	for (iter = renderObjects.begin(); iter != renderObjects.end(); iter++){
		if ((*iter)->visible){
			(*iter)->update();
			SDL_Rect pos;
			pos.x = int((*iter)->posX);
			pos.y = int((*iter)->posY);
			SDL_BlitSurface((*iter)->renderResource->mSurface, &(*iter)->renderRect, renderWindow, &pos);
		}
	}
}