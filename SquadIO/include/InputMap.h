#ifndef INPUTMAP_H_INCLUDED
#define INPUTMAP_H_INCLUDED

#include "sdl2\SDL.h"

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport)
#else
#define SQUADIO_API __declspec(dllimport)
#endif

// SDL key codes found at https://wiki.libsdl.org/SDLScancodeLookup
// https://wiki.libsdl.org/SDL_Keysym
// accessed by ev.key.keysym.scancode in InputManager

#define KEYBOARD_SIZE 282
#define MOUSE_SIZE 3

enum KeyboardKeys {
	KEY_UNKNOWN = SDL_SCANCODE_UNKNOWN,
	KEY_A = SDL_SCANCODE_A,
	KEY_B = SDL_SCANCODE_B,
	KEY_C = SDL_SCANCODE_C,
	KEY_D = SDL_SCANCODE_D,
	KEY_E = SDL_SCANCODE_E,
	KEY_F = SDL_SCANCODE_F,
	KEY_G = SDL_SCANCODE_G,
	KEY_H = SDL_SCANCODE_H,
	KEY_I = SDL_SCANCODE_I,
	KEY_J = SDL_SCANCODE_J,
	KEY_K = SDL_SCANCODE_K,
	KEY_L = SDL_SCANCODE_L,
	KEY_M = SDL_SCANCODE_M,
	KEY_N = SDL_SCANCODE_N,
	KEY_O = SDL_SCANCODE_O,
	KEY_P = SDL_SCANCODE_P,
	KEY_Q = SDL_SCANCODE_Q,
	KEY_R = SDL_SCANCODE_R,
	KEY_S = SDL_SCANCODE_S,
	KEY_T = SDL_SCANCODE_T,
	KEY_U = SDL_SCANCODE_U,
	KEY_V = SDL_SCANCODE_V,
	KEY_W = SDL_SCANCODE_W,
	KEY_X = SDL_SCANCODE_X,
	KEY_Y = SDL_SCANCODE_Y,
	KEY_Z = SDL_SCANCODE_Z,
	KEY_1 = SDL_SCANCODE_1,
	KEY_2 = SDL_SCANCODE_2,
	KEY_3 = SDL_SCANCODE_3,
	KEY_4 = SDL_SCANCODE_4,
	KEY_5 = SDL_SCANCODE_5,
	KEY_6 = SDL_SCANCODE_6,
	KEY_7 = SDL_SCANCODE_7,
	KEY_8 = SDL_SCANCODE_8,
	KEY_9 = SDL_SCANCODE_9,
	KEY_0 = SDL_SCANCODE_0,
	KEY_RETURN = SDL_SCANCODE_RETURN,
	KEY_ESCAPE = SDL_SCANCODE_ESCAPE,
	KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
	KEY_TAB = SDL_SCANCODE_TAB,
	KEY_SPACE = SDL_SCANCODE_SPACE,
	KEY_MINUS = SDL_SCANCODE_MINUS,
	KEY_EQUALS = SDL_SCANCODE_EQUALS,
	KEY_LBRACKET = SDL_SCANCODE_LEFTBRACKET,
	KEY_RBRACKET = SDL_SCANCODE_RIGHTBRACKET,
	KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,
	KEY_NONUSHASH = SDL_SCANCODE_NONUSHASH,
	KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
	KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
	KEY_GRAVE = SDL_SCANCODE_GRAVE,
	KEY_COMMA = SDL_SCANCODE_COMMA,
	KEY_PERIOD = SDL_SCANCODE_PERIOD,
	KEY_SLASH = SDL_SCANCODE_SLASH,
	KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK,
	KEY_F1 = SDL_SCANCODE_F1,
	KEY_F2 = SDL_SCANCODE_F2,
	KEY_F3 = SDL_SCANCODE_F3,
	KEY_F4 = SDL_SCANCODE_F4,
	KEY_F5 = SDL_SCANCODE_F5,
	KEY_F6 = SDL_SCANCODE_F6,
	KEY_F7 = SDL_SCANCODE_F7,
	KEY_F8 = SDL_SCANCODE_F8,
	KEY_F9 = SDL_SCANCODE_F9,
	KEY_F10 = SDL_SCANCODE_F10,
	KEY_F11 = SDL_SCANCODE_F11,
	KEY_F12 = SDL_SCANCODE_F12,
	KEY_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN,
	KEY_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK,
	KEY_PAUSE = SDL_SCANCODE_PAUSE,
	KEY_INSERT = SDL_SCANCODE_INSERT,
	KEY_HOME = SDL_SCANCODE_HOME,
	KEY_PAGEUP = SDL_SCANCODE_PAGEUP,
	KEY_DELETE = SDL_SCANCODE_DELETE,
	KEY_END = SDL_SCANCODE_END,
	KEY_PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
	KEY_RIGHT = SDL_SCANCODE_RIGHT,
	KEY_LEFT = SDL_SCANCODE_LEFT,
	KEY_DOWN = SDL_SCANCODE_DOWN,
	KEY_UP = SDL_SCANCODE_UP,
	// add keypad codes here later 83-221
	KEY_LCTRL = SDL_SCANCODE_LCTRL,
	KEY_LSHIFT = SDL_SCANCODE_LSHIFT,
	KEY_LALT = SDL_SCANCODE_LALT,
	KEY_LGUI = SDL_SCANCODE_LGUI,
	KEY_RCTRL = SDL_SCANCODE_RCTRL,
	KEY_RSHIFT = SDL_SCANCODE_RSHIFT,
	KEY_RALT = SDL_SCANCODE_RALT,
	KEY_RGUI = SDL_SCANCODE_RGUI,
	KEY_MODE = SDL_SCANCODE_MODE,
	KEY_AUDIONEXT = SDL_SCANCODE_AUDIONEXT,
	KEY_AUDIOPREV = SDL_SCANCODE_AUDIOPREV,
	KEY_AUDIOSTOP = SDL_SCANCODE_AUDIOSTOP,
	KEY_AUDIOPLAY = SDL_SCANCODE_AUDIOPLAY,
	KEY_AUDIOMUTE = SDL_SCANCODE_AUDIOMUTE,
	KEY_MEDIASELECT = SDL_SCANCODE_MEDIASELECT,
	KEY_WWW = SDL_SCANCODE_WWW,
	KEY_MAIL = SDL_SCANCODE_MAIL,
	KEY_CALCULATOR = SDL_SCANCODE_CALCULATOR,
	KEY_COMPUTER = SDL_SCANCODE_COMPUTER,
	KEY_AC_SEARCH = SDL_SCANCODE_AC_SEARCH,
	KEY_AC_HOME = SDL_SCANCODE_AC_HOME,
	KEY_AC_BACK = SDL_SCANCODE_AC_BACK,
	KEY_AC_FORWARD = SDL_SCANCODE_AC_FORWARD,
	KEY_AC_STOP = SDL_SCANCODE_AC_STOP,
	KEY_AC_REFRESH = SDL_SCANCODE_AC_REFRESH,
	KEY_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS,
	KEY_BRIGHTNESSDOWN = SDL_SCANCODE_BRIGHTNESSDOWN,
	KEY_BRIGHTNESSUP = SDL_SCANCODE_BRIGHTNESSUP,
	KEY_DISPLAYSWITCH = SDL_SCANCODE_DISPLAYSWITCH,
	KEY_KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE,
	KEY_KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN,
	KEY_KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP,
	KEY_EJECT = SDL_SCANCODE_EJECT,
	KEY_SLEEP = SDL_SCANCODE_SLEEP
};

