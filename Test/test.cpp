#include "test.h"
#include "RenderManager.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>

using namespace std;

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
	cout << "this is _tmain()" << endl;
	return 0; 
}