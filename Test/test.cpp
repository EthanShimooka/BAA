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

	obj->renderRect.w = width * 3;
	obj->renderRect.h = height * 3;
	obj->anchor = { 1.2, 1.2 };
	for (float i = 0;; i++){
		//obj->posX = (1 - sin(i/160))*50;
		//obj->posY = (1 - sin(i / 160)) * 50;
		//obj->renderRect.w = width *(2 - sin(i/16)) * 2;
		//obj->renderRect.h = height *(2 - sin(i/16))* 2;
		//std::cout << obj->renderRect.w *(2 - sin(i)) * 2 << endl;
		//std::cout << int(i / 10) % 4 <<":"<< obj->flipH << obj->flipV<<endl;
		/*if (int(i/10) % 4 == 0) { obj->flipH = false; }
		if (int(i/10) % 4 == 1) { obj->flipV = false; }
		if (int(i/10) % 4 == 2) { obj->flipH = true; }
		if (int(i/10) % 4 == 3) { obj->flipV = true; }*/
		//SDL_Point anchor = { obj->renderRect.w * obj->anchor.x, obj->renderRect.h * obj->anchor.y };
		//std::cout << "(" << anchor.x << "," << anchor.y << ")" << endl;
		obj->rotation = i*1.3;
		//obj->posX++;
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



