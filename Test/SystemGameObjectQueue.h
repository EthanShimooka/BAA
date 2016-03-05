#pragma once
#ifndef SYSTEMGAMEOBJECTQUEUE_H_INCLUDED
#define SYSTEMGAMEOBJECTQUEUE_H_INCLUDED

#include "GameObject.h"
#include <vector>


class SystemGameObjectQueue
{
private:
protected:
public:
	SystemGameObjectQueue();
	~SystemGameObjectQueue();

	vector<GameObject*> alive_objects;
	vector<GameObject*> dead_objects;

	GameObject* AddObject(GameObject * obj);

	void DeleteObject(uint64_t g_id);


};

//GLOBAL INSTANCE OF SYSTEMGAMEOBJECTQUEUE. Anywhere that includes this file can just use GameObjects like a local variable.
extern SystemGameObjectQueue GameObjects;

#endif