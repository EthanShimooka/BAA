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
	THROW_EXCEPTION(301, "Failed to find layer in SceneManager");
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
	SceneObject* object = new SceneObject();
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
			object->posX = (float)atof(AttribValue.c_str());
		}
		if (AttribName == "posy") {
			object->posY = (float)atof(AttribValue.c_str());
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
	
	if (object->colorKeyEnabled)
		object->setColorKey(r, g, b);

	layer->m_SceneObjects.push_back(object);

}

////////////////////////////////////////////////////////////////////////////////////////////////

bool SceneManager::loadFromXMLFile(std::string Filename) {
	tinyxml2::XMLDocument doc;
	std::list<Layer*> list;

	std::string path = "resources\\" + Filename;
	//std::string path = Filename;

	if (doc.LoadFile(path.c_str())){
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