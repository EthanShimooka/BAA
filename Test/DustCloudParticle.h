#pragma once
#include "ParticleRenderComponent.h"
class DustCloudParticle :
	public ParticleRenderComponent
{
public:
	DustCloudParticle(unsigned int numParticles, float minSize, float maxSize, float xPos,float yPos);
	~DustCloudParticle();
	std::list<particle> particles;
	void Update();
};

void createDustCloudParticle(unsigned int numParticles, float minSize, float maxSize, float xPos, float yPos);
