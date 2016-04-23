#pragma once
#ifndef EFFECTRENDERCOMPONENT_H_INCLUDED
#define EFFECTRENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
#include "include\SceneManager.h"
#include "MinionObjectFactory.h"
#include "Invoke.h"
class EffectRenderComponent : public RenderComponent
{
public:
	/// Constructor
	EffectRenderComponent(GameObject* effect, int effectType);
	/// Destructor
	~EffectRenderComponent();
	/// Update
	void Update();
	/// Gets rid of the effect
	void DestroyEffect();
	bool explosionTriggered = false;
};

#endif