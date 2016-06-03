#include "PlayerUIComponent.h"


PlayerUIComponent::PlayerUIComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_UI, this);
}


PlayerUIComponent::~PlayerUIComponent(){
	for (auto currUIObj : UIObjs){
		delete currUIObj;
	}
}

void PlayerUIComponent::addToKillList(uint64_t shooter, uint64_t victim){
	if (!gameObjectRef->GetComponent(COMPONENT_UI))
		return;
	//start by finding the first open spot to add the notification to
	int elemIndex = 0;
	bool success = false;
	for (unsigned i = 0; i < killHUD.size(); i++){
		if (!killHUD[i].first->visible){
			elemIndex = i;
			success = true;
			break;
		}
	}

	if (!success){
		//this happens when we iterate through the list and see that there is no free spot to put the new notification
		//we need to rotate the array and add it on to the end now
		auto tempElem = killHUD[0];
		for (unsigned i = 0; i < killHUD.size() - 1; i++){
			killHUD[i] = killHUD[i + 1];
		}
		killHUD[killHUD.size() - 1] = tempElem;
		//now that we rotated it, modify the last elem.
	}
	//create the new elem here
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	string shooterText = GamerServices::sInstance->GetRemotePlayerName(shooter);
	string victimText = GamerServices::sInstance->GetRemotePlayerName(victim);
	shooterText += " -> " + victimText;
	//reassign the new element to be the new notification
	killHUD[elemIndex].first->setResourceObject(RenderManager::getRenderManager()->renderText(shooterText.c_str(), 255, 0, 255, 20, "BowlbyOneSC-Regular"));
	killHUD[elemIndex].first->visible = true;
	killHUD[elemIndex].second = clock();
}

void PlayerUIComponent::updateKillHUD(){
	//update player kill notification
	double oldestAge = clock() - killHUD[0].second;
	//std::cout << "oldestAge=" << oldestAge << std::endl;
	//when the message has displayed for 5 seconds, it's old and should be removedi
	if (oldestAge>5000){
		//circular rotation on array
		killHUD[0].first->visible = false;
		auto tempElem = killHUD[0];
		for (unsigned i = 0; i < killHUD.size() - 1; i++){
			killHUD[i] = killHUD[i + 1];
		}
		killHUD[killHUD.size() - 1] = tempElem;
		//now update postions on screen
		for (unsigned i = 0; i < killHUD.size(); i++){
			killHUD[i].first->setPos((float)killHUD[i].first->posX, (float)(130 + i * 30));
		}
	}
}

void PlayerUIComponent::Update(){
	updateKillHUD();
	//update HUD
	int w, h;
	birdseedHUD->getSize(w, h);
	ClassComponent* classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
	PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	int maxBirdseed = logicComp->getMaxBirdseedByClass(classComp->getClass());
	float meterPercent = (classComp->currBirdseed / (float)maxBirdseed);
	if (meterPercent > 1) meterPercent = 1;
	SDL_Rect rect = birdseedHUD->getRenderRect();
	SDL_Rect seedRect = { defaultRect.x, (int)(defaultRect.y + defaultRect.h*(1 - meterPercent)), defaultRect.w, (int)(defaultRect.h*meterPercent) };
	birdseedHUD->posY = 30 + defaultRect.h*(1 - meterPercent);
	birdseedHUD->setRenderRect(seedRect);

	// set render rectangle for charge bar HUD
	//chargeHUD->getSize(w, h);
	//SDL_Rect cRect = { chargeRect.x, chargeRect.y + chargeRect.h*(1 - currChargePercentage), chargeRect.w, chargeRect.h*currChargePercentage };
	//chargeHUD->posY = chargeRect.h * (1 - currChargePercentage);
	//chargeHUD->setRenderRect(cRect);

	//update the countdown timer
	RenderManager* renderMan = RenderManager::getRenderManager();
	int timeRemaininginSeconds = Timing::sInstance.GetTimeRemainingS();
	string minutes = Timing::sInstance.GetMinutesLeftAsString(timeRemaininginSeconds);
	string seconds = Timing::sInstance.GetSecondsLeftAsString(timeRemaininginSeconds);
	if (seconds.length() == 1)seconds = "0" + seconds;
	std::string title = minutes + ":" + seconds; //concat on the time remaining here!
	timerHUD->replaceResourceObject(renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular"));
	//renderMan->renderText(title.c_str(), 255, 255, 0, 70, "BowlbyOneSC-Regular",timerHUD->renderResource);
}