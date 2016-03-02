#pragma once
#ifndef SYSTEMUIOBJECTQUEUE_H_INCLUDED
#define SYSTEMUIOBJECTQUEUE_H_INCLUDED

#include <vector>
#include "UIObject.h"

class SystemUIObjectQueue{
public:
	SystemUIObjectQueue();
	~SystemUIObjectQueue();

	vector<UIObject*> alive_objects;
	vector<UIObject*> dead_objects;

	UIObject* AddObject(UIObject * obj);

	void DeleteObject(int g_id);


};

//GLOBAL INSTANCE OF SYSTEMGAMEOBJECTQUEUE. Anywhere that includes this file can just use GameObjects like a local variable.
extern SystemUIObjectQueue UIObjects;

#endif