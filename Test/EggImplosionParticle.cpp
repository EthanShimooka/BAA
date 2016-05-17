#include "EggImplosionParticle.h"


EggImplosionParticle::EggImplosionParticle(SDLRenderObject * base, unsigned int divisions, float x, float y)
{
	RenderComponent::RenderComponent();
	//gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* ResMan = ResourceManager::GetResourceManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, x, y, base->getPosZ());
	objRef->toggleVisible();
	//baseImage = base->renderResource;
	//RenderResource * baseImage = (RenderResource*)ResMan->findResourcebyID(74);
	//SDL_Rect baseRect = objRef->getRenderRect();
	//unsigned int scale = 2;
	//float size = baseRect.w / scale;
	float centerX = base->getPosX();
	float centerY = base->getPosY();
	//for (int x = 1; x < float(divisions+1)*2.0; x+=2){ 
	//	for (int y  = 1; y < float(divisions+1)*2.0; y+=2){
	for (int x = 0; x <= divisions; x++){ 
		for (int y = 0; y <= divisions; y++){
			SDLRenderObject * sprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 74, centerX, centerY);
			sprite->setScale(2);
			float yStart = sprite->getWidth() *((x*2+1) / (float(divisions + 1)*2.0) - sprite->getAnchorX());
			float xStart = sprite->getHeight() *((y*2+1) / (float(divisions + 1)*2.0) - sprite->getAnchorY());
			sprite->flipV = true;
			sprite->setPos(centerX, centerY);
			//play->setResourceObject(renderMan->renderText("Timer", 255, 0, 255, 50, "BowlbyOneSC-Regular"));
			sprite->setResourceObject(baseImage);
			SDL_Rect baseRect = sprite->getRenderRect(); 
			/*int xPos = (baseRect.w - int(baseRect.w / (divisions + 1.0)) > 0) ?
						rand() % (baseRect.w - int(baseRect.w / (divisions + 1.0))) : 0;
			int yPos = (baseRect.h - int(baseRect.h / (divisions + 1.0)) > 0) ?
						rand() % (baseRect.h - int(baseRect.h / (divisions + 1.0))) : 0;*/
			int xPos = x * int(baseRect.h / (divisions + 1.0));
			int yPos = y * int(baseRect.h / (divisions + 1.0));
			SDL_Rect rect = { xPos, yPos, round(baseRect.w / (divisions + 1.0)), round(baseRect.h / (divisions + 1.0)) };
			//sprite->setScaleX(base->getScaleX());
			sprite->setRenderRect(rect);
			float u = (rand() % 360) / 360.0;
			float v = (rand() % 360) / 360.0;
			float angle1 = 3.14 * 2 * u;
			float angle2 = acos(2 * v - 1);

			std::list<motion> movements;
			movements.push_back(makeMotion(moveLinearXY(sprite, centerX + sin(angle1)*cos(angle2) * 300,
																centerY + sin(angle1)* sin(angle2) * 300,
																xStart + centerX, yStart+ centerY), 0, 1, ease_QuadOut));
			movements.push_back(makeMotion(moveLinearZ(sprite, cos(angle1) * 10, 0), 0, 1, ease_QuadOut));
			float spinAngle = rand() % 360;
			//movements.push_back(makeMotion(rotateTransform(sprite, rand() % 360, (rand() % 90) - 45), 0, 1));
			movements.push_back(makeMotion(rotateTransform(sprite, spinAngle, -spinAngle+90), 0, 1,ease_QuadOut));
			Animation * movement = new Animation(1000, movements);
			//int maxtime = 100000; //in seconds
			//std:list<motion> motions;
			particle p;
			p.animations = movement;
			p.sprite = sprite;
			p.timer = 0;
			particles.push_back(p);
		}
	}
}


EggImplosionParticle::~EggImplosionParticle()
{
	for (auto iter = particles.begin(); iter != particles.end(); iter++){
	}
}

void EggImplosionParticle::Update(){
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
void createEggParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y){
	GameObject* particleBase = new GameObject();
	particleBase->isAlive = true;
	particleBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	particleBase->setPos(x, y);

	EggImplosionParticle* rend = new EggImplosionParticle(base, numParticles, x, y);
	particleBase->AddComponent(COMPONENT_RENDER, rend);
	GameObjects.AddObject(particleBase);

}