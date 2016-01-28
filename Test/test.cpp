#include "test.h"
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
	//main() is the entry point for standard C++ standard, but _tmain is a Microsoft extension.
	//TODO: Since the Microsoft specific_tmain is the main entry point for our project, try and call main() from it and put all code in main()
	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");
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


	renderMan->renderObjects.push_back(obj); //list
	std::cout <<"size of array :" << renderMan->renderObjects.size() << std::endl;
	float width = obj->renderRect.w;
	float height = obj->renderRect.h;
	for (float i = 0;; i++){
		//obj->posX = (1 - sin(i/8))*100;
		//obj->renderRect.w = width *(1 - sin(i)) * 2;
		//obj->renderRect.h = height *(1 - sin(i/8))* 2;
		//std::cout << obj->renderRect.w *(2 - sin(i)) * 2 << endl;

		obj->rotation = 45;
		//NOTE: update returns a bool saying whether or not it updated.
		//currently the only case it doesn't is if ESC is press or SDL_QUIT is signaled
		//as detailed in the book
		bool stat = renderMan->update();
		if (!stat)break;
	}
	//renderMan->update();
	std::cout << renderMan << endl;

	log->close();
	return 0;
}



