#include "test.h"
#include <cmath>

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
	/*LogManager* log = LogManager::GetLogManager();
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
			 << "Press 3 for text test" << endl
			 << "Press 4 for all players in lobby" << endl;
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
		case 4:
			NetworkManager::sInstance->GetAllPlayersInLobby();

		}
		NetworkManager::sInstance->ProcessIncomingPackets();
	}*/
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(400, 256, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");
	renderMan->setBackground("tess1.gif"); //TODO: change so it does not reference the direct filename
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";
	//fetches resource count


	SDLRenderObject* obj = new SDLRenderObject();
	RenderResource* rend = static_cast<RenderResource*>(resourceMan->findResourcebyID(1));
	obj->renderResource = rend;
	obj->setResourceObject(rend);
	SDLRenderObject* obj2 = new SDLRenderObject();
	RenderResource* rend2 = static_cast<RenderResource*>(resourceMan->findResourcebyID(3));
	obj2->renderResource = rend2;
	obj2->setResourceObject(rend2);
	SDLRenderObject* obj3 = new SDLRenderObject();
	RenderResource* rend3 = static_cast<RenderResource*>(resourceMan->findResourcebyID(4));
	obj3->renderResource = rend3;
	obj3->setResourceObject(rend3);

	obj->layer = 1;
	obj2->layer = 3;
	obj3->layer = 4;
	//cout << (obj3 < obj2) << endl;
	renderMan->renderObjects.push_back(obj2);
	renderMan->renderObjects.push_back(obj);
	renderMan->renderObjects.push_back(obj3);
	renderMan->sortObjects();
	float width = obj->renderRect.w;
	float height = obj->renderRect.h;
	obj->anchor = { 0.5 , 0.5 };
	//renderMan->zoom = 4;
	
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");


	
	for (float i = 0;; i++){
		sceneMan->AssembleScene();
		//sceneMan->AssembleScene(
		//if (renderMan->isReadyToQuit())break;
		float sini = 100 * (sin(i / 16) + 1);
		//renderMan->zoom = (sin(i / 600) + 1);
		//renderMan->cameraPoint = { obj->posX, obj->posY };
		//renderMan->cameraPoint = { (obj->posX + obj2->posX) / 2, (obj->posY + obj2->posY) / 2 };
		float focus = 0.54; // 0.5 = midpoint, 1.0 = obj focus, 0.0 = obj2 focus
		renderMan->cameraPoint = { (obj->posX*focus + obj2->posX*(1 - focus)), (obj->posY*focus + obj2->posY*(1 - focus)) };
		float zoomRatio = renderMan->zoomRatio(obj2->posX - obj2->renderRect.w / 2, obj2->posY - obj2->renderRect.h / 2);
		float temp = zoomRatio = renderMan->zoomRatio(obj2->posX - obj2->renderRect.w / 2, obj2->posY + obj2->renderRect.h / 2);
		if (temp > zoomRatio) { zoomRatio = temp; }
		temp = renderMan->zoomRatio(obj2->posX + obj2->renderRect.w / 2, obj2->posY - obj2->renderRect.h / 2);
		if (temp > zoomRatio) { zoomRatio = temp; }
		temp = renderMan->zoomRatio(obj2->posX + obj2->renderRect.w / 2, obj2->posY + obj2->renderRect.h / 2);
		if (temp > zoomRatio) { zoomRatio = temp; }
		//cout << zoomRatio << endl;
		renderMan->zoom = zoomRatio;
		//obj->posX = 200 * (sin(i / 320));
		//obj->posY = 200 * -(cos(i / 320));
		obj2->posX = 500 * (sin(i / 32)) + obj->posX;
		obj2->posY = 500 * -(cos(i / 40)) + obj->posY;
		//obj->renderRect.h = height * (int(i) % 100);
		obj->rotation = i;
		//if (int(i/10) % 4 == 0) obj->flipH = false;
		//if (int(i/10) % 4 == 1) obj->flipV = false;
		//if (int(i/10) % 4 == 2) obj->flipH = true;
		//if (int(i/10) % 4 == 3) obj->flipV = true;

		renderMan->update();
	}
	std::cout << renderMan << endl;

	//log->close();
	return 0;
}