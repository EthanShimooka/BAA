#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	visible = true;
	lasttime = clock();
	progress = 0;

}


RenderComponent::~RenderComponent()
{
}

/// Assign a Diffrent SDL render Object
void RenderComponent::AddBoundingBox(){
	/*SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 10, 10);
	box->setIfRenderRect(true);
	box->setParent(base);
	allObjs["box"] = box;*/
}
void RenderComponent::AssignSprite(SDLRenderObject* rend){

	objRef = rend;
}


/// Sets the next animation given a string value found in a hashtable

void RenderComponent::setAnimation(std::string name){
	if (animations.count(name)){
		nextAnimation = animations[name];
	}
}

/// The general animation function, that alters the object's

void RenderComponent::animate(){
	unsigned int currenttime = clock();
	if (currentAnimation){
		progress += currenttime - lasttime;
		while (progress >= currentAnimation->duration){
			progress -= currentAnimation->duration;
			if (nextAnimation){
				currentAnimation = nextAnimation;
				//queue next animation through a switch statement
			}
			else{
				currentAnimation = animations["idle"];
			}
		}
		float curr = currentAnimation->lengthConversion(progress);
		auto len = currentAnimation->duration;
		currentAnimation->animate(curr);
	}
	lasttime = currenttime;
}

/// Updates SDL render Object from Move Data in game
void RenderComponent::RenderBoundingBox(SDLRenderObject* boxRender){
	PhysicsComponent* physics = dynamic_cast<PhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	//PlayerPhysicsComponent* physics = gameObjectRef->GetComponent(COMPONENT_PHYSICS)
	//box->setRenderRect((physics->mBody->GetUserData()).getWidth(), (physics->mBody->GetUserData()).getHeight() );
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
	boxRender->setRenderRect(round(aabb.upperBound.x - aabb.lowerBound.x), round(aabb.upperBound.y - aabb.lowerBound.y));
	boxRender->setPos(physics->mBody->GetPosition().x, physics->mBody->GetPosition().y);
	ApplyPhysicsRotation(boxRender);
}
void RenderComponent::ApplyPhysicsRotation(SDLRenderObject* render){
	PhysicsComponent* physics = dynamic_cast<PhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	render->setRotation(physics->mBody->GetAngle() * 180 / M_PI);
}
void RenderComponent::Update(){

	//Updates the related SDLRenderObject with the player's values
	//The SDLRenderObject is was is showed on screen, but is only 
	//a 'figurehead' for the player object 

	objRef->posX = gameObjectRef->posX;
	objRef->posY = gameObjectRef->posY;
	objRef->flipH = gameObjectRef->flipH;
	objRef->flipV = gameObjectRef->flipV;
	objRef->setScale(gameObjectRef->scaleX, gameObjectRef->scaleY);
	objRef->rotation = gameObjectRef->rotation;
	objRef->visible = visible;

	//there is most likely more attributes to send over. update as needed
}


