#pragma once
#include "RenderComponent.h"
#include "SystemGameObjectQueue.h"

class ParticleRenderComponent :
	public RenderComponent
{
public:
	ParticleRenderComponent();
	~ParticleRenderComponent();
	virtual void Update();
	struct particle{
		SDLRenderObject * sprite;
		Animation * animations;
		float timer = 0.0;
	};
};

void createParticle();
