#pragma once
#include "include\RenderManager.h"


RenderManager RenderManager::renderManager;

RenderManager::RenderManager(){
	ID = 1;
}

RenderManager* RenderManager::getRenderManager(){
	return &renderManager;
}

SDL_Renderer* RenderManager::getRenderManagerRenderer(){
	RenderManager* manager = &renderManager;
	return manager->renderer;
}

bool RenderManager::init(unsigned int width, unsigned int height, bool fullScreen, char* WindowTitle){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "Error: Could not initialize SDL Render" << std::endl;
		return false;
	}
	else if (!fullScreen){
		std::cout << "not fullscreen" << std::endl;
	}
	//renderWindow = SDL_CreateWindow(WindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, fullScreen);
	SDL_CreateWindowAndRenderer(width, height, fullScreen, &renderWindow, &renderer);
	if (!renderWindow){
		//there was an error creating the window
		return false;
	}
	//Get window surface
	zoom = 1;
	minZoom = .05;
	cameraPoint = {0,0};
	SDL_Surface* screenSurface = SDL_GetWindowSurface(renderWindow);
	//Fill the surface white 
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0 ) ); 

	return true;
}

void RenderManager::update(){
	//check to see if escape key was pushed (paused) or 
	/*SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT: return false;
			case SDL_KEYDOWN:{
				if (event.key.keysym.sym == SDLK_ESCAPE)return false;
			}
		}
	}*/
	//clear screen
	windowSurface = SDL_GetWindowSurface(renderWindow);

	//Fill the surface white
	SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0, 0, 0));
	SDL_RenderClear(renderer);
	renderBackground();
	SDL_UpdateWindowSurface(renderWindow);
	//interate through renderables, and generate the current frame
	renderAllObjects();

	//
	
	SDL_RenderPresent(renderer);
	//TODO: Remove delay
	SDL_Delay(20);
	//This next line is only still here to act as a restore point
	//SDL_RendererFlip(renderWindow);

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
/*void RenderManager::setBackground(SDL_Texture* bg){
	if (bg){
		SDL_Surface* tempSurface = SDL_ConvertSurface(bg, bg->format,bg->flags);
		//SDL_BlitSurface(bg, NULL,tempSurface, NULL);
		if (tempSurface){
			SDL_FreeSurface(background);
			background = tempSurface;
		}
	}
	else{
		printf("Unable to copy the image %s! SDL_image Error: %s\n", IMG_GetError());
	}
}*/
void RenderManager::setBackground(std::string filename){
	//background = bg;
	std::string path = "resources/" + filename;
	std::cout<<path<<std::endl;
	SDL_Surface *tempSurface = IMG_Load(path.c_str());
	//mTexture = SDL_CreateTextureFromSurface(RenderManager::getRenderManagerRenderer(), tempSurface);
	SDL_Texture*tempTexture = SDL_CreateTextureFromSurface(RenderManager::getRenderManagerRenderer(), tempSurface);
	if (tempSurface){
		//free old buffer
		SDL_FreeSurface(tempSurface);
		if (tempTexture){
			if (background){
				SDL_DestroyTexture(background);
			}
			background = tempTexture;
		}
	}
	else{
		printf("Unable to load the image %s! SDL_image Error: %s\n", filename, IMG_GetError());
	}
}
void RenderManager::renderBackground(){
	//to avoid using a null background
	if (zoom < minZoom){ zoom = minZoom; }
	if (background){
		//maybe invert z = 1/zoom
		float z = 1/zoom;
		SDL_Rect dstrect;
		SDL_QueryTexture(background, NULL, NULL, &dstrect.w, &dstrect.h);
		//offset is for how the background tiles tile. it tells you the offset of the centermost tile 
		//it should give the illusion that the tiling begins at (0,0)
		float centerOffsetX = windowSurface->w / 2 - (int(cameraPoint.x) % dstrect.w)*z;
		float centerOffsetY = windowSurface->h / 2 - (int(cameraPoint.y) % dstrect.h)*z;
		dstrect.w *= z;//stretched due to zoom
		dstrect.h *= z;
		//tiling the image
		for (float x = centerOffsetX - ceil(centerOffsetX / (dstrect.w))*dstrect.w; x < windowSurface->w; x += dstrect.w){
			//x = the offset - the number of times the background needs to be repeated from the offset point and (0,0) on the window and keep the background static
			dstrect.x = round(x);//rounding to make it less jagged
			for (float y = centerOffsetY - ceil(centerOffsetY / (dstrect.h))*dstrect.h; y < windowSurface->h; y += dstrect.h){
				dstrect.y = round(y);
				SDL_RenderCopy(renderer, background, NULL, &dstrect);
			}
		}
	}
}

