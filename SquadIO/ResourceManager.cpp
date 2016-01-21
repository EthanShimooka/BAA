
#include "ResourceManager.h"



ResourceManager::~ResourceManager()
{
}

void ResourceManager:: clear()
{
	return;
}

bool ResourceManager::loadFromXMLFile(std::string Filename)
{
	std::string path = "resources/" + Filename;
	//FILE *

	tinyxml2::XMLDocument doc;
	doc.LoadFile(path.c_str());
	if (doc.ErrorID() == 0){
		try{
			tinyxml2::XMLNode* ResourceTree = doc.FirstChildElement("resources");
			//if (doc.LoadFile("resources.xml") == tinyxml2::XML_NO_ERROR)
			//{
			if (ResourceTree){


				for (tinyxml2::XMLNode* child = ResourceTree->FirstChild(); 
					child;
					child = child->NextSiblingElement())
				{
					
				    tinyxml2::XMLElement* Element = child->ToElement();
					if (Element){
						gameResource *Resource = NULL;
						for (const tinyxml2::XMLAttribute* ElementAttrib = Element->FirstAttribute(); ElementAttrib; ElementAttrib = ElementAttrib->Next()){ //should this be const?
	
							std::string AttribName = ElementAttrib->Name();

							std::string AttribValue = ElementAttrib->Value();

							//Detect Resource Type
							if (AttribName == "type")
							{
								if (AttribValue == "graphic"){

									//Resource = RenderManager->loadResourceFromXML (Element);
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


		return true;
		}
		catch (cException& e){
			//report error

			return false;
		}
	}
	else return false;
}

void ResourceManager::setCurrentScope(unsigned int Scope)
{
	return;
}

