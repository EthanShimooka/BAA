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
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(400, 256, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");



	for (float i = 0;; i++){
		
		renderMan->update();
		//if (renderMan->isReadyToQuit())break;
	}
	std::cout << renderMan << endl;

	log->close();


	return 0;
}