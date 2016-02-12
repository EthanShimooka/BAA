#include <stdio.h>
#include "include\InputManager.h"
#include "include\SceneManager.h"


class InputListener{


private:
protected:
public:
	InputListener(){};
	~InputListener();
	void getInput();
	float input_x;
	float input_y;
};