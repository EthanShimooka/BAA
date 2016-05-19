#pragma once
#include "ParticleRenderComponent.h"
class EggImplosionParticle :
	public ParticleRenderComponent
{
public:
	EggImplosionParticle(SDLRenderObject * base, unsigned int divisions, float x, float y);
	~EggImplosionParticle();
	void Update();
	RenderResource * baseImage;
	std::list<particle> particles;
};


void createEggParticle(SDLRenderObject * base, unsigned int numParticles, float x, float y);
