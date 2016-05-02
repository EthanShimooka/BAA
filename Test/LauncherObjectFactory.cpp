#include "LauncherObjectFactory.h"


LauncherObjectFactory::LauncherObjectFactory()
{
}


LauncherObjectFactory::~LauncherObjectFactory()
{
}


GameObject * LauncherObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length, int team){

	GameObject* launcher = new GameObject();

	launcher->ID = PID;
	launcher->setPos(posX, posY);
	launcher->isAlive = true;
	launcher->health = 5;
	launcher->team = team;
	launcher->type = GAMEOBJECT_TYPE::OBJECT_BASE; // CHANGE

	// Minion Specific Render Component. In future will have flag
	// for type of class,  which will instatiate launcherd on flag

		LauncherRenderComponent* rend = new LauncherRenderComponent(launcher, team);
	if (team == TEAM_YELLOW){
		launcher->flipV = false;
		launcher->flipH = false;
	}
	else{
		launcher->flipV = true;
		launcher->flipH = true;
	}
		LauncherPhysicsComponent* physics = new LauncherPhysicsComponent(launcher);

	//MidlauncherLogicComponent* logic = new MidlauncherLogicComponent(launcher);

	return launcher;
}