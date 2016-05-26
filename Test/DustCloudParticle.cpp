#include "DustCloudParticle.h"


DustCloudParticle::DustCloudParticle(unsigned int numParticles, float minSize, float maxSize, float xPos, float yPos)
{
	RenderComponent::RenderComponent();
	//gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* ResMan = ResourceManager::GetResourceManager();
	//RenderResource * originalImage = ;
	//std::function<bool(void)> charge = isCharging;
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, xPos, yPos);
	objRef->toggleVisible();
	for (unsigned int i = 0; i < numParticles; i++){
		SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, xPos, yPos);
		RenderResource * resource = new RenderResource((RenderResource*)ResMan->findResourcebyID(4001));
		resource->load();
		sprite->setResourceObject(resource);
		sprite->setScale(sprite->calcXScale(minSize + (maxSize-minSize)*(rand()%100)/100));
		std::list<motion> movements;
		movements.push_back(makeMotion(moveLinearXY(sprite, xPos, yPos, xPos+ 40 -(rand() % 80),
													yPos + 40 - (rand() % 80)),0, 1, ease_QuadIn));
		movements.push_back(makeMotion(rotateTransform(sprite, rand() % 360, (rand() % 90) - 45), 0, 1));
		Animation * movement = new Animation((float)(700 - (rand() % 200)), movements);
		particle p;
		p.animations = movement;
		p.sprite = sprite;
		p.timer = (float)progress;
		particles.push_back(p);
	}
}


DustCloudParticle::~DustCloudParticle()
{
}


void DustCloudParticle::Update(){
	unsigned int currenttime = clock();
	unsigned int oldTime = progress;
	progress += currenttime - lasttime;
	//PlayerLogicComponent *  log = dynamic_cast<PlayerLogicComponent * >(parentObject->GetComponent(COMPONENT_LOGIC));
	//if (alive){}
	if (particles.empty()){
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
			sceneMan->RemoveObject(iter->sprite);
			iter->sprite->renderResource->unload();
			delete iter->sprite->renderResource;
			auto toErase = iter;
			iter++;
			particles.erase(toErase);
		}
		else{
			iter->animations->animate(curr);
			//float parab = curr < 0.5 ? ease_QuadOut(curr * 2) : ease_QuadIn(1-(curr-0.5) * 2);
			iter->sprite->renderResource->setAlpha((Uint8)(255 *ease_QuadOut(1.0f-curr)*0.75f));
			//iter->sprite->renderResource->setColor(rand() % 255, 255, rand() % 255);
			iter++;
		}
	}
	lasttime = currenttime;
}

void createDustCloudParticle(unsigned int numParticles, float minSize, float maxSize, float xPos, float yPos){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(xPos, yPos);

	DustCloudParticle* rend = new DustCloudParticle(numParticles, minSize,maxSize,xPos, yPos);
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	rend->gameObjectRef = particleBase;
	GameObjects.AddObject(particleBase);

}