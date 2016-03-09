#include "PlayerRenderComponent.h"
#include "include\AnimationLibrary.h"

PlayerRenderComponent::PlayerRenderComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();

	SceneManager* sceneMan = SceneManager::GetSceneManager();

	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 0, 0, 0);
	base->toggleIfRenderImage();
	SDLRenderObject * armL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100103, 0, 0);
	//armL->setPosZ(0.5);
	SDLRenderObject * legL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100105, 30, 300);
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100101, 0, 0);
	SDLRenderObject * legR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100104, 50, 300);
	SDLRenderObject * armR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100102, 0, 0);
	
	//PlayerPhysicsComponent pos = gameObjectRef->GetComponent(COMPONENT_PHYSICS); 
	SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0,10,10);
	box->setIfRenderRect(true);
	
	//objRef->setAnchor(0.5, 0.5);
	
	armR->setAnchor(174 / double(armR->renderRect.w), 154 / double(armR->renderRect.h));
	armL->setAnchor(178 / double(armL->renderRect.w), 168 / double(armL->renderRect.h)); 
	legR->setAnchor(128 / double(legR->renderRect.w),  39 / double(legR->renderRect.h));
	legL->setAnchor(253 / double(legL->renderRect.w),  62 / double(legL->renderRect.h));
	//armR->setCurrentFrame(1);
	body->setParent(base);
	armL->setParent(body);
	armR->setParent(body);
	legL->setParent(body);
	legR->setParent(body);
	box->setParent(base);
	body->setScale(0.1);
	objRef = base;
	allObjs["base"] = base;
	allObjs["box"] = box;
	allObjs["body"] = body;
	allObjs["legL"] = legL;
	allObjs["legR"] = legR;
	allObjs["armL"] = armL;
	allObjs["armR"] = armR;
	
	//Animation* idle = new Animation();
	//idle->duration = 20;
	list<motion> motions;
	motions.push_back(makeMotion(moveCircArc(armR, 0, 50, 50, 0, 360), 0, 1));
	motions.push_back(makeMotion(moveCircArc(armL, 0, 50, 50, 180, 360), 0, 1));
	Animation* idle = new Animation(400,motions);
	animations["idle"] = idle;
	auto ani = animations["idle"];
	auto ani2 = &animations["idle"];
	//auto mot = idle.motions.begin();
	currentAnimation = idle;
	//currentAnimation;
}


PlayerRenderComponent::~PlayerRenderComponent()
{
}

void PlayerRenderComponent::RenderPhysics(){
	PlayerPhysicsComponent* physics = dynamic_cast<PlayerPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	//PlayerPhysicsComponent* physics = gameObjectRef->GetComponent(COMPONENT_PHYSICS)
	//allObjs["box"]->setRenderRect((physics->mBody->GetUserData()).getWidth(), (physics->mBody->GetUserData()).getHeight() );
	b2AABB aabb;
	b2Transform t;
	t.SetIdentity();
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	b2Fixture* fixture = physics->mBody->GetFixtureList();
	while (fixture != NULL)
	{
		//aabb.Combine(aabb, fixture->GetAABB());
		const b2Shape *shape = fixture->GetShape();
		const int childCount = shape->GetChildCount();
		for (int child = 0; child < childCount; ++child) {
			const b2Vec2 r(shape->m_radius, shape->m_radius);
			b2AABB shapeAABB;
			shape->ComputeAABB(&shapeAABB, t, child);
			shapeAABB.lowerBound = shapeAABB.lowerBound + r;
			shapeAABB.upperBound = shapeAABB.upperBound - r;
			aabb.Combine(shapeAABB);
		}
		fixture = fixture->GetNext();
	}
	allObjs["box"]->setRenderRect(round(aabb.upperBound.x - aabb.lowerBound.x), round(aabb.upperBound.y- aabb.lowerBound.y));
}

void PlayerRenderComponent::Update(){
	RenderComponent::Update();
	RenderPhysics();
	RenderComponent::animate();
}


