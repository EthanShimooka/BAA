#include "ButtonManager.h"

LButton::LButton(){
	obj = nullptr;
	mPositionX = 0;
	mPositionY = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(float x, float y){
	mPositionX = x;
	mPositionY = y;
}

float LButton::getXPosition(){
	return mPositionX;
}

float LButton::getYPosition(){
	return mPositionY;
}

void LButton::handleEvent(SDL_Event* e){
	while (SDL_PollEvent(e)){
	//if mouse event happened
		if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
			//get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);
			//check if mouse is in button
			bool inside = true;
			//mouse is left of button
			if (x < mPositionX)
				inside = false;
			//mouse is right of the button
			else if (x > mPositionX + BUTTON_WIDTH)
				inside = false;
			//mouse above the button
			else if (y < mPositionY)
				inside = false;
			//mouse below the button
			else if (y > mPositionY + BUTTON_HEIGHT){
				inside = false;
			}

			//mouse is outside button
			if (!inside) {
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
			}
			//mouse is inside button
			else{
				//set mouse over sprite
				switch (e->type){
				case SDL_MOUSEMOTION:
					std::cout << "mouse move" << std::endl;
					std::cout << e->motion.x << " " << e->motion.y << std::endl;
					mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;
				case SDL_MOUSEBUTTONDOWN:
					std::cout << "button click!!" << std::endl;
					mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
					break;
				case SDL_MOUSEBUTTONUP:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
					break;
				}
			}
		}
	}
}