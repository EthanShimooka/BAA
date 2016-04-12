#include "PlayerObjectFactory.h"
//#include "ClassComponentIncludes.h"
//#include "ClassComponent.h"
 

PlayerObjectFactory::PlayerObjectFactory()
{
}


PlayerObjectFactory::~PlayerObjectFactory()
{

}


/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* PlayerObjectFactory::Spawn(uint64_t PID, int classType, bool local)
{

	GameObject* player = new GameObject();
	player->ID = PID;
	player->isAlive = true;
	player->type = GAMEOBJECT_TYPE::OBJECT_PLAYER;

	PlayerRenderComponent* rend = nullptr;
	ClassComponent* classComp = nullptr;


	switch (classType){
	case CLASS_CHICKEN:
		classComp = new ChickenClassComponent(player);
		rend = new PlayerRenderComponent(player, ChickenClassComponent::animation);
		break;
	case CLASS_EAGLE:
		classComp = new EagleClassComponent(player);
		rend = new PlayerRenderComponent(player, EagleClassComponent::animation);
		break;
	case CLASS_PEACOCK:
		classComp = new PeacockClassComponent(player);
		rend = new PlayerRenderComponent(player, PeacockClassComponent::animation);
		break;
	case CLASS_FLAMINGO:
		classComp = new FlamingoClassComponent(player);
		rend = new PlayerRenderComponent(player, FlamingoClassComponent::animation);
		break;
	case CLASS_TURKEY:
		classComp = new TurkeyClassComponent(player);
		rend = new PlayerRenderComponent(player, TurkeyClassComponent::animation);
		break;
	case CLASS_QUAIL:
		classComp = new QuailClassComponent(player);
		rend = new PlayerRenderComponent(player, QuailClassComponent::animation);
		break;
	default:
		LogManager* log = LogManager::GetLogManager();
		log->logBuffer << "Bad enum chosen for class\n";
		log->flush();
		break;
	}

	//PlayerRenderComponent* rend = new PlayerRenderComponent(player);

	if (local){
		PlayerInputComponent* input = new PlayerInputComponent(player, classComp->speed, classComp->featherSpeed);
		PlayerPhysicsComponent* physics = new PlayerPhysicsComponent(player, classComp->height, classComp->width);
	}
	

	PlayerLogicComponent* logic = new PlayerLogicComponent(player);

	PlayerNetworkComponent* net = new PlayerNetworkComponent(player);
	player->setPos(player->posX, 200);
	
	return player;
}