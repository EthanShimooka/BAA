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
	obj2->anchor = { 1.0 , 1.0 };
	//renderMan->zoom = 4;
	for (float i = 0;; i++){
		float sini = 100 * (sin(i / 16) + 1);
		//renderMan->zoom = (sin(i / 600) + 1);
		//renderMan->cameraPoint = { obj->posX, obj->posY };
		//renderMan->cameraPoint = { (obj->posX + obj2->posX) / 2, (obj->posY + obj2->posY) / 2 };
		float focus = 0.54; // 0.5 = midpoint, 1.0 = obj focus, 0.0 = obj2 focus
		renderMan->cameraPoint = { (obj->posX*focus + obj2->posX*(1-focus)), (obj->posY*focus + obj2->posY*(1-focus)) };
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
		obj2->posX = 150 * (sin(i / 32)) + obj->posX;
		obj2->posY = 150 * -(cos(i / 40)) + obj->posY;
		//obj->renderRect.h = height * (int(i) % 100);
		obj2->rotation = i;
		if (obj2->posY < 0) {
			obj2->flipV = true;
			obj2->flipH = true;
		}
		else {
			obj2->flipV = false;
			obj2->flipH = false;
		}
		//if (int(i/10) % 4 == 1) obj->flipV = false;
		//if (int(i/10) % 4 == 2) obj->flipH = true;
		//if (int(i/10) % 4 == 3) obj->flipV = true;
		renderMan->update();
		//if (renderMan->isReadyToQuit())break;
	}
	std::cout << renderMan << endl;

	log->close();
	return 0;
}



