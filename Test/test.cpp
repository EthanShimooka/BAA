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

	//RandGen::StaticInit();
	// need to initialize Steam before SDL so the overlay works*/
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
			 << "Press 3 for text test" << endl
			 << "Press 4 for all players in lobby" << endl;
		cin >> x;
		uint32_t hello = 2;
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
			while (hello < 10001){
				NetworkManager::sInstance->SendHelloWorld(hello);
				NetworkManager::sInstance->ProcessIncomingPackets();
				hello++;
			}
			break;
		case 4:
			NetworkManager::sInstance->GetAllPlayersInLobby();
			break;
		
		case 5:
			uint32_t h = 1;
			NetworkManager::sInstance->SendHelloWorld(h);
		}
	}
	/*
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	renderMan->init(400, 256, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");
	renderMan->setBackground("sky.jpg"); //TODO: change so it does not reference the direct filename
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";
	//fetches resource count

	SDLRenderObject* obj = new SDLRenderObject();
	RenderResource* rend = static_cast<RenderResource*>(resourceMan->findResourcebyID(1));


			obj->renderResource = rend;
			obj->setResourceObject(rend);
			obj->renderRect.w = 50;
			obj->renderRect.h = 50;

		

	SDLRenderObject* obj = new SDLRenderObject();
	//////////////////////////////////////////////////////////
	//TODO: Gets stuck on an infinite loop trying to find ID number 2
	RenderResource* rend = static_cast<RenderResource*>(resourceMan->findResourcebyID(1));
	obj->renderResource = rend;
	obj->setResourceObject(rend);

	renderMan->renderObjects.push_back(obj); //list
	std::cout <<"size of array :" << renderMan->renderObjects.size() << std::endl;

	renderMan->update();
	std::cout << renderMan << endl;*/
	/*
	float width = obj->renderRect.w;
	float height = obj->renderRect.h;
	obj->anchor = { 0.5, 0.5 };
	for (float i = 0;; i++){
		float sini = 100 * (sin(i / 16) + 1);
		obj->posX = sini;
		//obj->renderRect.h = height * (int(i) % 100);
		obj->rotation = i;
		if (int(i / 10) % 4 == 0) obj->flipH = false;
		if (int(i / 10) % 4 == 1) obj->flipV = false;
		if (int(i / 10) % 4 == 2) obj->flipH = true;
		if (int(i / 10) % 4 == 3) obj->flipV = true;
		renderMan->update();
		//if (renderMan->isReadyToQuit())break;
	}
	std::cout << renderMan << endl;*/

	log->close();
	return 0;
}