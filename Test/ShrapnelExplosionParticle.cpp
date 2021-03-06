#include "ShrapnelExplosionParticle.h"


ShrapnelExplosionParticle::ShrapnelExplosionParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y)
{
	RenderComponent::RenderComponent();
	//gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, x, y, base->getPosZ());
	objRef->toggleVisible();
	baseImage = base->renderResource;
	SDL_Rect baseRect = base->getRenderRect();
	unsigned int scale = 2;
	float size = (float)(baseRect.w/scale);
	float centerX = x;
	float centerY = y;
	for (unsigned int i = 0; i < numParticles; i++){
		SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, centerX, centerY);
		//play->setResourceObject(renderMan->renderText("Timer", 255, 0, 255, 50, "BowlbyOneSC-Regular"));
		sprite->setResourceObject(baseImage);
		int xPos = (baseRect.w - int(size) > 0) ? rand() % (baseRect.w - int(size)) : 0;
		int yPos = (baseRect.h - int(size) > 0) ? rand() % (baseRect.h - int(size)) : 0;
		SDL_Rect rect = { xPos, yPos , (int)size, (int)size };
		sprite->setScaleX(base->getScaleX());
		sprite->setScaleY(base->getScaleY());
		sprite->setRenderRect(rect);
		float u = (float)((rand() % 360) / 360.0);
		float v = (float)((rand() % 360) / 360.0);
		float angle1 = (float)(3.14 * 2 * u);
		float angle2 = acos(2 * v - 1);

		std::list<motion> movements;
		movements.push_back(makeMotion(moveLinearXY(sprite, centerX, centerY, centerX + sin(angle1)*cos(angle2) * 300, centerY + sin(angle1)* sin(angle2) * 300), 0, 1, ease_QuadOut));
		movements.push_back(makeMotion(moveLinearZ(sprite, 0, cos(angle1) * 10), 0, 1, ease_QuadOut));
		movements.push_back(makeMotion(rotateTransform(sprite, rand() % 360, (rand() % 90) - 45), 0, 1));
		Animation * movement = new Animation((float)(1000.0f - (rand() % 200)), movements);
		//int maxtime = 100000; //in seconds
		//std:list<motion> motions;
		particle p;
		p.animations = movement;
		p.sprite = sprite;
		p.timer = 0;
		particles.push_back(p);
	}
}


ShrapnelExplosionParticle::~ShrapnelExplosionParticle()
{
	for (auto iter = particles.begin(); iter != particles.end(); iter++){
	}
}

void ShrapnelExplosionParticle::Update(){
	unsigned int currenttime = clock();
	progress += currenttime - lasttime;
	if (particles.empty()){
		//delete self and remove GameObject from list of objects
		gameObjectRef->isAlive = false;
	}
	for (auto iter = particles.begin(); iter != particles.end();){
		float curr = iter->animations->lengthConversion(progress);
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

void createParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(x, y);

	ShrapnelExplosionParticle* rend = new ShrapnelExplosionParticle(base, numParticles, x, y);
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	rend->gameObjectRef = particleBase;
	GameObjects.AddObject(particleBase);

}