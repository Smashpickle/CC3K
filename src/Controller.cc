#include "Controller.h"
#include <iostream>
#include <sstream>
// #include "CharacterFactory"
#include <fstream>

using namespace std;

Controller::~Controller() {
	if (playground)
		delete playground;
	if (player)
		delete player;
} // Controller::~Controller

vector<int> Controller::convert(string direction) {
	vector<int> retval;
	if (direction == "nw") {
		retval = {-1, -1};
	} else if (direction == "no") {
		retval = {-1, 0};
	} else if (direction == "ne") {
		retval = {-1, 1};
	} else if (direction == "we") {
		retval = {0, -1};
	} else if (direction == "ea") {
		retval = {0, 1};
	} else if (direction == "sw") {
		retval = {1, -1};
	} else if (direction == "so") {
		retval = {1, 0};
	} else if (direction == "se") {
		retval = {1, 1};
	} else
		retval.clear();
	return retval;
} // Controller::convert

Controller::Controller(string mn) : mapName{mn}, playground{new Floor} {}

void Controller::start() {
	playground->init(mapName);
	string race;
	int playerRoom = -1;
	while (true) {
		cout << "Choose a race: " << endl;
		getline(cin, race);
		if (race == "q") { // Quit
			cout << "Quitting" << endl;
			gameOver();
			return;
		} else {
			this->player = playground->spawnPlayer(race);
			if (!player) {
				cout << "Invalid Race" << endl;
			} else {
				break;
			}
		}
	}
	playerRace = race;
	if (mapName != "defaultMap.txt") {
		cerr << "No RNG Generation" << endl;
		playground->spawnManual(mapName, player, floorNumber);
	} else {
		cerr << "Placing Player" << endl;
		playerRoom = playground->placePlayer();
		cerr << "Creating Stairs" << endl;
		playground->spawnStairs(playerRoom);
		cerr << "Creating Potions" << endl;
		playground->spawnPotions();
		cerr << "Creating Gold" << endl;
		playground->spawnGold();
		cerr << "Creating Enemy" << endl;
		playground->spawnEnemies();
	}
	// playground->spawnManual("testMap.txt", player);
	loop();
} // Controller::start

void Controller::loop() {
	string commandLine;
	while (!gameIsOver) {
		playground->printMap();
		cout << "Floor " << floorNumber << endl;
		playground->getPlayerPtr()->displayStats();
		cout << "Enter command:" << endl;
		bool validAction = false;
		// Loop until a valid command is issued
		while (!validAction && !gameIsOver) {
			getline(cin, commandLine);
			cout << "**********************************************************"
			        "****"
			        "******************"
			     << endl;
			istringstream iss{commandLine};
			string command;
			string direction;
			iss >> command;

			if (command.size() == 2) { // Movement command
				vector<int> offset = convert(command);
				if (offset.size() != 2) {
					cout << "Invalid Direction" << endl;
					continue; // invalid action. Ask again
				}
				int status = playground->tryMove(offset);
				if (status == 0) {
					cout << "Blocked" << endl;
					continue; // invalid action. Ask again
				}
				// status == 1 (successful move) or 2 (stairs)
				validAction = true;
				if (status == 2) {
					goDown();
					// If going down, we may want to break out immediately
					break;
				}
			} else if (command == "u") { // Use command
				iss >> direction;
				vector<int> offset = convert(direction);
				if (offset.size() != 2) {
					cout << "Invalid Direction" << endl;
					continue;
				}
				bool status = playground->tryUse(offset);
				if (!status) {
					cout << "No Potion there" << endl;
					continue; // invalid action. Ask again
				}
				validAction = true;
			} else if (command == "a") { // Attack command
				iss >> direction;
				vector<int> offset = convert(direction);
				if (offset.size() != 2) {
					cout << "Invalid Direction" << endl;
					continue;
				}
				bool status = playground->tryAttack(offset);
				if (!status) {
					cout << "No Enemy there" << endl;
					continue; // invalid action. Ask again
				}
				validAction = true;
			} else if (command == "b") { // Buy command
				iss >> direction;
				vector<int> offset = convert(direction);
				if (offset.size() != 2) {
					cout << "Invalid Direction" << endl;
					continue;
				}
				int status = playground->tryBuy(offset);
				if (status == 0) {
					cout << "No Merchant there" << endl;
					continue; // invalid action. Ask again
				}
				if (status == 1) {
					cout << "Not enough gold to buy a potion!" << endl;
				} else if (status == 2) {
					cout << "Merchant is out of potions to sell!" << endl;
				} else if (status == 3) {
					cout << "Merchant: You are healthy! Do not waste gold!" << endl;
				} else if (status == 4) {
					cout << "Merchant: You have betrayed our trust... I will NOT sell to you!" << endl;
				} else {
					cout << "Healed to full amount!" << endl;
				}
				validAction = true;
			} else if (command == "r") { // Restart
				cout << "Restarting" << endl;
				validAction = true;
				restart();
				// After restart, break out of the inner loop
				break;
			} else if (command == "q") { // Quit
				cout << "Quitting" << endl;
				validAction = true;
				gameOver();
				break;
			} else { // Not valid
				cout << "Invalid Command" << endl;
				continue;
			}
		} // end inner loop
		if (gameIsOver) break;
		playground->enemyAction();
		// todo: implement Viewer refresh and NPC movement
		if (playground->getPlayerPtr()->getHP() <= 0) {
			gameOver();
		}
	}
} // Controller::loop

