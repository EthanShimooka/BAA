#include "test.h"
#include <iostream>

using namespace std;

int main() {
	LogManager* log = LogManager::GetLogManager();

	ResourceManager* rec;

	rec->loadFromXMLFile("test.xml");

	
	log->create("log.txt");
	try {
		
		THROW_EXCEPTION(1, "test error");

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
}