#include "Controller.h"
#include <string>

using namespace std;

const string defaultMapName = "defaultMap.txt";

int main(int argc, char *argv[]) {
	if (argc == 2) {
		Controller game{argv[1]};
		game.start();
	} else {
		Controller game{defaultMapName};
		game.start();
	}
	return 0;
}
