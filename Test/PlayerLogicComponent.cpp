#include "PlayerLogicComponent.h"
#include "include\network\GamerServices.h"

uint64_t PlayerLogicComponent::childID{ 1001 };

PlayerLogicComponent::PlayerLogicComponent(GameObject* player, int team)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	gameObjectRef->team = team;
	child_id_counter = childID;
	childID += 1000;
	std::cout << child_id_counter << std::endl;
	dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS))->powerNum = &child_id_counter;
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

	

	
}

/// For spawning local feathers
uint64_t PlayerLogicComponent::spawnFeather(int dx, int dy, float speed){
	PlayerRenderComponent * render = (PlayerRenderComponent*)gameObjectRef->GetComponent(COMPONENT_RENDER);
	gameObjectRef->flipH = dx < 0;
	render->setAnimation("throw");
	render->setNextAnimation("idle");
	GameObject* newFeather = fFactory.Spawn(gameObjectRef, child_id_counter++, gameObjectRef->posX, gameObjectRef->posY, (float)dx, (float)dy, speed);
	GameObjects.AddObject(newFeather);
	return child_id_counter - 1;
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
		vel.x = vel.x < 5 ? 5 : vel.x;
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



void PlayerLogicComponent::playDeathSFX(int playerClass){
	AudioManager* audioMan = AudioManager::getAudioInstance();
	switch (playerClass){
	case CLASS_CHICKEN:
		audioMan->playByName("chickensfx.ogg");
		break;
	case CLASS_PEACOCK:
		audioMan->playByName("peacocksfx.ogg");
		break;
	case CLASS_FLAMINGO:
		audioMan->playByName("flamingosfx.ogg");
		break;
	case CLASS_QUAIL:
		audioMan->playByName("quailsfx.ogg");
		break;
	case CLASS_TURKEY:
		audioMan->playByName("turkeysfx.ogg");
		break;
	case CLASS_EAGLE:
		//Unimplemented
		//audioMan->playByName("eaglesfx.ogg");
		break;
	}
	
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