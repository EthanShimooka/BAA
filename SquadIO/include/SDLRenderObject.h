#pragma once
#ifndef SDLRENDEROBJECT_H_INCLUDED
#define SDLRENDEROBJECT_H_INCLUDED

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us
#include "EngineObject.h"
#include "RenderResource.h"
#include "sdl2\SDL.h"
#include "sdl2\SDL_image.h"

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
//#include <Windows.h>
#include <math.h>
#include <list>

/**
* SDLRender Object is the renderable object that take a pointer to a renderResource (gameResource).
* SDLRenderObject also contains the renderable options that are fed into the renderManager.
*/
class SDLRenderObject : public EngineObject{
	//NOTE: when we make position, rotation, etc. private members we either need to call
	//the appropriate getter setter functions in RenderManager->renderAllObjects (doable) or use c++ friend feature (doable just different)
private:
protected:
public:
	struct anchor_point {
		float x;
		float y;
	} anchor;
	/// pointer to renderResource, which is derived from the RenderManager
	/// function loadfromXML()
	RenderResource *renderResource;
	/// SDL Rect object. contains the definition of a rectangle, 
	/// with the origin at the upper left.
	SDL_Rect renderRect;
	/// Object position on the x axis
	float posX;
	/// Object position on the y axis
	float posY;
	/// Object position on the z axis, perpendicular to the camera
	float posZ;
	/// Object's rotation
	double rotation;
	/// width multiplier
	float width;
	/// height multiplier
	float height;
	/// if flipped horizonatally
	bool flipH;
	/// if flipped verically
	bool flipV;
	/// if visible in the world
	bool visible;
	/// render the render rectangle
	bool ifRenderRect;
	/// render the image
	bool ifRenderImage;
	/// Total number of frames
	unsigned int frameTotal;
	/// current frame of the animation sheet
	unsigned int frameCurrent;
	/// number of frames arranged horizontally
	unsigned int frameWidth;
	/// number of frames arranged vertically
	unsigned int frameHeight;

	/// SDL color key paramater, usually should not be tampared with
	SDL_Color colorKey;
	/// A key to enable color filtering 
	bool colorKeyEnabled;
	///  Constructor?
	SQUADIO_API SDLRenderObject();
	/// Set a resource object from a Render Resource onto a SDL surface 
	SQUADIO_API void setResourceObject(RenderResource *source);
	/*SQUADIO_API SDL_Rect* getRenderRect();
	SQUADIO_API void resetRenderRect();
	SQUADIO_API SDL_Point getPosition();
	SQUADIO_API void setPosition(SDL_Point point);
	*/
	
	/// Get object's x position
	SQUADIO_API float getPosX();
	/// Get object's y position
	SQUADIO_API float getPosY();
	/// Get object's z position
	SQUADIO_API float getPosZ();
	/// Get object's position
	SQUADIO_API void getPos(float &x, float &y);
	/// Set object's position
	SQUADIO_API void setPos(float x, float y);
	SQUADIO_API void setPos(float x, float y,float z);
	SQUADIO_API void setPosZ(float z);

	/// Get object's width multiplier
	SQUADIO_API float getScaleX();
	/// Get object's height multiplier
	SQUADIO_API float getScaleY();
	/// Set object's width multiplier
	SQUADIO_API void setScaleX(float sx);
	/// Set object's height multiplier
	SQUADIO_API void setScaleY(float sy);
	/// Set object's size multiplier,
	SQUADIO_API void setScale(float s);
	/// Set object's size multiplier
	SQUADIO_API void setScale(float sx, float sy);


	/// Get object's width
	SQUADIO_API int getWidth();
	/// Get object's height
	SQUADIO_API int getHeight();
	/// Get object's width and height
	SQUADIO_API void getSize(int &w, int &h);
	/// Set object's width and height
	SQUADIO_API void setSize(int w, int h);
	/// Set object's position, width, and height
	SQUADIO_API void setRenderRect(SDL_Rect rect);
	/// Set object's position, width, and height
	SQUADIO_API void setRenderRect(int width,int height);

	/// Check if the object is visible
	SQUADIO_API bool isVisible();
	/// Set if the object is visible
	SQUADIO_API void setVisible(bool flag);
	SQUADIO_API void toggleVisible();

	/// Set if the object should be rendered as a rectangle
	SQUADIO_API void setIfRenderRect(bool flag);
	SQUADIO_API void toggleIfRenderRect();

	/// Set if the object should be rendered as an image
	SQUADIO_API void setIfRenderImage(bool flag);
	SQUADIO_API void toggleIfRenderImage();


	/// Get the object's rotation
	SQUADIO_API float getRotation();
	/// Set teh object's rotation
	SQUADIO_API void setRotation(float degrees);

	/// Check if the object is flipped horizontally
	SQUADIO_API bool isFlippedH();
	/// Check if the object is flipped vertically
	SQUADIO_API bool isFlippedV();
	/// Set if the object is flipped horizontally
	SQUADIO_API void setFlippedH(bool flag);
	SQUADIO_API void toggleFlippedH();
	/// Set if the object is flipped vertically
	SQUADIO_API void setFlippedV(bool flag);
	SQUADIO_API void toggleFlippedV();
	/// Get object's anchor xpoint relative to object's position and size
	SQUADIO_API float getAnchorX();
	/// Get object's anchor ypoint relative to object's position and size
	SQUADIO_API float getAnchorY();
	/// Get object's anchor point relative to object's position and size
	SQUADIO_API void getAnchor(float &a, float &b);
	/// Set object's anchor point relative to object's position and size
	SQUADIO_API void setAnchor(double a, double b);
	/// Set object's anchor point to the coordinate system
	SQUADIO_API void setAnchor(int x, int y);

	/// Get the object's current frame number
	SQUADIO_API unsigned int getCurrentFrame();
	/// Set the object's current frame number
	SQUADIO_API void setCurrentFrame(unsigned int f);
	/// Get the render rectangle based on current frame
	SQUADIO_API SDL_Rect getRenderRect();
	/// Set the number of frames on framesheet
	SQUADIO_API void setFrames(unsigned int w, unsigned int h, unsigned int totalFrames = 0);


	/// Abstract update function to be overriden.
	SQUADIO_API void setColorKey(unsigned int r, unsigned int g, unsigned int b);
	SQUADIO_API virtual void update(){};
	SDLRenderObject * parent;
	SQUADIO_API void setParent(SDLRenderObject * par);
	SQUADIO_API void unrender();
};

#endif SDLRENDEROBJECT_H_INCLUDED