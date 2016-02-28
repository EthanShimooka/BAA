#include "include\ButtonManager.h"

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

bool LButton::handleEvent(SDL_Event* e){
	while (SDL_PollEvent(e)){
	//if mouse event happened
		if (e->type == SDL_MOUSEBUTTONDOWN){
			//get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			//mouse is left of button
			if (x < mPositionX)
				return false;
			//mouse is right of the button
			else if (x > mPositionX + BUTTON_WIDTH)
				return false;
			//mouse above the button
			else if (y < mPositionY)
				return false;
			//mouse below the button
			else if (y > mPositionY + BUTTON_HEIGHT){
				return false;
			}
			std::cout << "Click!!" << std::endl;
			return true;
		}
	}
}