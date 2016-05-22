#include "ChargeParticle.h"


ChargeParticle::ChargeParticle(GameObject * source, PlayerLogicComponent * logic, unsigned int numParticles,
							   unsigned int frequency, float offsetX, float offsetY, float width, float height)
{
	RenderComponent::RenderComponent();
	//gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	parentObject = source;
	numberOfParticles = numParticles;
	frequencyOfParticles = frequency;
	alive = true;
	posX = offsetX;
	posY = offsetY;
	w = width;
	h = height;
	//std::function<bool(void)> charge = isCharging;
	PlayerLogicComponent * logicComponent = logic;
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, parentObject->posX, parentObject->posY);
	objRef->toggleVisible();
}


ChargeParticle::~ChargeParticle()
{
}

void ChargeParticle::Update(){
	if (!parentObject || !(parentObject->isAlive)){
		alive = false;
	}
	unsigned int currenttime = clock();
	unsigned int oldTime = progress;
	progress += currenttime - lasttime;
	PlayerLogicComponent *  log = dynamic_cast<PlayerLogicComponent * >( parentObject->GetComponent(COMPONENT_LOGIC));
	if (alive && log->charging && ((currenttime - lasttime) > frequencyOfParticles ||
							 oldTime%frequencyOfParticles > progress%frequencyOfParticles)){
		SceneManager* sceneMan = SceneManager::GetSceneManager();
		RenderManager* renderMan = RenderManager::getRenderManager();
		float centerX = parentObject->posX + posX;
		float centerY = parentObject->posY + posY;
		for (unsigned int i = 0; i < numberOfParticles; i++){
			float x = i*(w / (numberOfParticles - 1)) - (w / 2);
			float y = 0;
			float dx = i*((w*1.5f) / (numberOfParticles - 1)) - ((w*1.5f) / 2);
			float a = (i - ((float(numberOfParticles) - 1.0f)) / 2.0f);
			float b = (float(numberOfParticles) - 1.0f) / 2.0f;
			float heightDif = (a / b)*(a / b);
			float dy = -h + h*(0.2f)*heightDif;
			float size = 0.2f;
			SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 4004, x, y);
			//play->setResourceObject(renderMan->renderText("Timer", 255, 0, 255, 50, "BowlbyOneSC-Regular"));
			//sprite->setScaleX(base->getScaleX());
			//sprite->setScaleY(base->getScaleY());
			//sprite->setRenderRect(rect);
			std::list<motion> movements;
			movements.push_back(makeMotion(moveLinearXY(sprite, centerX + x, centerY + y, centerX + dx, centerY + dy), 0, 1, ease_QuadOut));
			movements.push_back(makeMotion(resizeSquareTransform(sprite, size, 0.01f), 0.0f, 1.0f, ease_QuadIn));
			//movements.push_back(makeMotion(keyframeAnimate(sprite, 0, 3), 0.0, 1.0, ease_QuadIn));
			//movements.push_back(makeMotion(moveLinearZ(sprite, 0, cos(angle1) * 10), 0, 1, ease_QuadOut));
			//movements.push_back(makeMotion(rotateTransform(sprite, rand() % 360, (rand() % 90) - 45), 0, 1));
			Animation * movement = new Animation((float)(500 - (rand() % 100)), movements);
			//int maxtime = 100000; //in seconds
			//std:list<motion> motions;
			particle p;
			p.animations = movement;
			p.sprite = sprite;
			p.timer = (float)progress;
			particles.push_back(p);
		}
	}
	if (particles.empty() && !alive){
		//delete self and remove GameObject from list of objects
		gameObjectRef->isAlive = false;
	}
	for (auto iter = particles.begin(); iter != particles.end();){
		float curr = iter->animations->lengthConversion((int)(progress - iter->timer));
		//if (curr >= 1.0) iter->sprite->setIfRenderImage(false);
		if (curr >= 1.0){
			//iter->sprite->setIfRenderImage(false);
			delete iter->animations;
			SceneManager* sceneMan = SceneManager::GetSceneManager();
			sceneMan->RemoveObject(iter->sprite, sceneMan->findLayer("layer2"));
			auto toErase = iter;
			iter++;
			particles.erase(toErase);
		}
		else{
			iter->animations->animate(curr);
			iter++;
		}
	}
	lasttime = currenttime;
}

ChargeParticle * createChargeParticle(GameObject * source, PlayerLogicComponent * logic, unsigned int numParticles,
										unsigned int frequency, float offsetX, float offsetY, float width, float height){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(0, 0);

	ChargeParticle* rend = new ChargeParticle(source, logic, numParticles, frequency, offsetX, offsetY, width, height );
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	rend->gameObjectRef = particleBase;
	GameObjects.AddObject(particleBase);
	return rend;
}