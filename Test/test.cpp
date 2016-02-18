#include "test.h"
#include <functional>


//#include "include\network\NetIncludes.h"

using namespace std;

void update();
void render(RenderManager*);
long double getCurrentTime();

typedef float(*ease_function)(float);

float ease_linear(float i){
	return i;
}
float ease_QuadOut(float i){
	return pow(i,2);
}
float ease_QuadIn(float i){
	return -i*(i-2);
}
std::function<float(float)> getBezier(float x0, float x1, float x2, float x3){
	return [=](float i) {
		return x0 + i*(3 * x1 - 3 * x0) + i*i*(3 * x2 - 6 * x1 + 3 * x0) + i*i*i*(x3 - 3 * x2 + 3 * x1 - x0);
	};
}
std::function<void(float)> rotateTransform(SDLRenderObject* obj, double start, double end){
	return [=](float i) {obj->rotation = (end-start)*i+start; };
}

std::function<void(float)> moveCircArc(SDLRenderObject* obj, int centerx, int centery, double rad, double start_angle, double end_angle){
	return [=](float i) {
		obj->posX = centerx + rad * cos(M_PI*(end_angle*i + start_angle)/180);
		obj->posY = centery + rad * sin(M_PI*(end_angle*i + start_angle)/180);
	};
}
std::function<void(float)> moveEllipseArc(SDLRenderObject* obj, int centerx, int centery, double height, double width, double start_angle, double end_angle){
	return [=](float i) {
		obj->posX = centerx + width/2 * cos(M_PI*(end_angle*i + start_angle)/180);
		obj->posY = centery + height / 2 * sin(M_PI*(end_angle*i + start_angle)/180);
	};
}
//float bezier()
struct motion{
	std::function<void(float)> trans;
	std::function<float(float)> ease;
	int start; //a value from 0 to 1
	int duration; //a value from 1-start to 0
};
struct animation{
	list <motion> motions;
	bool animate(float i){
		for (auto mot =  motions.begin(); mot != motions.end();mot++){
			float place;
			if (i >= mot->start + mot->duration){place = 1.0;}//so durations of 0 are assumed to have finished
			else if (i < mot->start)			{place = 0.0;}
			else								{place = (i - mot->start) / mot->duration;}
			mot->trans(mot->ease(place));//apply transformation, place should be between 0 and 1
		}
	}
};

int main() {

	return 0;
}

int _tmain(int argc, _TCHAR* argv[]){
	LogManager* log = LogManager::GetLogManager();
	log->create("log.txt");

	/*if (!GamerServices::StaticInit())
		std::cout << "Failed to initialize Steam" << "\n";

	if (!NetworkManager::StaticInit())
		std::cout << "NetworkManager::StaticInit() failed!" << "\n";

	while (true){
		GamerServices::sInstance->Update();
		NetworkManager::sInstance->ProcessIncomingPackets();
		cout << "state: " << NetworkManager::sInstance->GetState() << endl;
		if (NetworkManager::sInstance->GetState() == 4)
			break;
		if (NetworkManager::sInstance->GetPlayerCount() == 2){
			NetworkManager::sInstance->GetAllPlayersInLobby();
			NetworkManager::sInstance->TryReadyGame();
		}
	}*/

	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	ResourceManager* resourceMan = ResourceManager::GetResourceManager();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderMan->init(700, 700, false, "Birds At Arms");
	resourceMan->loadFromXMLFile("source.xml");
	renderMan->zoom = 0.25;
	resourceMan->setCurrentScope(0);
	std::cout << "resource count : " << resourceMan->getResourceCount() << "\n";

	sceneMan->loadFromXMLFile("SceneTree.xml");

	InputListener* listen = new InputListener();


	Square* player1 = new Square(100, 100, 1);
	player1->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2, player1->x, player1->y);
	Square* player2 = new Square(200, 200, 2);
	player2->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, player2->x, player2->y);

	struct point{
		int x = 0;
		int y = 0;
	}center;
	//center = {};
	Square* leg = new Square(14+center.x, 60+center.y, 3);
	leg->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 103, leg->x, leg->y);
	leg->obj->anchor = { 42 / float(leg->obj->renderRect.w), 2 / float(leg->obj->renderRect.h) };
	Square* armor = new Square(0+center.x, 0+center.y, 4);
	armor->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 101, armor->x, armor->y);
	armor->obj->anchor = {0,0};
	Square* arm = new Square(31+center.x, 43+center.y, 5);
	arm->obj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 102, arm->x, arm->y);
	arm->obj->anchor = { 14 / float(arm->obj->renderRect.w), 3 / float(arm->obj->renderRect.h) };
	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;

	int var = 0;

	auto up = rotateTransform(arm->obj, 0, 180);
	auto down = rotateTransform(arm->obj, 180, 0);
	while (gameloop) {
		var += 1;
		//NetworkManager::sInstance->ProcessIncomingPackets();
		listen->getInput();

		//arm->obj->rotation = var * 2;
		center.x += listen->input_x;
		center.y += listen->input_y;
		auto arcbody = moveEllipseArc(armor->obj, center.x, center.y, 5, 2, 0, -360);
		arcbody(float(var % 12) / 12);
		auto arcarm = moveEllipseArc(arm->obj, 31 + armor->obj->posX, 43 + armor->obj->posY, 0, 4, -180, 360);
		arcarm(float(var % 12) / 12);

		leg->obj->posX = 14 + center.x;
		leg->obj->posY = 60 + center.y;
		//arm->obj->posX = 31 + armor->obj->posX;
		//arm->obj->posY = 43 + armor->obj->posY;
		
		int length = 20;
		float loop = (var % length);
		/*if (loop < length/2){
			up(ease_QuadOut(loop/(length/2)));
		}
		else{
			down(ease_QuadIn((loop - length / 2) / (length / 2)));
		}*/
		
		//cout << player1->obj->posX << "," << player2->obj->posX<< endl;

		player2->update();

		if (input->isKeyDown(KEY_ESCAPE))
			gameloop = false;

		input->update();
		

		sceneMan->AssembleScene();

		//render(renderMan);
	}
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	std::cout << renderMan << endl;

	log->close();
	return 0;
}


void init(){

}





void render(RenderManager* renderMan) {
	renderMan->update();
}

long double getCurrentTime(){
	long double sysTime = time(0);
	long double sysTimeMS = sysTime * 1000;

	return sysTimeMS;
}