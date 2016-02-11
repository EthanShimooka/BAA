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

void numbersDropped(const vector<uint32_t>& v){
	size_t size = v.size();
	//bool flag = false;
	for (size_t i = 0, j = 0; i < size; ++i, ++j){
		while (j != v[i]){
			cout << j << " ";
			++j;
		}
	}
}

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
<<<<<<< HEAD

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
			break;
		case 5:
			NetworkManager::sInstance->ProcessIncomingPackets();
			size_t size = NetworkManager::sInstance->test.size();
			cout << "size: " << size << endl;
			if (size > 0){
				cout << "Packets Dropped: ";
				numbersDropped(NetworkManager::sInstance->test);
				cout << "Percentage: " << static_cast<double>(size) / static_cast<double>(NetworkManager::sInstance->test[size - 1]) << endl;
			}
			break;
		}
		NetworkManager::sInstance->ProcessIncomingPackets();
	}*/
	/*
=======
	InputManager* input = InputManager::getInstance();
>>>>>>> origin/master
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