void RenderManager::renderAllObjects(){
	//NOTE: this list might need to be changed to be pointers
	//NOTE: May have to be based on a subset of renderobjects, not all of them
	if (zoom < minZoom){ zoom = minZoom; }
	float z = 1/zoom; //maybe invert
	std::list<SDLRenderObject*>::iterator iter;
	for (iter = renderObjects.begin(); iter != renderObjects.end(); iter++){
		if ((*iter)->visible){
			//this update is a SpriteObject specific method for spritesheets
			//(*iter)->update();
			SDL_Rect pos;
			pos.x = int((((*iter)->posX) - cameraPoint.x - (*iter)->renderRect.w / 2)*z + windowSurface->w / 2);
			pos.y = int((((*iter)->posY) - cameraPoint.y - (*iter)->renderRect.h / 2)*z + windowSurface->h / 2);
			pos.w = (*iter)->renderRect.w*z;
			pos.h = (*iter)->renderRect.h*z;
			/*auto src = (*iter)->renderResource->mSurface;
			auto srcrect = &(*iter)->renderRect;
			auto dst = windowSurface;
			auto dstrect = &pos;
			SDL_BlitSurface(src, srcrect, dst, dstrect);*/

			//TODO: replace NULL parameters with meaningful SDL_Rects
			//uses the object's anchor value as a general position, and multiplies it with the proper w and h
			SDL_Point anchor = { int((*iter)->renderRect.w*z*(*iter)->anchor.x), int((*iter)->renderRect.h*z*(*iter)->anchor.y) };
			SDL_RendererFlip flip = SDL_FLIP_NONE;
			if ((*iter)->flipH){ flip = SDL_FLIP_HORIZONTAL; }
			if ((*iter)->flipV){ flip = SDL_FLIP_VERTICAL; }
			if ((*iter)->flipH && (*iter)->flipV){ flip = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL); }
			//SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
			SDL_RenderCopyEx(renderer, (*iter)->renderResource->mTexture, NULL, &pos, (*iter)->rotation, &anchor, flip);
		}
	}
}

void RenderManager::free(){
	SDL_DestroyWindow(renderWindow);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(windowSurface);
	//TODO: this obviously isn't a complete implementation of the free function
	std::list<SDLRenderObject*>::iterator iter;
	for (iter = renderObjects.begin(); iter != renderObjects.end(); iter++){
		(*iter)->renderResource->unload();
	}
}

bool RenderManager::isReadyToQuit(){
	//returns whether or not an SDL_QUIT event has been made
	//When we want to quit, we can push a SDL_QUIT from anywhere,
	//and the rendermanager will see it here and initiate program shutdown
	std::list<SDL_Event*>events;
	std::list<SDL_Event*>::iterator iter;
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		events.push_back(&event);
		for (iter = events.begin(); iter != events.end(); iter++){
			switch ((*iter)->type){
				case SDL_QUIT: return true;
					//This case is just for debugging purposes for the moment
				case SDL_KEYDOWN:{
						 if (event.key.keysym.sym == SDLK_ESCAPE)return true;
				}
			}
		}
	}

	//No quit event was found, so put everything back into the event queue
	while (events.size() > 0){
		SDL_PushEvent(events.front());
		events.pop_front();
	}
	return false;
}