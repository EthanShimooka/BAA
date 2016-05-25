#include "FeatherZoomParticle.h"


FeatherZoomParticle::FeatherZoomParticle(GameObject * source, unsigned int numParticles, unsigned int frequency)
{
	RenderComponent::RenderComponent();
	//gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	parentObject = source;
	numberOfParticles = numParticles;
	frequencyOfParticles = frequency;
	alive = true;
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, parentObject->posX, parentObject->posY);
	objRef->toggleVisible();
}


FeatherZoomParticle::~FeatherZoomParticle()
{
	for (auto iter = particles.begin(); iter != particles.end();){
		delete iter->animations;
		SceneManager* sceneMan = SceneManager::GetSceneManager();
		sceneMan->RemoveObject(iter->sprite);
		auto toErase = iter;
		iter++;
		particles.erase(toErase);
	}
}

void FeatherZoomParticle::Update(){
	if (!parentObject || !(parentObject->isAlive)){
		alive = false;
	}
	unsigned int currenttime = clock();
	unsigned int oldTime = progress;
	progress += currenttime - lasttime;
	if (alive && ((currenttime - lasttime) > frequencyOfParticles || oldTime%frequencyOfParticles > progress%frequencyOfParticles)){
		SceneManager* sceneMan = SceneManager::GetSceneManager();
		RenderManager* renderMan = RenderManager::getRenderManager();
		//SDL_Rect baseRect = parent->getRenderRect();
		//unsigned int scale = 2;
		//float size = baseRect.w / scale;
		float centerX = parentObject->posX;
		float centerY = parentObject->posY;
		for (unsigned int i = 0; i < numberOfParticles; i++){
			SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 4002, centerX, centerY,0.1f);
			//play->setResourceObject(renderMan->renderText("Timer", 255, 0, 255, 50, "BowlbyOneSC-Regular"));
			//sprite->setScaleX(base->getScaleX());
			//sprite->setScaleY(base->getScaleY());
			//sprite->setRenderRect(rect);
			float angle1 = (30 - (rand() % 60)) + parentObject->rotation;
			sprite->setRotation(angle1);
			std::list<motion> movements;
			movements.push_back(makeMotion(resizeSquareTransform(sprite, 0.01f,0.5f), 0.0f, 0.5f, ease_QuadOut));
			movements.push_back(makeMotion(resizeSquareTransform(sprite, 0.5f, 0.01f), 0.5f, 1.0f, ease_QuadIn));
			movements.push_back(makeMotion(keyframeAnimate(sprite,0,3), 0.0, 1.0, ease_QuadIn));
			//movements.push_back(makeMotion(moveLinearXY(sprite, centerX, centerY, centerX + rand() % 20 - 40, centerY +rand() % 20 - 40), 0, 1, ease_QuadOut));
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
		float curr = iter->animations->lengthConversion((int)(progress-iter->timer));
		//if (curr >= 1.0) iter->sprite->setIfRenderImage(false);
		if (curr >= 1.0){
			//iter->sprite->setIfRenderImage(false);
			delete iter->animations;
			SceneManager* sceneMan = SceneManager::GetSceneManager();
			sceneMan->RemoveObject(iter->sprite);
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

void createFeatherParticle(GameObject * source, unsigned int numParticles, unsigned int frequency){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(0, 0);

	FeatherZoomParticle* rend = new FeatherZoomParticle(source, numParticles, frequency);
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	rend->gameObjectRef = particleBase;
	GameObjects.AddObject(particleBase);

}