#include "test.h"
#include <iostream>

using namespace std;

int main() {
	LogManager* log = LogManager::GetLogManager();
	log->create("C:\\Users\\Brandon Jarvinen\\Desktop");
	try {
		THROW_EXCEPTION(1, "dude error");

	}
	catch (cException& e) {
		cout << e.what() << endl;

	}
	/*double a = 7.4;
	int b = 98;
	cout << SquadIO::SquadIO::Add(a, b) << endl;
	return 0;*/
}