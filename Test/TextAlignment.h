#pragma once
#include "include\RenderManager.h"

class TextAlignment
{
private:
	RenderManager* renderMan;
	SceneManager* sceneMan;
	int offset;
	int totalOffest;
	int fontSize = 30;
	std::string font;
	std::vector<SDLRenderObject*> texts;
	std::string layer;
	float startingYPos;
	float startingXPos;
	bool on;

	void findOffset();

public:
	TextAlignment(float y = 1 / 4.0, float x = 1 / 4.0, std::string font = "BowlbyOneSC-Regular", int fontSize = 30, std::string layer = "layer1");
	~TextAlignment();

	static enum TEXT_POS{
		LEFT = 1,
		MIDDLE = 2,
		RIGHT = 3,
	};

	struct COLOR{
		int r, g, b;
		COLOR(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {};
	};
	
	void createText(std::string text, COLOR* color, float x_offset);
	void createText(std::string text, COLOR* color);
	void createText(std::string text, COLOR* color, TEXT_POS pos);
	void setFont(std::string _font) { font = _font; }
	void setFontSize(int size);
	void updateText(std::string text, int textNum);
	void setStartingYPos(float height) { startingYPos = height; }
	void setStartingXPos(float width) { startingXPos = width; }
	//void setLayer(std::string layer) { layer = layer; }
	void resetOffset() { totalOffest = 0; }
	void toggleOn(int textNum, bool on);
	void toggleAllOn(bool on);
};

