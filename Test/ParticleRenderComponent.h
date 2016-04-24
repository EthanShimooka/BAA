#pragma once
#include "RenderComponent.h"
#include "SystemGameObjectQueue.h"

class ParticleRenderComponent :
	public RenderComponent
{
public:
	ParticleRenderComponent(SDLRenderObject * base,unsigned int numParticles,float x, float y);
	~ParticleRenderComponent();
	void Update();
	RenderResource * baseImage;
	struct particle{
		SDLRenderObject * sprite;
		Animation * animations;
		float timer = 0.0;
	};
	std::list<particle> particles;
};

void createParticle(SDLRenderObject * base, unsigned int numParticles,float x,float y);
