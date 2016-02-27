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

	vector<GameObject*> alive_object;
	vector<GameObject*> dead_object;

	void AddObject(GameObject * obj);

	void DeleteObject(int g_id);


};

#endif