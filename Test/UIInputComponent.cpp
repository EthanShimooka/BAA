#include "UIInputComponent.h"

UIInputComponent::UIInputComponent(){
}


UIInputComponent::~UIInputComponent(){
}

void UIInputComponent::Update(){	

	UIRenderComponent* rend = dynamic_cast<UIRenderComponent*>(uiObjectRef->GetComponent(COMPONENT_RENDER));

	uint64_t me = NetworkManager::sInstance->GetMyPlayerId();

	switch (uiObjectRef->ID){
	case PLAY_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			NetworkManager::sInstance->TryReadyGame();
		}
		break;
	case CANCEL_BUTTON:
		break;
	case BACK_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			std::cout << "Click!" << std::endl;
			//NetworkManager::sInstance->SetState(NetworkManager::sInstance->NMS_MainMenu);
		}
		break;
	case JOIN_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			NetworkManager::sInstance->StartLobbySearch();
		}
		break;
	case READY_BUTTON:
		if (isButtonPressed(READY_BUTTON_WIDTH, READY_BUTTON_HEIGHT)){
			//std::cout << "click" << std::endl;
		}
		break;
	case INVITE_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT)){
			//std::cout << "click" << std::endl;
			GamerServices::sInstance->InviteFriendsFromOverlay();
		}
		break;
	case CHICKEN:
		if (isButtonPressed(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "click" << std::endl;
			AudioManager* audioMan = AudioManager::getAudioInstance();
			audioMan->playByName("chickensfx.ogg");
			uiObjectRef->ready = true;
		}
		if (isMouseHovering(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	case EAGLE:
	case TURKEY:
		if (isButtonPressed(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "click" << std::endl;
			AudioManager* audioMan = AudioManager::getAudioInstance();
			audioMan->playByName("turkeysfx.ogg");
			uiObjectRef->ready = true;
		}
		if (isMouseHovering(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	case QUAIL:
		if (isButtonPressed(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "click" << std::endl;
			AudioManager* audioMan = AudioManager::getAudioInstance();
			audioMan->playByName("quailsfx.ogg");
			uiObjectRef->ready = true;
		}
		if (isMouseHovering(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	case FLAMINGO:
		if (isButtonPressed(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "click" << std::endl;
			AudioManager* audioMan = AudioManager::getAudioInstance();
			audioMan->playByName("flamingosfx.ogg");
			uiObjectRef->ready = true;
		}
		if (isMouseHovering(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	case PEACOCK:
		if (isButtonPressed(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "click" << std::endl;
			AudioManager* audioMan = AudioManager::getAudioInstance();
			audioMan->playByName("peacocksfx.ogg");
			uiObjectRef->ready = true;
		}
		if (isMouseHovering(this->uiObjectRef->getWidth(), this->uiObjectRef->getHeight())){
			//std::cout << "hovering" << std::endl;
			uiObjectRef->hoverPicture = true;
		}
		else{
			uiObjectRef->hoverPicture = false;
		}
		break;
	case YELLOW_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT) && !uiObjectRef->teamPicked){
			rend->ChangeSprite(YELLOW_BUTTON2);
			uiObjectRef->teamPicked = true;
			NetworkManager::sInstance->SendTeamToPeers(TEAM_YELLOW);
		}
		else if (isMouseHovering(BUTTON_WIDTH, BUTTON_HEIGHT) && !uiObjectRef->teamPicked){
			rend->ChangeSprite(YELLOW_BUTTON2);
		}
		else if (!isMouseHovering(BUTTON_WIDTH, BUTTON_HEIGHT) && !uiObjectRef->teamPicked){
			rend->ChangeSprite(YELLOW_BUTTON);
		}
		else if (uiObjectRef->teamPicked == false){
			rend->ChangeSprite(YELLOW_BUTTON);
		}
		break;
	case PURPLE_BUTTON:
		if (isButtonPressed(BUTTON_WIDTH, BUTTON_HEIGHT) && !uiObjectRef->teamPicked){
			rend->ChangeSprite(PURPLE_BUTTON2);
			NetworkManager::sInstance->SendTeamToPeers(TEAM_PURPLE);
			uiObjectRef->teamPicked = true;
		}
		else if (isMouseHovering(BUTTON_WIDTH, BUTTON_HEIGHT) && !uiObjectRef->teamPicked){
			rend->ChangeSprite(PURPLE_BUTTON2);
		}
		else if (!isMouseHovering(BUTTON_WIDTH, BUTTON_HEIGHT) && !uiObjectRef->teamPicked){
			rend->ChangeSprite(PURPLE_BUTTON);
		}
		else if (uiObjectRef->teamPicked == false){
			rend->ChangeSprite(PURPLE_BUTTON);
		}
		break;
	}
}

bool UIInputComponent::isButtonPressed(int width, int height){

	InputManager* input = InputManager::getInstance();
	if (input->isMouseDown(MOUSE_LEFT)){
		//get mouse position
		int x, y;
		x = input->getMouseX();
		y = input->getMouseY();

		//mouse is left of button
		if (x < uiObjectRef->posX)
			return false;
		//mouse is right of the button
		else if (x > uiObjectRef->posX + width)
			return false;
		//mouse above the button
		else if (y < uiObjectRef->posY)
			return false;
		//mouse below the button
		else if (y > uiObjectRef->posY + height)
			return false;
		else{
			return true;
		}
	}
	return false;
}

bool UIInputComponent::isMouseHovering(int width, int height){

	InputManager* input = InputManager::getInstance();

	int x, y;
	x = input->getMouseX();
	y = input->getMouseY();

	if (x < uiObjectRef->posX)
		return false;
	//mouse is right of the button
	else if (x > uiObjectRef->posX + width)
		return false;
	//mouse above the button
	else if (y < uiObjectRef->posY)
		return false;
	//mouse below the button
	else if (y > uiObjectRef->posY + height)
		return false;
	else{
		return true;
	}
}