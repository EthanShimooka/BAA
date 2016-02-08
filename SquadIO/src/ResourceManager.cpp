/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ResourceManager.cpp
* External Libraies: TinyXML 2.0
* Copyright Team Squabble Squad
*
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "include\ResourceManager.h"
#include "include\RenderManager.h"

ResourceManager ResourceManager::resourceManager;

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::GetResourceManager()
{
	return &resourceManager;
}

// ResourceManager::findResourcebyID() - - 
// Accepts a resource-specific unique unsigned int and
// cycles through to find specified resource and returns
// said resource

gameResource* ResourceManager::findResourcebyID(unsigned int RID)
{
	std::map < unsigned int, std::list < gameResource*>>::iterator it;
	//search through scopes
	for (it = m_Resources.begin(); it != m_Resources.end(); it++) {
		if (!(*it).second.empty()) {
			std::list<gameResource*>::iterator list_it;
			for (list_it = (*it).second.begin(); list_it != (*it).second.end();
				list_it++){
				//if matching ID
				int thisID = (*list_it)->m_ResourceID;
				if ( thisID== RID)
					return (*list_it);
			}
		}
	}
	return NULL;
}
gameResource* ResourceManager::findResourcebyFilename(std::string RFN)
{
	std::map < unsigned int, std::list < gameResource*>>::iterator it;
	//search through scopes
	for (it = m_Resources.begin(); it != m_Resources.end(); it++) {
		if (!(*it).second.empty()) {
			std::list<gameResource*>::iterator list_it;
			for (list_it = (*it).second.begin(); list_it != (*it).second.end();
<<<<<<< HEAD
				*list_it){
=======
				*list_it++){

>>>>>>> refs/heads/new-master
				//if matching ID
				if ((*list_it)->m_Filename == RFN)
					return (*list_it);
			}
		}
	}
	return NULL;
}

<<<<<<< HEAD
=======
gameResource* ResourceManager::findResourcebyFilename(std::string RFN)
{
	std::map < unsigned int, std::list < gameResource*>>::iterator it;
	//search through scopes
	for (it = m_Resources.begin(); it != m_Resources.end(); it++) {
		if (!(*it).second.empty()) {
			std::list<gameResource*>::iterator list_it;
			for (list_it = (*it).second.begin(); list_it != (*it).second.end();
				*list_it){
				//if matching ID
				if ((*list_it)->m_Filename == RFN)
					return (*list_it);
			}
		}
	}
	return NULL;
}
>>>>>>> refs/heads/new-master

// ResourceManager::clear() - - 
//Clears Resource manager of elements

void ResourceManager::clear()
{
	std::map < unsigned int, std::list < gameResource*>>::iterator it;

	for (it = m_Resources.begin(); it != m_Resources.end(); it++){

		if (!(*it).second.empty())
		{
			std::list<gameResource*>::iterator list_it;

			//examine all resources under scope
			for (list_it = (*it).second.begin(); list_it != (*it).second.end();
				list_it++){

				//resource deletaion
				(*list_it)->unload();
				delete(*list_it);
				*list_it = NULL;
			}
			(*it).second.clear();
		}
	}
	m_Resources.clear();
}


//ResourceManager::loadFromXMLFile()  -- 
//
//Takes in a filename and loads resources from XML
//into memory

bool ResourceManager::loadFromXMLFile(std::string Filename)
{

	//LogManager* log = LogManager::GetLogManager();
	//log->create("log.txt");
	RenderManager* renderManager = RenderManager::getRenderManager();

	std::string path = "resources\\" + Filename;

	//FILE *

	tinyxml2::XMLDocument doc;
	doc.LoadFile(path.c_str());
	
		if (doc.ErrorID() == 0){

			tinyxml2::XMLNode* ResourceTree = doc.FirstChildElement("resources");
			if (ResourceTree){


				for (tinyxml2::XMLNode* child = ResourceTree->FirstChild();
					child;
					child = child->NextSiblingElement())
				{

					tinyxml2::XMLElement* Element = child->ToElement();
					if (Element){
						gameResource *Resource = NULL;
						for (const tinyxml2::XMLAttribute* ElementAttrib =
							Element->FirstAttribute(); ElementAttrib;
							ElementAttrib = ElementAttrib->Next()){ //should this be const?

							std::string AttribName = ElementAttrib->Name();

							std::string AttribValue = ElementAttrib->Value();

							//Detect Resource Type
							if (AttribName == "type")
							{
								if (AttribValue == "graphic"){

									Resource = renderManager->loadResourceFromXML(Element);
									std::cout << "Graphic Resource Loaded \n";

								}

								if (AttribValue == "audio"){

									//Resource = AudioManager->loadResourceFromXML (Element);
									std::cout << "Sound Resource Loaded \n";

								}

								if (AttribValue == "text"){

									//Resource = PlatformManager->loadResourceFromXML (Element);
									std::cout << "Text Resource Loaded \n";

								}
								//maybe change the values

							}

							if (Resource) {

								if (AttribName == "UID") {
									Resource->m_ResourceID = atoi(AttribValue.c_str());
									std::cout << "Resource unique Identifier Loaded \n";
								}
								if (AttribName == "filename") {
									Resource->m_Filename = AttribValue;
									std::cout << "Filename assigned \n";
								}
								if (AttribName == "scenescope") {
									Resource->m_Scope = atoi(AttribValue.c_str());
									std::cout << "Scope Loaded \n";
								}

							}
						}

						if (Resource){
							m_Resources[Resource->m_Scope].push_back(Resource);
							m_ResourceCount++;
						}
					}
				}
				return true;
			}
		}
		else{
			THROW_EXCEPTION(100, "Opening/Parsing XML Failure");
		}
	
	//log->close();


	return false;
}


// ResourceManager:: setCurrentScope :
//  flush current Scene and load specified
//  scene (Scope)

void ResourceManager::setCurrentScope(unsigned int Scope)
{
	if (m_CurrentScope != 0)
	{
		std::list<gameResource*>::iterator list_it;

		for (list_it = m_Resources[m_CurrentScope].begin(); list_it !=
			m_Resources[m_CurrentScope].end(); list_it++) {
			(*list_it)->unload(); //?
		}

		m_CurrentScope = Scope;
	}

	//new scope load
	std::list<gameResource*>::iterator list_it;

	for (list_it = m_Resources[m_CurrentScope].begin();
		list_it != m_Resources[m_CurrentScope].end(); list_it++){
		(*list_it)->load();
	}
	return;
}
