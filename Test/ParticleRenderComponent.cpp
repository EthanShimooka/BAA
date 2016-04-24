#include "ParticleRenderComponent.h"


ParticleRenderComponent::ParticleRenderComponent(SDLRenderObject * base, unsigned int numParticles,float x, float y)
{
	RenderComponent::RenderComponent();
	//gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1 ,x, y, base->getPosZ());
	objRef->toggleVisible();
	baseImage = base->renderResource;
	SDL_Rect baseRect = base->getRenderRect();
	float size = baseRect.w/5;
	float centerX = x;
	float centerY = y;
	for (unsigned int i = 0; i < numParticles; i++){
		SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, centerX, centerY);
		//play->setResourceObject(renderMan->renderText("Timer", 255, 0, 255, 50, "BowlbyOneSC-Regular"));
		sprite->setResourceObject(baseImage);
		SDL_Rect rect = { rand() % (baseRect.w-int(size)), rand() % (baseRect.h-int(size)),size,size};
		sprite->setRenderRect(rect);
		float angle = (rand() % 360)*3.14/180;
		std::list<motion> movements;
		movements.push_back(makeMotion(moveLinearXY(sprite, centerX, centerY, centerX + cos(angle) * 300, centerY+sin(angle) * 300), 0, 1, ease_QuadOut));
		movements.push_back(makeMotion(rotateTransform(sprite,rand()%360,(rand()%90)-45), 0, 1, ease_QuadOut));
		Animation * movement = new Animation(1000-(rand()%200),movements);
		//int maxtime = 100000; //in seconds
		//std:list<motion> motions;
		particle p;
		p.animations = movement;
		p.sprite = sprite;
		p.timer = 0;
		particles.push_back(p);
	}
}


ParticleRenderComponent::~ParticleRenderComponent()
{
	for (auto iter = particles.begin(); iter != particles.end(); iter++){
		delete iter->animations;
	}
}

void ParticleRenderComponent::Update(){
	unsigned int currenttime = clock();
	progress += currenttime - lasttime;
	for (auto iter = particles.begin(); iter != particles.end(); iter++){
		float curr = iter->animations->lengthConversion(progress);
		if (curr >= 1.0) iter->sprite->setIfRenderImage(false);
		else iter->animations->animate(curr);
	}
	lasttime = currenttime;
	
}

void createParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(x, y);

	ParticleRenderComponent* rend = new ParticleRenderComponent(base, numParticles, x, y);
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	GameObjects.AddObject(particleBase);
	//FeatherNetworkComponent* net;
		//feather = new GameObject();
		//feather->ID = PID;
		//feather->isAlive = true;
		//feather->type = GAMEOBJECT_TYPE::OBJECT_FEATHER;
		//feather->team = owner->team;
		//feather->setPos(posX, posY);
		//rend = new FeatherRenderComponent(feather);
		//logic->owner = owner;

	// Feather Specific Render Component. In future will have flag
	// for type of class,  which will instatiate based on flag



	//return feather;
}