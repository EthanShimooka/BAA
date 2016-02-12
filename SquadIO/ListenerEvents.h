#include "include\engineObject.h"
#include "include\SceneManager.h"


class InputListener : public SceneListener {
public:
	/// SCENE_EVENT_TYPE m_ListenFor;

	/// Abstract fucntion to handle event. To be overridden depending
	/// on type of event
	void Event(SceneManager* Manager, void* customData) const = 0;

};


class CollisionListener : public SceneListener {
public:
	/// SCENE_EVENT_TYPE m_ListenFor;

	/// Abstract fucntion to handle event. To be overridden depending
	/// on type of event
	void Event(SceneManager* Manager, void* customData) const = 0;

};


class NetworkListener : public SceneListener {
public:
	/// SCENE_EVENT_TYPE m_ListenFor;

	/// Abstract fucntion to handle event. To be overridden depending
	/// on type of event
	void Event(SceneManager* Manager, void* customData) const = 0;

};