void Controller::restart() {
	delete playground;
	if (player) {
        delete player;
        player = nullptr;
    }
	floorNumber = 1;
	playground = new Floor;
	start();
} // Controller::reset

void Controller::goDown() {
	floorNumber++;
	score += playground->getScore();
	wasMerchantsAggro = playground->isAggro("Merchant");
	hasBarrierSuit = playground->hasBarrierSuitFloor("Barrier Suit");
	cerr << "Merchant Aggro: " << wasMerchantsAggro << endl;
	cerr << "Has Barrier Suit: " << hasBarrierSuit << endl;
	if (floorNumber > 5) {
		gameOver();
	} else {
		// Removes all temporary buff/debuff potions from the player.
		player->removePotionEffects();
		delete playground;
		playground = new Floor;
		cout << "generating new map" << endl;
		playground->init(mapName);
		if (mapName != "defaultMap.txt") {
			playground->spawnManual(mapName, player, floorNumber);
		} else {
			playground->setPlayer(player);
			// Place the player and record which chamber they are in.
			cerr << "Placing Player" << endl;
			int playerRoom = playground->placePlayer();
			// Spawn stairs in a chamber different from the player's.
			cerr << "Creating Stairs" << endl;
			playground->spawnStairs(playerRoom);
			cerr << "Creating Potions" << endl;
			playground->spawnPotions();
			cerr << "Creating Gold" << endl;
			playground->spawnGold();
			cerr << "Creating Enemy" << endl;
			playground->spawnEnemies();
		}

		if (wasMerchantsAggro) {
			cerr << "Calling turnOnAggro" << endl;
			playground->turnOnAggro("Merchant");
		}

		if (hasBarrierSuit) {
			cerr << "Calling turnOnBarrierSuit" << endl;
			playground->turnOnBarrierSuit();
		}
		loop();
	}
} // Controller::goDown

void Controller::gameOver() {
	cout << "**************************************************************"
	        "****"
	        "**************"
	     << endl;
	cout << "Game Over" << endl;
	if (floorNumber > 5) {
		cout << "Your final score is " << playground->getScore() << endl;
	}
	cout << "Play again? Y/else" << endl;
	string response;
	getline(cin, response);
	if (response == "y" || response == "Y") {
		restart();
	} else {
		gameIsOver = true;
	}
} // Controller::gameOver
