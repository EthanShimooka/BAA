#pragma once
#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED


#include "include\SceneManager.h"
#include "include\network\MemoryBitStream.h"

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
		x = 0.0;
		y = 0.0;
	}
	
	Square(float x, float y, int ID) : x(x), y(y), ID(ID){};

	void Write(OutputMemoryBitStream& outData);
	void Read(InputMemoryBitStream& data);
};





#endif