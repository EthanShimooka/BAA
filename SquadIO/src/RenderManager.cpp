#pragma once
#include "include\RenderManager.h"


RenderManager RenderManager::renderManager;

RenderManager::RenderManager(){
	ID = 1;
}

RenderManager* RenderManager::getRenderManager()
{
	return &renderManager;
}

bool RenderManager::init(unsigned int width, unsigned int height, bool fullScreen, char* WindowTitle){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "Error: Could not initialize SDL Render" << std::endl;
		return false;
	}
	else if (!fullScreen){
		std::cout << "not fullscreen" << std::endl;
	}
	renderWindow = SDL_CreateWindow(WindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, fullScreen);
	if (!renderWindow){
		//there was an error creating the window
		return false;
	}
	//Get window surface
	SDL_Surface* screenSurface = SDL_GetWindowSurface(renderWindow);
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
	windowSurface = SDL_GetWindowSurface(renderWindow);

	//Fill the surface white
	SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF));
	

	//interate through renderables, and generate the current frame
	renderAllObjects();

	//
	SDL_UpdateWindowSurface(renderWindow);

	//This next line is only still here to act as a restore point
	//SDL_RendererFlip(renderWindow);
	
	return true;
}
//TODO: this function is necessary, but we need a resource manager first
gameResource* RenderManager::loadResourceFromXML(tinyxml2::XMLElement *elem){
	if (elem){
		
		gameResource* resource = new RenderResource(); // This is uber important

		for (const tinyxml2::XMLAttribute* elementAttrib = elem->FirstAttribute(); elementAttrib; elementAttrib = elementAttrib->Next()){
			std::string AttribName = elementAttrib->Name();
			std::string AttribValue = elementAttrib->Value();
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
			SDL_BlitSurface((*iter)->renderResource->mSurface, &(*iter)->renderRect, windowSurface, &pos);
		}
	}
}

void RenderManager::free(){
	SDL_DestroyWindow(renderWindow);
	SDL_FreeSurface(windowSurface);

	//TODO: this obviously isn't a complete implementation of the free function
}