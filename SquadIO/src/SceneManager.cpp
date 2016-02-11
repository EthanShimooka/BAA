#pragma once
#include "include\SceneManager.h"

///////////////////////////////////////////////////////////////////////////////

bool compareLayerOrder(const Layer* lhs, const Layer* rhs){
	return lhs->m_ZOrder < rhs->m_ZOrder;
}

///////////////////////////////////////////////////////////////////////////////

SceneManager SceneManager::sceneManager;

SceneManager::SceneManager(){}

SceneManager* SceneManager::GetSceneManager()
{
	return &sceneManager;
}

///////////////////////////////////////////////////////////////////////////////

Layer::Layer() : EngineObject() {
	m_Visible = true;
	m_PosX = m_PosY = 0.0f;
	m_ZOrder = 0;
}

///////////////////////////////////////////////////////////////////////////////

Layer* SceneManager::addLayer(std::string Name) {
	Layer* layer = findLayer(Name);

	if (!layer) {
		layer = new Layer();
		layer->m_Name = Name;
		m_Layers.push_back(layer);
	}
	return layer;
}

///////////////////////////////////////////////////////////////////////////////

Layer* SceneManager::findLayer(std::string Name) {
	std::list<Layer*>::iterator list_it;
	//render all associated render objects
	for (list_it = m_Layers.begin(); list_it != m_Layers.end(); list_it++){
		if ((*list_it)->m_Name == Name){
			return(*list_it);
		}
	}
	//THROW_EXCEPTION(301, "Failed to find layer in SceneManager");
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////

void SceneManager::removeLayer(std::string Name){
	std::list<Layer*>::iterator list_it;
	//render all associated render objects
	for (list_it = m_Layers.begin(); list_it != m_Layers.end(); list_it++){
		if ((*list_it)->m_Name == Name){
			m_Layers.remove(*list_it);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void SceneManager::addLayerObjects(Layer* layer, tinyxml2::XMLElement* element) {
	SDLRenderObject* object = new SDLRenderObject();
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;

	if (!object)
		return;
	
	for (const tinyxml2::XMLAttribute* ElementAttrib = element->FirstAttribute(); ElementAttrib; ElementAttrib = ElementAttrib->Next()) {
		std::string AttribName = ElementAttrib->Name();
		std::string AttribValue = ElementAttrib->Value();
		if (AttribName == "resourceID"){
			ResourceManager* ResMan = ResourceManager::GetResourceManager();

			object->setResourceObject((RenderResource*) ResMan->findResourcebyID(atoi(AttribValue.c_str())));
		}

		if (AttribName == "posx") {
			float x = (float)atof(AttribValue.c_str());
			object->posX = (float)atof(AttribValue.c_str());		}
		if (AttribName == "posy") {
			object->posY = (float)atof(AttribValue.c_str());
		}

		if (AttribName == "visible"){
			if (AttribValue == "true")
				object->visible = true;
			else
				object->visible = false;
		}

		if (AttribName == "colorkey"){
			if (AttribValue == "true")
				object->colorKeyEnabled = true;
			else
				object->colorKeyEnabled = false;
		}

		if (AttribName == "r") {
			r = atoi(AttribValue.c_str());
		}
		if (AttribName == "g") {
			g = atoi(AttribValue.c_str());
		}
		if (AttribName == "b") {
			b = atoi(AttribValue.c_str());
		}
	}
	
	//if (object->colorKeyEnabled)
		//object->setColorKey(r, g, b);

	//probably will want physics features to be assigned here
	layer->m_SceneObjects.push_back(object);
}

////////////////////////////////////////////////////////////////////////////////////////////////

bool SceneManager::loadFromXMLFile(std::string Filename) {
	LogManager* log = LogManager::GetLogManager(); //debug

	tinyxml2::XMLDocument doc;
	std::list<Layer*> list;

	std::string path = "resources\\" + Filename;
	//std::string path = Filename;
	doc.LoadFile(path.c_str());
	if (doc.ErrorID() == 0){
		//find resources node
		tinyxml2::XMLNode* ResourceTree = doc.FirstChildElement("scene");
		
		if (ResourceTree) {
			//Enumerate resource objects
			for (tinyxml2::XMLNode* child = ResourceTree->FirstChild(); child; child = child->NextSibling()) {
				tinyxml2::XMLElement* element = child->ToElement();

				if (element) {
					Layer* layer = new Layer();
					layer->m_ZOrder = m_Layers.size();

					for (const tinyxml2::XMLAttribute* ElementAttrib = element->FirstAttribute(); ElementAttrib; ElementAttrib = ElementAttrib->Next()){
						//examine layers
						std::string AttribName = ElementAttrib->Name();
						std::string AttribValue = ElementAttrib->Value();

						//detect resource type. graphic? audio? text?
						if (AttribName == "name"){
							layer->m_Name = AttribValue;
							continue;
						}

						if (AttribName == "posx"){
							layer->m_PosX = (float)atof(AttribValue.c_str());
						}

						if (AttribName == "posy"){
							layer->m_PosY = (float)atof(AttribValue.c_str());
						}

						if (AttribName == "visible"){
							if (AttribValue == "true")
								layer->m_Visible = true;
							else
								layer->m_Visible = false;
						}
					} // end XMLAttribute loop

					m_Layers.push_back(layer);
					log->logBuffer << "Size of layers : "<< m_Layers.size() << std::endl;
					log->flush();

					//cycle through layer objects
					for (tinyxml2::XMLNode* objs = child->FirstChild(); objs; objs = objs->NextSibling()) {
						if (std::string(objs->Value()) == "objects") {
							for (tinyxml2::XMLNode* obj = objs->FirstChild(); obj; obj = obj->NextSibling()) {
								tinyxml2::XMLElement* objElement = obj->ToElement();

								addLayerObjects(layer, objElement);
							}
						}
					}
				}
			} // end XMLNode loop
			sortLayers();
			return true;
		}

	}//end doc.LoadFile()
	THROW_EXCEPTION(302, "Failed to load XML for Scene Manager");
	return false;
} //end loadFromXMLFile

//////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SceneManager::saveToXMLFile(std::string Filename){
	tinyxml2::XMLDocument saveFile;

	tinyxml2::XMLNode* sceneNode = saveFile.NewElement("scene");

	//iterate through layers and create xml elements for each
	int i = 1;
	for (auto layerIter = m_Layers.begin(); layerIter != m_Layers.end(); layerIter++){
		auto layerObjects = (*layerIter)->m_SceneObjects;
		string layerName = "layer" + std::to_string(i);
		tinyxml2::XMLElement* currLayer = saveFile.NewElement("layer");
		currLayer->SetAttribute("name", layerName.c_str());
		currLayer->SetAttribute("posx", (*layerIter)->m_PosX);
		currLayer->SetAttribute("posy", (*layerIter)->m_PosY);
		currLayer->SetAttribute("visible", (*layerIter)->m_Visible ? "true" : "false");
		saveFile.InsertFirstChild(sceneNode);

		//build xml element for each of the objects
		tinyxml2::XMLNode* currObjects = saveFile.NewElement("objects");
		for (auto objectIter = layerObjects.begin(); objectIter != layerObjects.end(); objectIter++){
			SDLRenderObject* currObject = (*objectIter);

			tinyxml2::XMLElement* pElement = saveFile.NewElement("object");
			pElement->SetText("");
			pElement->SetAttribute("resourceID", currObject->renderResource->m_ResourceID);
			pElement->SetAttribute("posx", currObject->posX);
			pElement->SetAttribute("posy", currObject->posY);
			pElement->SetAttribute("visible", currObject->visible ? "true" : "false");
			pElement->SetAttribute("rotation", currObject->rotation);
			pElement->SetAttribute("colorkey", currObject->colorKeyEnabled ? "true" : "false");
			if (currObject->colorKeyEnabled){
				pElement->SetAttribute("r", currObject->colorKey.r);
				pElement->SetAttribute("g", currObject->colorKey.g);
				pElement->SetAttribute("b", currObject->colorKey.b);
			}
			currObjects->InsertFirstChild(pElement);

		}
		currLayer->InsertFirstChild(currObjects);
		sceneNode->InsertEndChild(currLayer);
		i++;
	}

	std::string path = "resources/" + Filename;
	saveFile.SaveFile(path.c_str(), false);
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::checkTimerExpired() {
	std::list<Timer*>::iterator list_it;

	//render all associated render objects
	for (list_it = m_Timers.begin(); list_it != m_Timers.end(); list_it++){
		(*list_it)->update();

		if ((*list_it)->m_Expired) {
			std::list<SceneListener*>::iterator listener_it;

			for (listener_it = m_Listeners.begin(); listener_it != m_Listeners.end(); listener_it++){
				if ((*listener_it)->m_ListenFor == SE_TIMER_EXPIRED) {
					(*listener_it)->Event(this, NULL);
					(*list_it)->start();
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::update() {
	checkTimerExpired();

	//iterate through all the scene items and perform physics updates on them.
	for (auto layerIter = m_Layers.begin(); layerIter != m_Layers.end(); layerIter++){
		auto layerObjects = (*layerIter)->m_SceneObjects;
		for (auto objectIter = layerObjects.begin(); objectIter != layerObjects.end(); objectIter++){
			//perform the physics updates here

			//if ((*objectIter)->bodyType == b2_dynamicBody){
				//do something
			//}else if((*objectIter)->bodyType == b2_staticBody){
				//could be an immovable platform? maybe a switch?
			//}
			//other physics stuff
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::addTimer(unsigned int id, DWORD interval){
	Timer* timer = new Timer();
	timer->m_ID = id;
	timer->m_Interval = interval;
	m_Timers.push_back(timer);
	timer->start();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::addListener(SceneListener* object) {
	m_Listeners.push_back(object);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::sortLayers() {
	m_Layers.sort(compareLayerOrder);
}

void SceneManager::AssembleScene(){
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	//get reference to network manager
	renderMan->renderObjects.clear();
	for (std::list<Layer*>::iterator lay_it = m_Layers.begin(); lay_it != m_Layers.end(); lay_it++) {
		for (std::list<SDLRenderObject*>::iterator obj_it = (*lay_it)->m_SceneObjects.begin(); obj_it != (*lay_it)->m_SceneObjects.end(); obj_it++) {
			//cout << "item:" << &(*obj_it) << "x=" << (*obj_it)->posX << endl;
			/*
			if ((*obj_it)->getPlayerID() == GamerServices::sInstance->myID()) {
			//if this object is a locally owned object => update using input manager
			(*obj_it)->update(input);
			} else {
			//if this object is not locally owned => update object using information from packets
			//loop through all packets looking for a specific packet with this Unique Object Reference
			//if you find the specific packet with said UOR set this objects values to packet's values
			(*obj_it)->update(network);

			}
			*/
			renderMan->renderObjects.push_back((*obj_it));
		}
	}

	renderMan->update();
}

void SceneManager::InstantiateObject(Layer* layer, int resourceID, float x, float y){
	SDLRenderObject* object = new SDLRenderObject();
	if (!object)
		return;
	
	ResourceManager* ResMan = ResourceManager::GetResourceManager();
	object->setResourceObject((RenderResource*)ResMan->findResourcebyID(resourceID));

	object->posX = x;
	object->posY = y;
	layer->m_SceneObjects.push_back(object);
}

void SceneManager::RemoveObject(SDLRenderObject* object, Layer* layer) {
	if (!layer || !object)
		return;
	for (std::list<SDLRenderObject*>::iterator obj_it = layer->m_SceneObjects.begin(); obj_it != layer->m_SceneObjects.end(); obj_it++) {
		if (&(*obj_it) == &object) {
			layer->m_SceneObjects.erase(obj_it);//probably causes memleak, need to kill all the scene object values first?
			break;
		}
	}
	
}
