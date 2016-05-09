#pragma once
#include "ParticleRenderComponent.h"
class FeatherZoomParticle :
	public ParticleRenderComponent
{
public:
	FeatherZoomParticle(GameObject * source, unsigned int numParticles, unsigned int frequency);
	~FeatherZoomParticle();
	void Update();
	GameObject * parentObject;
	std::list<particle> particles;
	unsigned int numberOfParticles;
	unsigned int frequencyOfParticles;
	bool alive;
};

void createFeatherParticle(GameObject * source, unsigned int numParticles, unsigned int frequency);