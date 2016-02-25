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


	SDLRenderObject* player1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2, 100, 100);
	SDLRenderObject* player2 =  sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, 200, 200);
	SDLRenderObject* base = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 0, 0, 0);
	base->anchor = { 0.5, 0.5 };
	//base->setVisible(false);
	SDLRenderObject* leg = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 103, -5, 30);
	leg->anchor = { 42 / float(leg->renderRect.w), 2 / float(leg->renderRect.h) };
	leg->setParent(base);
	SDLRenderObject* armor = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 101, 0, 0);
	armor->anchor = {0.5,0.5};
	armor->setParent(base);
	SDLRenderObject* arm = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 102, 31, 43);
	arm->anchor = { 14 / float(arm->renderRect.w), 3 / float(arm->renderRect.h) };
	arm->setParent(armor);
	//armor->setParent(a);
	/////////////////////////////////////////////////////
	/*              * * * GAME LOOP * * *              */
	/////////////////////////////////////////////////////
	bool gameloop = true;

	int var = 0;

	auto up = rotateTransform(arm, 0, 180);
	auto down = rotateTransform(arm, 180, 0);

	auto arcarm = moveEllipseArc(arm, 12, 14, 0, 4, -180, 360);
	auto arcbody = moveEllipseArc(armor, 0, 0, 5, 2, 0, -360);
	renderMan->zoom = 0.5;
	float size = 6;
	float ratio = 0.7;
	int armswing = size;
	int moveSpd = 1;
	while (gameloop) {
		var += 1;
		//if (var % 10 == 0)
		//NetworkManager::sInstance->ProcessIncomingPackets();
		//listen->getInput();

		//arm->rotation = var * 2;
		//base->posX += listen->input_x;
		//base->posY += listen->input_y;
		
		if (input->isKeyDown(KEY_DOWN)){
			base->posY += moveSpd;
		}
		if (input->isKeyDown(KEY_UP)){
			base->posY -= moveSpd;
		}
		if (input->isKeyDown(KEY_LEFT)){
			base->posX -= moveSpd;
		}
		if (input->isKeyDown(KEY_RIGHT)){
			base->posX += moveSpd;
		}
		if(input->isKeyDown(KEY_A)){
			renderMan->flippedScreen = !renderMan->flippedScreen;
		}
		if (input->isKeyDown(KEY_Q)){
			//base->setVisible(!base->isVisible());
			base->setFlippedH(!base->isFlippedH());
		}
		if (input->isKeyDown(KEY_W)){
			//base->setVisible(!base->isVisible());
			base->setFlippedV(!base->isFlippedV());
		}
		if (armswing > size && input->isKeyDown(KEY_Z)){
			armswing = 0;
		}
		if (armswing <= size){
			if (armswing < size*ratio)up(ease_QuadIn(float(armswing) / (size*ratio)));
			else down(ease_QuadOut(float(armswing - (size*ratio)) / (size*(1-ratio))));
			cout << float(armswing) << endl;
			armswing += 1;
		}
		else{
			arcarm(float(var % 12) / 12);
		}
		arcbody(float(var % 12) / 12);
		
		//arm->posX = 31 + armor->posX;
		//arm->posY = 43 + armor->posY;
		
		int length = 20;
		float loop = (var % length);
		/*if (loop < length/2){
			up(ease_QuadOut(loop/(length/2)));
		}
		else{
			down(ease_QuadIn((loop - length / 2) / (length / 2)));
		}*/
		
		//cout << player1->posX << "," << player2->posX<< endl;

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