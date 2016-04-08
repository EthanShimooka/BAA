#pragma once
#include "include\AnimationLibrary.h"
#include <functional>


float ease_linear(float i){
	return i;
}
float ease_QuadIn(float i){
	return pow(i, 2);
}
float ease_QuadOut(float i){
	return i*(2 - i);
}
float ease_QuadInOut(float i){
	return (i < 0.5) ? 2 * i*i : -1 + (4 - 2 * i)*i;
}
std::function<float(float)> getBezier(float x0, float x1, float x2, float x3){
	return [=](float i) {
		return x0 + i*(3 * x1 - 3 * x0) + i*i*(3 * x2 - 6 * x1 + 3 * x0) + i*i*i*(x3 - 3 * x2 + 3 * x1 - x0);
	};
}
std::function<void(float)> rotateTransform(SDLRenderObject* obj, double start, double end){
	return [=](float i) {obj->rotation = end*i + start; };
}

std::function<void(float)> moveCircArc(SDLRenderObject* obj, float centerx, float centery, double radius, double start_angle, double end_angle){
	return [=](float i) {
		obj->posX = centerx + radius * cos(M_PI*(end_angle*i + start_angle) / 180);
		obj->posY = centery + radius * sin(M_PI*(end_angle*i + start_angle) / 180);
	};
}
std::function<void(float)> moveEllipseArc(SDLRenderObject* obj, float centerx, float centery, double height, double width, double start_angle, double end_angle){
	return [=](float i) {
		obj->posX = centerx + width / 2 * cos(M_PI*(end_angle*i + start_angle) / 180);
		obj->posY = centery + height / 2 * sin(M_PI*(end_angle*i + start_angle) / 180);
	};
}

std::function<void(float)> moveLinearX(SDLRenderObject* obj, float startx, float endx){
	return [=](float i) {obj->posX = (endx - startx)*i + startx; };
}
std::function<void(float)> moveLinearY(SDLRenderObject* obj, float starty, float endy){
	return [=](float i) {obj->posY = (endy - starty)*i + starty; };
}
std::function<void(float)> moveLinearZ(SDLRenderObject* obj, float startz, float endz){
	return [=](float i) {obj->posZ = (endz - startz)*i + startz; };
}
std::function<void(float)> moveLinearXY(SDLRenderObject* obj, float startx, float starty, float endx, float endy){
	return [=](float i) {obj->posZ = (endx - startx)*i + startx;
						 obj->posY = (endy - starty)*i + starty; };
}
std::function<void(float)> moveLinearXYZ(SDLRenderObject* obj, float startx, float starty, float startz, float endx, float endy, float endz){
	return [=](float i) {obj->posZ = (endx - startx)*i + startx;
					 	 obj->posY = (endy - starty)*i + starty;
						 obj->posZ = (endz - startz)*i + startz;
	};
}
std::function<void(float)> keyframeJump(SDLRenderObject* obj, unsigned int frame){
	return [=](float i) { obj->frameCurrent = frame; };
}
std::function<void(float)> keyframeAnimate(SDLRenderObject* obj, unsigned int startFrame, unsigned int endFrame){
	return [=](float i) { 
		if (i < 0) { obj->frameCurrent = startFrame; }
		else if (i >= 1){ obj->frameCurrent = endFrame; }
		else {
			obj->frameCurrent = (unsigned int)round(float(endFrame - startFrame)*i) + startFrame;
		}
	};
}



motion makeMotion(std::function<void(float)> trans, float start, float duration, std::function<float(float)> ease){
	motion m = { trans, ease, start, duration };
	return m;
}
Animation::Animation(float d, std::list<motion> m){
	duration = (unsigned int)d;
	motions = m;
}

Animation::~Animation(){
	std::cout << "Animation destructor called" << std::endl;
}


bool Animation::animate(float i){
	for (auto mot = motions.begin(); mot != motions.end(); mot++){
		if (i>=mot->start){
			float place;
			if (i >= mot->start + mot->duration){ place = 1.0; }//so durations of 0 are assumed to have finished
			//else if (i < mot->start)			{ place = 0.0; }
			else								{ place = (i - mot->start) / mot->duration; }
			mot->trans(mot->ease(place));//apply transformation, place should be between 0 and 1
		}
	}
	return ((i>1.0) || (i<0.0));
}
void Animation::push(std::function<void(float)> trans, int start, int duration, std::function<float(float)> ease){
	motion m = { trans, ease, start, duration };
	motions.push_back(m);
}

float Animation::lengthConversion(int progress){
	return float (progress / float(duration));
}