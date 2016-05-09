#pragma once
#include "ParticleRenderComponent.h"
#include "SystemGameObjectQueue.h"

class ShrapnelExplosionParticle :
	public ParticleRenderComponent
{
public:
	ShrapnelExplosionParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y);
	~ShrapnelExplosionParticle();
	void Update();
	RenderResource * baseImage;
	std::list<particle> particles;
};

void createParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y);
