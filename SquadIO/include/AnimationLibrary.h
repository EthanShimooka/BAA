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
SQUADIO_API std::function<float(float)> getBezierTracking(float x0, float x1, float x2, float * x3);
SQUADIO_API std::function<float(float)> getBezierTracking(float x0, float x1, float x2, std::function<float(void)> x3);
SQUADIO_API std::function<void(float)> rotateTransform(SDLRenderObject* obj, double start, double end);
SQUADIO_API std::function<void(float)> rescaleTransform(SDLRenderObject* obj, double start, double end);
SQUADIO_API std::function<void(float)> rescaleXTransform(SDLRenderObject* obj, double start, double end);
SQUADIO_API std::function<void(float)> rescaleYTransform(SDLRenderObject* obj, double start, double end);
SQUADIO_API std::function<void(float)> moveCircArc(SDLRenderObject* obj, float centerx, float centery, double radius, double start_angle, double end_angle);
SQUADIO_API std::function<void(float)> moveEllipseArc(SDLRenderObject* obj, float centerx, float centery, double height, double width, double start_angle, double end_angle);
SQUADIO_API std::function<void(float)> moveLinearXY(SDLRenderObject* obj, float startx, float starty, float endx, float endy);
SQUADIO_API std::function<void(float)> moveLinearX(SDLRenderObject* obj, float startx,float endx);
SQUADIO_API std::function<void(float)> moveLinearY(SDLRenderObject* obj, float starty, float endy);
SQUADIO_API std::function<void(float)> moveLinearZ(SDLRenderObject* obj, float startz, float endz);
SQUADIO_API std::function<void(float)> transformFlipH(SDLRenderObject* obj, bool trans);
SQUADIO_API std::function<void(float)> transformFlipV(SDLRenderObject* obj, bool trans);
SQUADIO_API std::function<void(float)> resizeSquareTransform(SDLRenderObject* obj, float start,float end);

SQUADIO_API std::function<void(float)> moveLinearXYZ(SDLRenderObject* obj, float startx, float starty, float startz, float endx, float endy, float endz);
SQUADIO_API std::function<void(float)> moveBezierX(SDLRenderObject* obj,std::function<float(float)> bezierX);
SQUADIO_API std::function<void(float)> moveBezierY(SDLRenderObject* obj,std::function<float(float)> bezierY);
SQUADIO_API std::function<void(float)> moveBezierZ(SDLRenderObject* obj, std::function<float(float)> bezierZ);
SQUADIO_API std::function<void(float)> moveBezierXY(SDLRenderObject* obj, std::function<float(float)> bezierX, std::function<float(float)> bezierY);
SQUADIO_API std::function<void(float)> moveBezierXYZ(SDLRenderObject* obj, std::function<float(float)> bezierX, std::function<float(float)> bezierY, std::function<float(float)> bezierZ);
SQUADIO_API std::function<void(float)> keyframeJump(SDLRenderObject* obj, unsigned int frame);
SQUADIO_API std::function<void(float)> keyframeAnimate(SDLRenderObject* obj, unsigned int startFrame, unsigned int endFrame);
SQUADIO_API std::function<void(float)> visibleSprite(SDLRenderObject* obj, bool isVisible);
SQUADIO_API std::function<void(float)> flashSprite(SDLRenderObject* obj,unsigned int perFrame = 1);

//float bezier()
struct motion{
	std::function<void(float)> trans;
	std::function<float(float)> ease;
	float start; //a value from 0 to 1
	float duration; //a value from 1-start to 0
};
SQUADIO_API motion makeMotion(std::function<void(float)> trans, float start, float duration, std::function<float(float)> ease = ease_linear);
class Animation{
	std::list <motion> motions;
public:
	SQUADIO_API Animation();
	SQUADIO_API Animation(float d, std::list<motion> m);
	SQUADIO_API ~Animation();
	unsigned int duration;
	SQUADIO_API float lengthConversion(int progress);
	SQUADIO_API bool animate(float i);
	SQUADIO_API void push(std::function<void(float)> trans, float start, float duration, std::function<float(float)> ease = ease_linear);
};

#endif