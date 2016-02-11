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

	///Initialize various managers
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(400, 256, false, "Birds At Arms");//create window
	resourceMan->loadFromXMLFile("source.xml");//load images for objects
	renderMan->setBackground("tess1.gif"); //TODO: change so it does not reference the direct filename
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";
	sceneMan->loadFromXMLFile("SceneTree.xml");//load objects onto scene
	
	//initializing objects not in XML
	SceneObject* obj = new SceneObject();//daffy duck that spins in the center of the window
	RenderResource* rend = static_cast<RenderResource*>(resourceMan->findResourcebyID(4));//daffy.jpg
	obj->renderResource = rend;
	obj->setResourceObject(rend);
	
	SceneObject* obj2 = new SceneObject();//yellow duck that circles around the center
	RenderResource* rend2 = static_cast<RenderResource*>(resourceMan->findResourcebyID(3));//duck.png
	obj2->renderResource = rend2;
	obj2->setResourceObject(rend2);

	//push the objects onto the scene manager's first layer
	sceneMan->m_Layers.front()->m_SceneObjects.push_back(obj);
	sceneMan->m_Layers.front()->m_SceneObjects.push_back(obj2);
	//obj->zdepth = 1;
	//obj2->zdepth = 3;
	//renderMan->sortObjects();

	//set the center of rotation/rendering for each object
	obj->anchor = { 0.5 , 0.5 };//{0,0} means top left corner of image
	obj2->anchor = { 0.5, 0.5 };//{1,1} means bottom right corner of image

	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	//core loop at moment
	for (float i = 0;; i++){
		//if (renderMan->isReadyToQuit())break;

		//cameraPoint is a point in the world that is made to be the window's center
		//Set the camera point to a point that allows two objects to be visible to the window
		float focus = 0.54; // 1.0 = obj focus; 0.0 = obj2 focus ; 0.5 = midpoint
		renderMan->cameraPoint = { (obj->posX*focus + obj2->posX*(1 - focus)), (obj->posY*focus + obj2->posY*(1 - focus)) };
		//cameraPoint is some point along a line that connects object 1 and object 2

		//zoom ratio returns a number that tells how much or little the window should be zoomed in or out
		//to make sure that a particular point is at the edge of the window

		//The following section tests the 4 corners of obj2's sprite, and makes sure all 4 corners are visible
		//alternate method: test distances, and only get the zoomRatio of the point with the largest distance from the cameraPoint
		float zoomRatio = renderMan->zoomRatio(obj2->posX - obj2->renderRect.w / 2, obj2->posY - obj2->renderRect.h / 2);
		float temp = zoomRatio = renderMan->zoomRatio(obj2->posX - obj2->renderRect.w / 2, obj2->posY + obj2->renderRect.h / 2);
		if (temp > zoomRatio) { zoomRatio = temp; }//if this corner requires a larger zoom, replace the older one
		temp = renderMan->zoomRatio(obj2->posX + obj2->renderRect.w / 2, obj2->posY - obj2->renderRect.h / 2);
		if (temp > zoomRatio) { zoomRatio = temp; }//if this corner requires a larger zoom, replace the older one
		temp = renderMan->zoomRatio(obj2->posX + obj2->renderRect.w / 2, obj2->posY + obj2->renderRect.h / 2);
		if (temp > zoomRatio) { zoomRatio = temp; }//if this corner requires a larger zoom, replace the older one
		renderMan->zoom = zoomRatio;//zoom is now the largest zoomRatio of the 4 corners

		//obj->posX = 200 * (sin(i / 320)); // change obj's x pos
		//obj->posY = 200 * -(cos(i / 320)); // change obj's y pos
		obj2->posX = 500 * (sin(i / 32)) + obj->posX; // change obj2's x pos in relation to obj
		obj2->posY = 500 * -(cos(i / 40)) + obj->posY; // change obj2's x pos in relation to obj 
		//obj->renderRect.h = height * (int(i) % 100); // stretch obj's sprite
		obj->rotation = i;// rotate obj

		//in a cycle, flip the orientation of obj's sprite
		//if (int(i/10) % 4 == 0) obj->flipH = false;
		//if (int(i/10) % 4 == 1) obj->flipV = false;
		//if (int(i/10) % 4 == 2) obj->flipH = true;
		//if (int(i/10) % 4 == 3) obj->flipV = true;

		sceneMan->AssembleScene();//render
		Sleep(30);//delay before the next update
	}
	std::cout << renderMan << endl;

	//log->close();
	return 0;
}