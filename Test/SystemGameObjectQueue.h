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

	std::vector<GameObject*> alive_objects;
	std::vector<GameObject*> dead_objects;
	std::vector<GameObject*> dead_feathers;
	std::vector<GameObject*> dead_minions;

	GameObject* AddObject(GameObject * obj);

	/// Loops deleting all gameobjects in alive_objects vector
	void DeleteObjects(int g_id);
};

//GLOBAL INSTANCE OF SYSTEMGAMEOBJECTQUEUE. Anywhere that includes this file can just use GameObjects like a local variable.
extern SystemGameObjectQueue GameObjects;

#endif