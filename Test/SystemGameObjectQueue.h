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

extern SystemGameObjectQueue GameObjects;