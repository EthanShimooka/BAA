#pragma once
#include "ParticleRenderComponent.h"
#include "PlayerInputComponent.h"

class ChargeParticle :
	public ParticleRenderComponent
{
private:
	bool alive;
	float posX, posY, w, h;
public:
	ChargeParticle(GameObject * source, PlayerLogicComponent * logic, unsigned int numParticles,
					unsigned int frequency, float offsetX, float offsetY, float width, float height);
	~ChargeParticle();
	void Update();
	GameObject * parentObject;
	std::list<particle> particles;
	unsigned int numberOfParticles;
	unsigned int frequencyOfParticles;
	//std::function<bool(void)> charge;
	PlayerLogicComponent * logicComponent;
	void turnOn();
	void turnOff();
};

ChargeParticle * createChargeParticle(GameObject * source, PlayerLogicComponent * logic, unsigned int numParticles,
										unsigned int frequency, float offsetX, float offsetY, float width, float height);
