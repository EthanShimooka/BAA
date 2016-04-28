#include "PlayerLogicComponent.h"
#include "include\network\GamerServices.h"


PlayerLogicComponent::PlayerLogicComponent(GameObject* player, int team)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	gameObjectRef->team = team;
}


PlayerLogicComponent::~PlayerLogicComponent()
{
}


void PlayerLogicComponent::Update(){
	if (!gameObjectRef->GetComponent(COMPONENT_INPUT))
		return;
	InputManager* input = InputManager::getInstance();
	//update orientation
	if (gameObjectRef->posY < 0)gameObjectRef->flipV = true;
	else gameObjectRef->flipV = false;

	//update HUD
	int w, h;
	birdseedHUD->getSize(w, h);
	ClassComponent* classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
	int maxBirdseed = getMaxBirdseedByClass(classComp->getClass());
	float meterPercent = (classComp->currBirdseed / (float)maxBirdseed);
	if (meterPercent > 1) meterPercent = 1;
	SDL_Rect rect = birdseedHUD->getRenderRect();
	SDL_Rect seedRect = { defaultRect.x, defaultRect.y + defaultRect.h*(1-meterPercent), defaultRect.w, defaultRect.h*meterPercent };
	birdseedHUD->posY = 30 + defaultRect.h*(1-meterPercent);
	birdseedHUD->setRenderRect(seedRect);

	// set render rectangle for charge bar HUD
	chargeHUD->getSize(w, h);
	SDL_Rect cRect = { chargeRect.x, chargeRect.y + chargeRect.h*(1 - currChargePercentage), chargeRect.w, chargeRect.h*currChargePercentage };
	chargeHUD->posY = chargeRect.h * (1 - currChargePercentage);
	chargeHUD->setRenderRect(cRect);

	//update the countdown timer
	RenderManager* renderMan = RenderManager::getRenderManager();
	int timeRemaininginSeconds = Timing::sInstance.GetTimeRemainingS();
	string minutes = Timing::sInstance.GetMinutesLeftAsString(timeRemaininginSeconds);
	string seconds = Timing::sInstance.GetSecondsLeftAsString(timeRemaininginSeconds);
	if (seconds.length() == 1)seconds = "0" + seconds;
	std::string title = minutes + ":" + seconds; //concat on the time remaining here!
	timerHUD->setResourceObject(renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular"));
}

/// For spawning local feathers
uint64_t PlayerLogicComponent::spawnFeather(int dx, int dy, float speed){
	PlayerRenderComponent * render = (PlayerRenderComponent*)gameObjectRef->GetComponent(COMPONENT_RENDER);
	gameObjectRef->flipH = dx < 0;
	render->setAnimation("throw");
	render->setNextAnimation("idle");
	GameObject* newFeather = fFactory.Spawn(gameObjectRef, featherNum++, gameObjectRef->posX, gameObjectRef->posY, (float)dx, (float)dy, speed);
	GameObjects.AddObject(newFeather);
	return featherNum - 1;
}

/// For spawning networked feathers
void PlayerLogicComponent::spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY, float speed){
	// charge time is one because speed is the feather speed * chargeTime
	GameObjects.AddObject(fFactory.Spawn(gameObjectRef, ID, initialX, initialY, (float)destX, (float)destY, speed));
	PlayerRenderComponent * render = (PlayerRenderComponent*)gameObjectRef->GetComponent(COMPONENT_RENDER);
	render->setAnimation("throw");
	render->setNextAnimation("walk");
}

void PlayerLogicComponent::becomeEgg(){
	if (!isEgg){
		//change texture to egg
		PlayerRenderComponent* renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
		SceneManager* sceneMan = SceneManager::GetSceneManager();
		

		//turn all sprites of player invisible
		for (auto obj : renderComp->allObjs)obj.second->visible = false;
		renderComp->allObjs["egg"]->visible=true;


		//allow body to roll and limit sliding
		PlayerPhysicsComponent* physicsComp = dynamic_cast<PlayerPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
		physicsComp->mBody->SetFixedRotation(false);
		b2Vec2 vel = physicsComp->mBody->GetLinearVelocity();
		std::cout << "horizontal velocity: " << vel.x << std::endl;
		vel.x = vel.x > 5 ? 5 : vel.x;
		physicsComp->mBody->SetLinearVelocity(b2Vec2(vel.x,vel.y));

		//ignore input and roll to base
		PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		logicComp->isEgg = true;

		// if this is the local Player
		if (gameObjectRef->isLocal){
			RenderManager::getRenderManager()->ShakeScreen(0.3f, 1.0f);
		}
	}

}

void PlayerLogicComponent::hatchBird(){
	if (isEgg){
		PlayerRenderComponent* renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
		//reset sprites
		for (auto obj : renderComp->allObjs)obj.second->visible = true;
		renderComp->allObjs["egg"]->visible = false;

		//reset positions
		renderComp->allObjs["base"]->posX = gameObjectRef->posX;
		renderComp->allObjs["base"]->posY = gameObjectRef->posY;
		//reset rotation
		PlayerPhysicsComponent* physicsComp = dynamic_cast<PlayerPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
		b2Vec2 pos;
		physicsComp->mBody->SetFixedRotation(true);
		pos = physicsComp->mBody->GetPosition();
		gameObjectRef->rotation = 0;
		physicsComp->mBody->SetTransform(pos, 0);
		renderComp->allObjs["base"]->rotation = 0;
		isEgg = false;
	}
}

void PlayerLogicComponent::startCharge() {
	charging = true;
}

void PlayerLogicComponent::endCharge() {
	charging = false;
}

int PlayerLogicComponent::getMaxBirdseedByClass(int playerClass){
	switch (playerClass)
	{
	case CLASS_CHICKEN:{
						   ChickenClassComponent* classComp = dynamic_cast<ChickenClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
						   return classComp->seedRequired;
	}
	case CLASS_PEACOCK:{
						   PeacockClassComponent* classComp = dynamic_cast<PeacockClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
						   return classComp->seedRequired;
	}
	case CLASS_FLAMINGO:{
							FlamingoClassComponent* classComp = dynamic_cast<FlamingoClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
							return classComp->seedRequired;
	}
	case CLASS_QUAIL:{
						 QuailClassComponent* classComp = dynamic_cast<QuailClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
						 return classComp->seedRequired;
	}
	case CLASS_TURKEY:{
						  TurkeyClassComponent* classComp = dynamic_cast<TurkeyClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
						  return classComp->seedRequired;
	}
	case CLASS_EAGLE:{
						 EagleClassComponent* classComp = dynamic_cast<EagleClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
						 return classComp->seedRequired;
	}
	default:{
				LogManager* log = LogManager::GetLogManager();
				log->logBuffer << "Problem in PlayerLogicComponent::getMaxBirdseedByClass. Will cause div by 0 error\n";
				log->flush();
				return 0;
	}
	}
}