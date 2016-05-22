#include "TutorialObjectFactory.h"


TutorialObjectFactory::TutorialObjectFactory()
{

}


TutorialObjectFactory::~TutorialObjectFactory()
{
}

GameObject* TutorialObjectFactory::Spawn(uint64_t PID, int imageID, float posX, float posY){
	GameObject* tutorial = new GameObject();
	tutorial->type = GAMEOBJECT_TYPE::OBJECT_TUTORIAL;
	tutorial->ID = PID;
	tutorial->isAlive = true;
	tutorial->setPos(posX, posY);
	TutorialRenderComponent* tutoRend = new TutorialRenderComponent(tutorial, imageID);

	GameObjects.AddObject(tutorial);
	return tutorial;
}