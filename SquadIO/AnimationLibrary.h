#pragma once
#ifndef ANIMATIONMANAGER_H_INCLUDED
#define ANIMATIONMANAGER_H_INCLUDED


#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include "include\RenderManager.h"

typedef float(*ease_function)(float);

SQUADIO_API float ease_linear(float i);
SQUADIO_API float ease_QuadIn(float i);
SQUADIO_API float ease_QuadOut(float i);
SQUADIO_API float ease_QuadInOut(float i);
SQUADIO_API std::function<float(float)> getBezier(float x0, float x1, float x2, float x3);
SQUADIO_API std::function<void(float)> rotateTransform(SDLRenderObject* obj, double start, double end);
SQUADIO_API std::function<void(float)> moveCircArc(SDLRenderObject* obj, int centerx, int centery, double rad, double start_angle, double end_angle);
SQUADIO_API std::function<void(float)> moveEllipseArc(SDLRenderObject* obj, int centerx, int centery, double height, double width, double start_angle, double end_angle);
//float bezier()
struct motion{
	std::function<void(float)> trans;
	std::function<float(float)> ease;
	int start; //a value from 0 to 1
	int duration; //a value from 1-start to 0
};
struct animation{
	list <motion> motions;
	bool animate(float i){
		for (auto mot = motions.begin(); mot != motions.end(); mot++){
			float place;
			if (i >= mot->start + mot->duration){ place = 1.0; }//so durations of 0 are assumed to have finished
			else if (i < mot->start)			{ place = 0.0; }
			else								{ place = (i - mot->start) / mot->duration; }
			mot->trans(mot->ease(place));//apply transformation, place should be between 0 and 1
		}
		return ((i>1.0) || (i<0.0));
	}
};

#endif