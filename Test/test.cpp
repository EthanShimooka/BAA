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
	return 0;*/
	RenderManager* rend = RenderManager::getRenderManager();
	cout << "this is main()" << endl;
	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	//RandGen::StaticInit();
	// need to initialize Steam before SDL so the overlay works
	if (!GamerServices::StaticInit())
	{
		std::cout << "Failed to initialize Steam" << "\n";
	}
	//NetworkManager::StaticInit();
	if (!NetworkManager::StaticInit())
	{
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";
	}
	while(true) {
		GamerServices::sInstance->Update();
		int x;
		cout << "Press 1 for player count" << endl
			 << "Press 2 for Player ID" << endl
			 << "Press 3 for text test" << endl;
		cin >> x;
		switch (x){
		case 1:
			cout << NetworkManager::sInstance->GetPlayerCount() << endl;
			if (NetworkManager::sInstance->IsMasterPeer()){
				cout << "You are master peer." << endl;
			}
			break;
		case 2:
			cout << GamerServices::sInstance->GetLocalPlayerName() << endl;
			break;
		case 3:
			NetworkManager::sInstance->SendHelloWorld();
			break;
		}
	}
	/*
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();




	renderMan->init(400, 256, false, "WindowTitle");
	resourceMan->loadFromXMLFile("source.xml");
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() <<"\n";
	//fetches resource count
	

	SDLRenderObject* obj = new SDLRenderObject();
	RenderResource* rend = static_cast<RenderResource*>(resourceMan->findResourcebyID(1));


			obj->renderResource = rend;
			obj->setResourceObject(rend);
			obj->renderRect.w = 50;
			obj->renderRect.h = 50;

		


	renderMan->renderObjects.push_back(obj); //list
	std::cout <<"size of array :" << renderMan->renderObjects.size() << std::endl;

	renderMan->update();
	std::cout << renderMan << endl;*/

	log->close();
	return 0;
}