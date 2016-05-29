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

GameObject* PlayerObjectFactory::Spawn(uint64_t PID, int classType, int team, bool local)
{

	GameObject* player = new GameObject();
	player->ID = PID;
	player->isAlive = true;
	player->type = GAMEOBJECT_TYPE::OBJECT_PLAYER;
	player->isLocal = local;
	PlayerRenderComponent* rend = nullptr;
	ClassComponent* classComp = nullptr;
	if (team == 1){
		player->setPos(-1600, 200);
		std::cout << "TEAM: " << team << "\nplayerID: " << player->ID << std::endl;
	}
	else {
		player->setPos(1600, -200);
	}

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
		rend = new PlayerRenderComponent(player, PeacockClassComponent::animation);
		classComp = new PeacockClassComponent(player);
		break;
	case CLASS_FLAMINGO:
		rend = new PlayerRenderComponent(player, FlamingoClassComponent::animation);
		classComp = new FlamingoClassComponent(player);
		break;
	case CLASS_TURKEY:
		rend = new PlayerRenderComponent(player, TurkeyClassComponent::animation);
		classComp = new TurkeyClassComponent(player);
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

	PlayerLogicComponent* logic = new PlayerLogicComponent(player, team);
	PlayerNetworkComponent* net = new PlayerNetworkComponent(player);

	PlayerPhysicsComponent* physics = new PlayerPhysicsComponent(player, classComp->height, classComp->width);

	if (local){		
		PlayerInputComponent* input = new PlayerInputComponent(player, classComp);
		PlayerUIComponent* UI = new PlayerUIComponent(player);

	}

	return player;
}