#pragma once

#include "GameObject.h"
#include <vector>


class SystemGameObjectQueue
{
private:
protected:
public:
	SystemGameObjectQueue();
	~SystemGameObjectQueue();

	vector<GameObject*> alive_object;
	vector<GameObject*> dead_object;

	void AddObject(GameObject * obj);

	void DeleteObject(int g_id);


};

//GLOBAL INSTANCE OF SYSTEMGAMEOBJECTQUEUE. Anywhere that includes this file can just use GameObjects like a local variable.
extern SystemGameObjectQueue GameObjects;