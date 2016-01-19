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
// TODO: import the tinyxml library
//#include "TimyXML.h"

class RenderResource{// : public cResource{ TODO: add this inheritance in when resource manager is done
private:
protected:
public:
	SDL_Surface *mSurface;

	~RenderResource();
	void load();
	void unload();
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
	void setResourceObject(RenderResource *source);
	virtual void update(){};
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
	unsigned int frameWidth;
	unsigned int frameHeight;

	void update();
	void play();
	void stop();
	void setFrameRect(unsigned int frameNumber);
	SpriteObject();
};

class RenderManager : public EngineObject {
private:
protected:
	RenderManager();
	static RenderManager renderManager;
public:
	SQUADIO_API static RenderManager * GetLogManager();
	static RenderManager* getRenderManager();
	SDL_Surface* renderWindow;
	std::stringstream videoInfo;
	bool init(unsigned int Width = 800, unsigned int Height = 600, bool fullScreen = false, char* WindowTitle = 0);
	void free();
	bool update();
	void toggleFullScreen();
	//cResource* loadResourceFromXML(TiXmlElement* element);
	void renderAllObjects();
	std::list<SDLRenderObject> renderObjects;
	~RenderManager();
};

#endif //SDL2DRENDERMANAGER_H_INCLUDED