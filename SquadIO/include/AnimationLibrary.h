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
SQUADIO_API std::function<void(float)> moveCircArc(SDLRenderObject* obj, float centerx, float centery, double radius, double start_angle, double end_angle);
SQUADIO_API std::function<void(float)> moveEllipseArc(SDLRenderObject* obj, float centerx, float centery, double height, double width, double start_angle, double end_angle);
SQUADIO_API std::function<void(float)> moveLinearXY(SDLRenderObject* obj, float startx, float starty, float endx, float endy);
SQUADIO_API std::function<void(float)> moveLinearX(SDLRenderObject* obj, float startx,float endx);
SQUADIO_API std::function<void(float)> moveLinearY(SDLRenderObject* obj, float starty, float endy);
SQUADIO_API std::function<void(float)> moveLinearZ(SDLRenderObject* obj, float startz, float endz);
SQUADIO_API std::function<void(float)> moveLinearXYZ(SDLRenderObject* obj, float startx, float starty, float startz, float endx, float endy, float endz);
SQUADIO_API std::function<void(float)> moveBezierX(std::function<float(float)> bezier, float startx, float endx);
SQUADIO_API std::function<void(float)> moveBezierY(std::function<float(float)> bezier, float starty, float endy);
SQUADIO_API std::function<void(float)> moveBezierZ(std::function<float(float)> bezier, float startz, float endz);
SQUADIO_API std::function<void(float)> moveBezierXY(std::function<float(float)> bezier, float startx, float starty, float endx, float endy);
SQUADIO_API std::function<void(float)> moveBezierXYZ(std::function<float(float)> bezier, float startx, float starty, float startz, float endx, float endy, float endz);
SQUADIO_API std::function<void(float)> keyframeJump(SDLRenderObject* obj,unsigned int frame);
SQUADIO_API std::function<void(float)> keyframeAnimate(SDLRenderObject* obj, unsigned int startFrame, unsigned int endFrame);

//float bezier()
struct motion{
	std::function<void(float)> trans;
	std::function<float(float)> ease;
	int start; //a value from 0 to 1
	int duration; //a value from 1-start to 0
};
SQUADIO_API motion makeMotion(std::function<void(float)> trans, int start, int duration, std::function<float(float)> ease = ease_linear);
class Animation{
	std::list <motion> motions;
public:
	SQUADIO_API Animation();
	SQUADIO_API Animation(float d, std::list<motion> m);
	SQUADIO_API ~Animation();
	unsigned int duration;
	SQUADIO_API float lengthConversion(int progress);
	SQUADIO_API bool animate(float i);
	SQUADIO_API void push(std::function<void(float)> trans, int start, int duration, std::function<float(float)> ease = ease_linear);
};

#endif