enum MouseButton {
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

enum JoystickButton{
	//NOTE: currently hardcoded values based on xbox360/X1/PS3 input. need to investigate
	//if steam controller uses same input.
	JOYSTICK_INVALID = SDL_CONTROLLER_BUTTON_INVALID,
	JOYSTICK_A = SDL_CONTROLLER_BUTTON_A,
	JOYSTICK_B = SDL_CONTROLLER_BUTTON_B,
	JOYSTICK_X = SDL_CONTROLLER_BUTTON_X,
	JOYSTICK_Y = SDL_CONTROLLER_BUTTON_Y,
	JOYSTICK_LEFTSHOULDER = 4,
	JOYSTICK_RIGHTSHOULDER = 5,
	JOYSTICK_BACK = 6,
	JOYSTICK_HOME = 10,
	JOYSTICK_START = 7,
	JOYSTICK_LEFTSTICK = 8,
	JOYSTICK_RIGHTSTICK = 9,
	JOYSTICK_DPAD_UP = SDL_HAT_UP,
	JOYSTICK_DPAD_RIGHTUP = SDL_HAT_RIGHTUP,
	JOYSTICK_DPAD_RIGHT = SDL_HAT_RIGHT,
	JOYSTICK_DPAD_RIGHTDOWN = SDL_HAT_RIGHTDOWN,
	JOYSTICK_DPAD_DOWN = SDL_HAT_DOWN,
	JOYSTICK_DPAD_LEFTDOWN = SDL_HAT_LEFTDOWN,
	JOYSTICK_DPAD_LEFT = SDL_HAT_LEFT,
	JOYSTICK_DPAD_LEFTUP = SDL_HAT_LEFTUP,
	JOYSTICK_MAX = SDL_CONTROLLER_BUTTON_MAX 
};

#endif
