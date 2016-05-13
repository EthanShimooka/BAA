#include "AbsorbParticle.h"


AbsorbParticle::AbsorbParticle(GameObject * startObj, GameObject * goalObj, unsigned int numParticles, float offsetX, float offsetY)
{
	RenderComponent::RenderComponent();
	//gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	goal = goalObj;
	numberOfParticles = numParticles;
	alive = true;
	posX = startObj->posX;
	posY = startObj->posY;
	posXOff = offsetX;
	posYOff = offsetY;
	//std::function<bool(void)> charge = isCharging;
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, startObj->posX, startObj->posY);
	objRef->toggleVisible();
	float centerX = goal->posX;
	float centerY = goal->posY;
	for (unsigned int i = 0; i < numberOfParticles; i++){
		//float x = i*(w / (numberOfParticles - 1)) - (w / 2);
		//float y = 0;
		//float dx = i*((w*1.5) / (numberOfParticles - 1)) - ((w*1.5) / 2);
		//float a = (i - ((float(numberOfParticles) - 1.0)) / 2.0);
		//float b = (float(numberOfParticles) - 1.0) / 2.0;
		//float heightDif = (a / b)*(a / b);
		//float dy = -h + h*(0.2)*heightDif;
		//float size = 0.2;
		SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 4004, posX,posY);
		//play->setResourceObject(renderMan->renderText("Timer", 255, 0, 255, 50, "BowlbyOneSC-Regular"));
		sprite->setScale(1);
		//sprite->setScaleX(base->getScaleX());
		//sprite->setScaleY(base->getScaleY());
		//sprite->setRenderRect(rect);

		float u = (rand() % 360) / 360.0;
		float v = (rand() % 360) / 360.0;
		float angle1 = 3.14 * 2 * u;
		float angle2 = acos(2 * v - 1);
		std::list<motion> movements;
		//auto bezierX = getBezier(posX, posX + sin(angle1)*cos(angle2) * 200, goal->posX, goal->posX);
		//auto bezierY = getBezier(posY, posY + sin(angle1)*sin(angle2) * 200, goal->posY, goal->posY);
		auto bezierX = getBezierTracking(posX, posX + sin(angle1)*cos(angle2) * 200, goal->posX, &(goal->posX));
		auto bezierY = getBezierTracking(posY, posY + sin(angle1)*sin(angle2) * 200, goal->posY, &(goal->posY));
		movements.push_back(makeMotion(moveLinearXY(sprite, posX, posY, goal->posX, goal->posY), 0, 1, ease_QuadIn));
		movements.push_back(makeMotion(moveBezierXY(sprite,bezierX,bezierY), 0, 1, ease_QuadIn));
		//movements.push_back(makeMotion(resizeSquareTransform(sprite, size, 0.01), 0.0, 1.0, ease_QuadIn));
		//movements.push_back(makeMotion(keyframeAnimate(sprite, 0, 3), 0.0, 1.0, ease_QuadIn));
		//movements.push_back(makeMotion(moveLinearZ(sprite, 0, cos(angle1) * 10), 0, 1, ease_QuadOut));
		//movements.push_back(makeMotion(rotateTransform(sprite, rand() % 360, (rand() % 90) - 45), 0, 1));
		Animation * movement = new Animation(1000 - (rand() % 200), movements);
		//int maxtime = 100000; //in seconds
		//std:list<motion> motions;
		particle p;
		p.animations = movement;
		p.sprite = sprite;
		p.timer = progress;
		particles.push_back(p);
	}
}


AbsorbParticle::~AbsorbParticle()
{
}

void AbsorbParticle::Update(){
	if (!goal || !(goal->isAlive)){
		alive = false;
	}
	unsigned int currenttime = clock();
	unsigned int oldTime = progress;
	progress += currenttime - lasttime;
	//PlayerLogicComponent *  log = dynamic_cast<PlayerLogicComponent * >(parentObject->GetComponent(COMPONENT_LOGIC));
	if (alive){
		
	}
	if (particles.empty() && !alive){
		//delete self and remove GameObject from list of objects
	}
	for (auto iter = particles.begin(); iter != particles.end();){
		float curr = iter->animations->lengthConversion(progress - iter->timer);
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

void createAbsorbParticle(GameObject * startObj, GameObject * goalObj, unsigned int numParticles,float offsetX, float offsetY){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(0, 0);
	AbsorbParticle* rend = new AbsorbParticle(startObj, goalObj, numParticles,offsetX, offsetY);
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	GameObjects.AddObject(particleBase);
}
