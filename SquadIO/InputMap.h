#ifndef INPUTMAP_H_INCLUDED
#define INPUTMAP_H_INCLUDED

#include <SDL.h>

// keyboard codes found at http://wiki.libsdl.org/SDLScancodeLookup

#define KEYBOARD_SIZE 1 // change to 282 later when keys are mapped
#define MOUSE_SIZE 2

enum KeyboardKeys {

};

enum MouseButton {
	MOUSE_LEFT,
	MOUSE_RIGHT
};

#endif