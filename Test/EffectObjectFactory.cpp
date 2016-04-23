#include "EffectObjectFactory.h"


EffectObjectFactory::EffectObjectFactory()
{
}


EffectObjectFactory::~EffectObjectFactory()
{
}


/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* EffectObjectFactory::Spawn(float posX, float posY, int effectType)
{
	GameObject* effect;

	EffectRenderComponent* rend;

	effect = new GameObject();
	effect->isAlive = true;
	effect->type = GAMEOBJECT_TYPE::OBJECT_EFFECT;
	effect->setPos(posX, posY);

	rend = new EffectRenderComponent(effect, effectType);

	return effect;
}