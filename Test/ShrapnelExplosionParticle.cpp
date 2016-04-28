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
	float size = baseRect.w / 5;
	float centerX = x;
	float centerY = y;
	for (unsigned int i = 0; i < numParticles; i++){
		SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, centerX, centerY);
		//play->setResourceObject(renderMan->renderText("Timer", 255, 0, 255, 50, "BowlbyOneSC-Regular"));
		sprite->setResourceObject(baseImage);
		SDL_Rect rect = { rand() % (baseRect.w - int(size)), rand() % (baseRect.h - int(size)), size, size };
		sprite->setRenderRect(rect);
		float u = (rand() % 360) / 360.0;
		float v = (rand() % 360) / 360.0;
		float angle1 = 3.14 * 2 * u;
		float angle2 = acos(2 * v - 1);

		std::list<motion> movements;
		movements.push_back(makeMotion(moveLinearXY(sprite, centerX, centerY, centerX + sin(angle1)*cos(angle2) * 300, centerY + sin(angle1)* sin(angle2) * 300), 0, 1, ease_QuadOut));
		movements.push_back(makeMotion(moveLinearZ(sprite, 0, cos(angle1) * 10), 0, 1, ease_QuadOut));
		movements.push_back(makeMotion(rotateTransform(sprite, rand() % 360, (rand() % 90) - 45), 0, 1));
		Animation * movement = new Animation(1000 - (rand() % 200), movements);
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
	}
	for (auto iter = particles.begin(); iter != particles.end();){
		float curr = iter->animations->lengthConversion(progress);
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

void createParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(x, y);

	ShrapnelExplosionParticle* rend = new ShrapnelExplosionParticle(base, numParticles, x, y);
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	GameObjects.AddObject(particleBase);

}