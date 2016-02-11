#pragma once
#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED


#include "include\SceneManager.h"

class Square
{
private:
protected:
public:

	~Square();
	float x;
	float y;
	int ID;

	SDLRenderObject* obj;

	void update();  //dontg know if this works ab

	Square(){
	obj = nullptr;
	x = 50.0;
	y = 50.0;
}

};





#endif