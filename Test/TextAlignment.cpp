#include "TextAlignment.h"


TextAlignment::TextAlignment(float y, float x, std::string font, int fontSize, std::string layer)
							: startingXPos(x), startingYPos(y), font(font), fontSize(fontSize), layer(layer)
{
	renderMan = RenderManager::getRenderManager();
	sceneMan = SceneManager::GetSceneManager();
	findOffset();
}


TextAlignment::~TextAlignment()
{
	for (auto& iter : texts){
		iter->setVisible(false);
		sceneMan->RemoveObject(iter);
	}
}

void TextAlignment::findOffset(){
	int w, h;
	renderMan->getWindowSize(&w, &h);
	offset = (int)((((w * h) * fontSize) / 1049088.0) * 2);
	totalOffest = 0;
}

void TextAlignment::createText(std::string text, COLOR* color, float x_offset){
	SDLRenderObject* sdlText;
	int w, h;
	renderMan->getWindowSize(&w, &h);
	sdlText = sceneMan->InstantiateObject(sceneMan->findLayer(layer), -1, 5, 0, true);
	// have to devide by 1049088.0 to acount for resolution change
	sdlText->setResourceObject(renderMan->renderText(text.c_str(), color->r, color->g, color->b, (int)(((w * h) * fontSize) / 1049088.0), font));
	sdlText->setPos((w * x_offset) - (sdlText->getWidth() / 2.0f), (h * startingYPos) - (sdlText->getHeight() / 2.0f) + totalOffest);
	totalOffest += offset;
	texts.push_back(sdlText);
}

void TextAlignment::createText(std::string text, COLOR* color){
	createText(text, color, startingXPos);
}

void TextAlignment::createText(std::string text, COLOR* color, TEXT_POS pos){
	createText(text, color, pos / 4.0f);
}

void TextAlignment::toggleAllOn(bool on){
	if (on && this->on == on) return;
	this->on = on;
	for (auto& iter : texts){
		iter->setVisible(on);
	}
}

void TextAlignment::toggleOn(int textNum, bool on){
	texts[textNum]->setVisible(on);
}

void TextAlignment::setFontSize(int size){
	fontSize = size; 
	findOffset();
}

void TextAlignment::updateText(std::string text, int textNum, COLOR* color){
	float posX = texts[textNum]->posX;
	float posY = texts[textNum]->posY;
	int w, h;
	renderMan->getWindowSize(&w, &h);
	float x_offset = (posX + (texts[textNum]->getWidth() / 2.0f)) / w;
	removeText(textNum);
	texts[textNum] = sceneMan->InstantiateObject(sceneMan->findLayer(layer), -1, 5, 0, true);
	// have to devide by 1049088.0 to acount for resolution change
	texts[textNum]->setResourceObject(renderMan->renderText(text.c_str(), color->r, color->g, color->b, (int)(((w * h) * fontSize) / 1049088.0), font));
	texts[textNum]->setPos((w * x_offset) - (texts[textNum]->getWidth() / 2.0f), posY);
}

void TextAlignment::removeText(int textNum){
	texts[textNum]->setVisible(false);
	sceneMan->RemoveObject(texts[textNum]);
}