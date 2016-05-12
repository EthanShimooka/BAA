#pragma once
#include "ParticleRenderComponent.h"
class AbsorbParticle :
	public ParticleRenderComponent
{
private:
	bool alive;
	float posX, posY, posXOff,posYOff;
public:
	AbsorbParticle(GameObject * startObj, GameObject * goalObj, unsigned int numParticles, float offsetX, float offsetY);
	~AbsorbParticle();
	void Update();
	GameObject * goal;
	std::list<particle> particles;
	unsigned int numberOfParticles;
	//std::function<bool(void)> charge;
	void turnOn();
	void turnOff();
};

void createAbsorbParticle(GameObject * startObj, GameObject * goalObj, unsigned int numParticles, float offsetX, float offsetY);
