#pragma once
#ifndef SDL2DRENDERMANAGER_H_INCLUDED
#define SDL2DRENDERMANAGER_H_INCLUDED

//throw macro to throw exceptions
#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(errorNum, errorDesc) throw cException(errorNum, errorDesc, __FILE__, __LINE__);
#endif

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us
#include "EngineObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <math.h>
#include <list>
#include "gameResource.h"
#include "Inc/Tinyxml2.h"  //XML library

// TODO: import the tinyxml library
//#include "TimyXML.h"

class RenderResource : public gameResource { 
private:
protected:
public:
	SDL_Surface *mSurface;

	~RenderResource();
	SQUADIO_API void load();
	SQUADIO_API void unload();
	RenderResource();
};

class SDLRenderObject : public EngineObject{
private:
protected:
public:
	RenderResource *renderResource;
	SDL_Rect renderRect;
	float posX;
	float posY;
	bool visible;
	SDL_Color colorKey;
	bool colorKeyEnabled;
	SDLRenderObject();
	SQUADIO_API void setResourceObject(RenderResource *source);
	SQUADIO_API virtual void update(){};
};

class SpriteObject : public SDLRenderObject{
private:
protected:
	DWORD timeLastFrame;

public:
	unsigned int totalFrames;
	unsigned int framesPerRow;
	unsigned int framesPerColumn;
	unsigned int currentFrame;
	unsigned int startFrame;
	float spriteSpeed;
	unsigned int frameWidth;
	unsigned int frameHeight;

	SQUADIO_API void update();
	SQUADIO_API void play();
	SQUADIO_API void stop();
	SQUADIO_API void setFrameRect(unsigned int frameNumber);
	SpriteObject();
};

class RenderManager : public EngineObject {
private:
protected:
	RenderManager();
	virtual ~RenderManager(){}
	static RenderManager renderManager;
public:
	SQUADIO_API static RenderManager* getRenderManager();
	SDL_Surface* renderWindow;
	std::stringstream videoInfo;
	SQUADIO_API bool init(unsigned int width = 800, unsigned int height = 600, bool fullScreen = false, char* WindowTitle = 0);
	SQUADIO_API void free();
	SQUADIO_API bool update();
	SQUADIO_API void toggleFullScreen();
	SQUADIO_API gameResource* loadResourceFromXML(tinyxml2::XMLElement* element);
	SQUADIO_API void renderAllObjects();
	//NOTE: this list might need to be changed to be pointers
	std::list<SDLRenderObject*> renderObjects;
};

#endif SDL2DRENDERMANAGER_H_INCLUDED