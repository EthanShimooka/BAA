#include "test.h"
//#include "include\network\NetIncludes.h"

using namespace std;

/*RenderResource* gameToRend(gameResource* game){
RenderResource* newSrc = new RenderResource();
newSrc->m_ResourceID = game->m_ResourceID;
newSrc->m_Scope = game->m_Scope;
newSrc->m_Filename = game->m_Filename;
newSrc->m_Type = game->m_Type;
return newSrc;
}*/


int main() {
	/*LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");
	try {
	THROW_EXCEPTION(1, "dude error");

	}
	catch (cException& e)
	{
	log->logBuffer << "***WHOOPS***\n";
	log->flush();
	log->logException(e);
	log->flush();
	cout << e.what() << endl;

	}
	log->close();
	/*double a = 7.4;
	int b = 98;
	cout << SquadIO::SquadIO::Add(a, b) << endl;
	*/
	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(400, 256, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml"); //load resources
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");



	for (float i = 0;; i++){
		renderMan->renderObjects.clear(); //empty renderables list before building up a new one each frame. NEEDS A LOOP TO CULL NON VISIBLE OBJECTS

		for (std::list<Layer*>::iterator lay_it = sceneMan->m_Layers.begin(); lay_it != sceneMan->m_Layers.end(); lay_it++) {
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

	log->close();


	return 0;
}