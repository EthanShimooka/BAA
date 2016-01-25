#include "test.h"


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
	return 0;*/
	RenderManager* rend = RenderManager::getRenderManager();
	cout << "this is main()" << endl;
	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	renderMan->init(400, 256, false, "WindowTitle");
	resourceMan->loadFromXMLFile("source.xml");


	//This block is supposted to load a sprite and draw it on screen. Thre are errors
	/*gameResource* tempSrc = resourceMan->findResourcebyID(1);
	tempSrc->load();

	RenderResource* sprite = resourceMan->findResourcebyID(1);
	SDLRenderObject* obj = new SDLRenderObject();
	obj->setResourceObject(sprite);
	renderMan->renderObjects.assign(1,obj);*/



	renderMan->update();
	//cout << renderMan << endl;
	cout << "this is _tmain()" << endl;
	return 0;
}



