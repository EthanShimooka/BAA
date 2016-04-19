#include "PlayerRenderComponent.h"

PlayerRenderComponent::PlayerRenderComponent(GameObject* player, function_t func)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	std::string playerName = NetworkManager::sInstance->getLobbyMap().find(gameObjectRef->ID)->second;

	SDLRenderObject * name = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 0, 0);
	int r, g, b;
	if (gameObjectRef->posY < 0){
		r = 200, g=0, b = 200;
	}
	else r = 255, g = 255, b=0;
	name->setResourceObject(renderMan->renderText(playerName.c_str(), r, g, b, 20, "BowlbyOneSC-Regular"));
	//name->setParent(base);
	name->setPos(0, -60);
	allObjs["name"] = name;
	if (allObjs["box"])allObjs["box"]->visible = true;
	//ChickenClassComponent* classComp = dynamic_cast<ChickenClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
	//classComp->animation(&objRef, allObjs, animations);

	func(&objRef, allObjs, animations);
}


PlayerRenderComponent::~PlayerRenderComponent()
{
	for (auto i = animations.begin(); i != animations.end(); i++){
		delete i->second;
	}
}


void PlayerRenderComponent::Update(){
	RenderComponent::Update();
	RenderBoundingBox((allObjs["box"]));
	ApplyPhysicsRotation(allObjs["base"]);
	RenderComponent::animate();
	allObjs["name"]->setPos(allObjs["base"]->getPosX(), -40 + allObjs["base"]->getPosY());
	if (!gameObjectRef->isAlive){
		if (allObjs["box"])allObjs["box"]->visible = false;
	}
	//update mouse position
	InputManager* inputMan = InputManager::getInstance();
	// ugly way of seeing if this is the local player
	if (!gameObjectRef->GetComponent(COMPONENT_INPUT))
		return;
	crosshairRef->posX = inputMan->getMouseX() - crosshairRef->getWidth()/2;
	crosshairRef->posY = inputMan->getMouseY() - crosshairRef->getHeight()/2;
	
	// update charge bar position (DOESN'T WORK RIGHT NOW)
	//chargebarMeterRef->posX = gameObjectRef->posX;
	//chargebarMeterRef->posY = gameObjectRef->posY;
	//chargebarShellRef->posX = gameObjectRef->posX;
	//chargebarShellRef->posY = gameObjectRef->posY;
	//chargebarMeterRef->posX = inputMan->getMouseX();
	//chargebarMeterRef->posY = inputMan->getMouseY();

}


