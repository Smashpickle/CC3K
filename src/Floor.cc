#include <iostream>
#include <sstream>

#include "Enemy.h"
#include "Factory.h"
#include "Floor.h"
#include "Info.h"
#include "Potion.h"
#include "Rng.h"
#include "Stairs.h"

using namespace std;

const int FIRSTROW = 0;
const int LASTROW = 25;
const int FIRSTCOLUMN = 0;
const int LASTCOLUMN = 79;
const int RANDOMDIRECTION = 2;
const int RANDOMCHAMBER = 5;
const int RANDOMENEMY = 18;
const int MAXENEMIES = 20;
const int RANDOMPOTION = 6;
const int MAXPOTIONS = 10;
const int RANDOMGOLD = 8;
const int MAXGOLDPILES = 10;
const int ENEMYGOLD = 1;
const int CANSPAWNDRAGON = 1;
const string STAIRS = "stairs";

#include <vector>

Floor::~Floor() {
	for (auto &row : floorMap) {
		for (auto &cell : row) {
			if (cell.getObject() &&
			    !(cell.getObject()->getCtgy() == Category::Player)) {
				delete cell.getObject();
			}
		}
	}
	delete td;
} // Floor::~Floor

void Floor::init(string mapName) {
	fstream mapin{mapName};
	td = new TextDisplay;
	floorMap.clear();
	vacantChamberCells.clear();
	floorMap.resize(LASTROW);
	cerr << "Vacant cell count at initialization is " << vacantChamberCells.size() << endl;
	// Reads from a file and import contents to the cellMap.
	for (int row = 0; row < LASTROW; row++) {
		string currLine;
		getline(mapin, currLine);
		// int col = 0;
		for (int col = 0; col < LASTCOLUMN; col++) {
			char currBlock = currLine[col];
			Type t;
			if (currBlock == '\n')
				continue;
			else if (currBlock == ' ')
				t = Type::Hole;
			else if (currBlock == '#')
				t = Type::Way;
			else if (currBlock == '-')
				t = Type::WallH;
			else if (currBlock == '|')
				t = Type::WallV;
			else if (currBlock == '+')
				t = Type::Door;
			else
				t = Type::Ground;
			floorMap[row].emplace_back(row, col, t);
			// cerr << "Cord R:" << row << " C:" << col << endl;
			td->notify(floorMap[row][col]);
			// cerr << *td;
		}
	}
	cerr << "Finished Cell Creation." << endl;
	// Attach cells to its neighbours.
	for (int r = 0; r < LASTROW; r++) {
		// cerr << "At row " << r << endl;
		for (int c = 0; c < LASTCOLUMN; c++) {
			for (int offsetr = -1; offsetr <= 1; offsetr++) {
				for (int offsetc = -1; offsetc <= 1; offsetc++) {
					if (offsetr == 0 && offsetc == 0)
						continue;
					int tempr = r + offsetr;
					int tempc = c + offsetc;
					if (tempr >= 0 && tempr < LASTROW && tempc >= 0 &&
					    tempc < LASTCOLUMN)
						floorMap[r][c].attach(&floorMap[tempr][tempc]);
				}
			}
		}
	}
	// Calculate chamber size and assign each Cell with offest/index.
	cerr << "Finished neighbour linking." << endl;
	counterArr.clear();
	counterArr.resize(5, 0);
	int chamberNumber = 0;
	for (int r = 0; r < LASTROW; r++) {
		// cerr << "At row " << r << endl;
		for (int c = 0; c < LASTCOLUMN; c++) {
			Info target = floorMap[r][c].getInfo();
			if (target.type == Type::Ground && target.chamberNumber == -1) {
				int chamberSize = 0;
				std::vector<Cell *> currChamberCells;
				vacantChamberCells.push_back(currChamberCells);
				floorMap[r][c].spreadChamberNumber(chamberNumber, &chamberSize,
				                                   vacantChamberCells);
				counterArr[chamberNumber] = chamberSize;
				chamberNumber++;
			}
		}
	}
	cerr << "Attaching TextDisplay as observer." << endl;
	for (auto &row : floorMap) {
		for (auto &cell : row) {
			// cell.clear();
			cell.attach(td);
		}
	}
} // Floor::init

vector<int> Floor::
generateDirection() {
	vector<int> newDirection = {0, 0};
	// Variable for generating a random direction for North and South.
	int randNS = 0;
	// Variable for generating a random direction for East and West.
	int randEW = 0;


	while (randNS == 0 && randEW == 0) {
		randNS = rng(-1, 1);
		randEW = rng(-1, 1);
		// cerr << "The random directions that were generated are NS = " <<
		// 	 randNS << " EW = " << randEW << endl;
	}
	newDirection[0] = randNS;
	newDirection[1] = randEW;
	return newDirection;
} // Floor::convert

void Floor::createRandomPlacement(int &randomChamber, int &randomCell,
                                  int playerRoom) {
	randomChamber = rng(0, RANDOMCHAMBER - 1);
	while (playerRoom == randomChamber) {
		randomChamber = rng(0, RANDOMCHAMBER - 1);
	}

	// Determine Cell count in chamber.
	int cellCount = vacantChamberCells[randomChamber].size();
	randomCell = rng(0, cellCount - 1);
	// cout << "randomChamber: " << randomChamber << " cellCount: " << cellCount
	// << endl;
} // Floor::createRandomPlacement

PlayerCharacter *Floor::spawnPlayer(string name) {
	PlayerCharacter *retval = createPlayerCharacter(name);
	if (retval) {
		player = retval;
	}
	return retval;
} // Floor::spawnPlayer

int Floor::placePlayer() {
	// Determine which chamber to spawn the Enemy in.
	// cerr << "in Placing Player function" << endl;
	int randomChamber = -1;
	int randomCell = -1;
	// Determines a random chamber and a random Cell in the chamber.
	createRandomPlacement(randomChamber, randomCell);
	occupyCell(randomChamber, randomCell, this->player);
	return randomChamber;
} // Floor::placePlayer

void Floor::setPlayer(PlayerCharacter *player) {
	this->player = player;
} // Floor::setPlayer

void Floor::occupyCell(int randomChamber, int randomCell, CellObject *co) {
	vacantChamberCells[randomChamber][randomCell]->setObject(co);
	vacantChamberCells[randomChamber].erase(
	    vacantChamberCells[randomChamber].begin() + randomCell);
} // Floor::occupyCell

void Floor::spawnStairs(int playerRoom) {
	// Determine which chamber to spawn the Stairs in.
	int randomChamber = -1;
	int randomCell = -1;
	// Determines a random chamber and a random Cell in the chamber.
	createRandomPlacement(randomChamber, randomCell, playerRoom);
	Item *stairs = createItem(STAIRS);
	Stairs *s = dynamic_cast<Stairs *>(stairs);
	if (s) {
		// Place stairs in the floor.
		this->stairs = s;
		// s->reveal();
	} else {
		cerr << "Error: Stairs creation failed!" << endl;
	}
	occupyCell(randomChamber, randomCell, s);
} // Floor::spawnStairs

void Floor::spawnPotions() {
	int potionCount = 0;
	while (potionCount < MAXPOTIONS) {
		// Determine which chamber to spawn the Potion in.
		int randomChamber = -1;
		int randomCell = -1;
		// Determines a random chamber and a random Cell in the chamber.
		createRandomPlacement(randomChamber, randomCell);
		// Determines which Enemy to spawn.
		int randomPotion = rng(1, RANDOMPOTION);
		Item *currPotion;
		if (randomPotion == 1) {
			currPotion = createItem("RHpotion");
		} else if (randomPotion == 2) {
			currPotion = createItem("BApotion");
		} else if (randomPotion == 3) {
			currPotion = createItem("BDpotion");
		} else if (randomPotion == 4) {
			currPotion = createItem("PHpotion");
		} else if (randomPotion == 5) {
			currPotion = createItem("WApotion");
		} else {
			currPotion = createItem("WDpotion");
		}
		// cerr << "Current Enemy address being placed: " << currPotion << endl;
		occupyCell(randomChamber, randomCell, currPotion);
		// cout << vacantChamberCells[randomChamber][randomCell] << endl;
		++potionCount;
	}
} // Floor::spawnPotions

vector<pair<int, int>> Floor::getCellNeighbours(Cell *cell) {
    vector<pair<int, int>> neighbours;
    vector<int> coordinates = cell->getCord();
    int r = coordinates[0];
    int c = coordinates[1];
	// cerr << "Cell in question getting its neighbours: " << endl;
	// cerr << "Row: " << r << " Col: " << c << endl;
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {
            if (rowOffset == 0 && colOffset == 0)
                continue;
            int nr = r + rowOffset;
            int nc = c + colOffset;
			
            if (nr >= 0 && nr < LASTROW && nc >= 0 && nc < LASTCOLUMN) {
                if (floorMap[nr][nc].getInfo().type == Type::Ground) {
					neighbours.push_back({nr, nc});
					// cerr << "(" << nr << ", ";
					// cerr << nc << ")" << endl;
				}
            }
        }
    }
    return neighbours;
} // Floor::getCellNeighbours

vector<pair<int, int>> Floor::getFreeNeighbours(vector<pair<int, int>> neigh) {
	vector<pair<int, int>> freeCells;
	int neighSize = neigh.size();
	for (int i = 0; i < neighSize; ++i) {
		int r = neigh[i].first;
		int c = neigh[i].second;
		// Since the vector of Cell neighbours are already all ground types,
		//   we only check if that cell contains an object.
		if (floorMap[r][c].getObject() == nullptr) {
			freeCells.push_back(neigh[i]);
		}
	}
	return freeCells;
} // Floor::getFreeNeighbours

void Floor::manualRemoveFreeCell(int chamberNumber, Cell* cellToRemove) {
	int indexToRemove = -1;
	vector<Cell *> chamberCells = vacantChamberCells[chamberNumber];
	int cellCount = chamberCells.size();
	for (int i = 0; i < cellCount; ++i) {
		if (chamberCells[i] == cellToRemove) {
			indexToRemove = i;
		}
	}
	if (indexToRemove != -1) {
		vacantChamberCells[chamberNumber].erase(
			vacantChamberCells[chamberNumber].begin() + indexToRemove);
		cerr << "Successfully erased occupied Cell" << endl;
	}
} // Floor::manualRemoveFreeCell

bool Floor::determineSpawnBS(vector<pair<int, int>> freeGoldNeighbours,
							 int goldNumFreeNeigh) {
	bool canSpawnBS = true;								
	for (int i = 0; i < goldNumFreeNeigh; ++i) {
		int row = freeGoldNeighbours[i].first;
		int col = freeGoldNeighbours[i].second;
		Cell *currNeighCell = &(floorMap[row][col]);

		// Obtain the free neighbours of the current gold neighbouring Cell.
		cerr << "These calls to get cell neighbours are from determinSpawnBS" << endl;
		vector<pair<int, int>> currNeighCellNeigh = getCellNeighbours(currNeighCell);
		vector<pair<int, int>> currNeighFreeNeigh = getFreeNeighbours(currNeighCellNeigh);
		if (currNeighFreeNeigh.size() < 1) {
			canSpawnBS = false;
		}
	}
	cerr << "determinSpawnBS finished" << endl;
	return canSpawnBS;
} // Floor::determineSpawnBS

void Floor::spawnGold() {
    int goldCount = 0;
	// Spawning only 10 piles of gold.
    while (goldCount < MAXGOLDPILES) {
        int randomChamber = -1, randomCell = -1;
		// Choosing a random chamber and a random Cell for the new Gold.
        createRandomPlacement(randomChamber, randomCell);
		
		// Choosing which gold hoard to create.
        int randomGold = rng(1, RANDOMGOLD);
        Item *currGold = nullptr;
        Enemy *dragon = nullptr;
        Item *bs = nullptr;

		// Initial setup for the Dragon Hoard (Gold only).
		Cell *potCell = nullptr;
        vector<pair<int, int>> goldCellNeighbours;
		vector<pair<int, int>> goldFreeNeighbours;
		vector<pair<int, int>> dragonFreeNeighbours;
        int goldNumFreeNeigh = 0;

        if (randomGold >= 1 && randomGold <= 5) {
            currGold = createItem("normalGold");
        } else if (randomGold == 6) {
            potCell = vacantChamberCells[randomChamber][randomCell];
			// Gets the cell's neighbours, then check whether or not they are occupied.
            goldCellNeighbours = getCellNeighbours(potCell);
			cerr << "number of neighbours: " << goldCellNeighbours.size() << endl;
			goldFreeNeighbours = getFreeNeighbours(goldCellNeighbours);
            goldNumFreeNeigh = goldFreeNeighbours.size();
			cerr << "number of free neighbours: " << goldNumFreeNeigh << endl;
            if (goldNumFreeNeigh >= CANSPAWNDRAGON) {
                currGold = createItem("dragonGold");
                dragon = createEnemy("D");

				// Determining whether to create a Barrier Suit or not.
                int createBS = rng(0, 1);
                if (!barrierSuit && createBS == 1 && 
					determineSpawnBS(goldFreeNeighbours, goldNumFreeNeigh)) {
                    barrierSuit = true;
                    bs = createItem("barrierSuit");
                }
            } else {
                currGold = createItem("normalGold");
            }
        } else {
            currGold = createItem("smallGold");
        }

        if (currGold) {
			// Places currGold in a random free cell in a random chamber, and then
			//   updates the vector of vacant Cells.
            occupyCell(randomChamber, randomCell, currGold);

			// Sets up a vector of Cells that will draw Dragon aggro, 
			//   if the Dragon spawns.
			vector<pair<int, int>> dragonAggroCells;
			Cell *goldCell = potCell;
			Cell *dragonCell = nullptr;
			Cell *bsCell = nullptr;
			vector<pair<int, int>> bsAggroCells;

			// Sets up a vector of Cells that determines the Dragon's guarded items.
			vector<pair<int, int>> guardedItemsLoca;

            // Place dragon if created and a valid neighbour exists.
            if (dragon && !goldFreeNeighbours.empty()) {
				// Chooses a random Cell neighbouring the currGold cell to 
				//   spawn the dragon. 
                int index = rng(0,  goldNumFreeNeigh - 1);
                pair<int, int> dragCoord = goldFreeNeighbours[index];
                dragonCell = &(floorMap[dragCoord.first][dragCoord.second]);

				// Spawns the Dragon.
                if (dragonCell->getInfo().type == Type::Ground &&
                    dragonCell->getObject() == nullptr) {
                    dragonCell->setObject(dragon);
					
					// Adds the Dragon gold hoard to the dragon's guarded items. 
					int goldCoordr = goldCell->getCord()[0];
					int goldCoordc = goldCell->getCord()[1];	
					guardedItemsLoca.push_back({goldCoordr, goldCoordc});

					// Sets a vector of Dragon aggro Cells through Dragon
					//   Hoard Cell neighbours.
					cerr << "(" << goldCell->getCord()[0] << ", " << goldCell->getCord()[1] << ")" << endl;
					dragonAggroCells = getCellNeighbours(goldCell);

                    // Remove this Cell from the vector of free Cells so 
					//   barrier suit uses a different cell.
                    goldFreeNeighbours.erase(goldFreeNeighbours.begin() + index);
					manualRemoveFreeCell(randomChamber, dragonCell);
					
					// Gets the free neighbours of the dragon Cell.
					cerr << "Free neighbours of the Dragon Cell to see" <<
					 		" if its possible to spawn the Barrier Suit." << endl;
					vector<pair<int, int>> dragonNeighbours = getCellNeighbours(dragonCell);
					dragonFreeNeighbours = getFreeNeighbours(dragonNeighbours);
                }
            }

            // Place barrier suit if created and a valid neighbour exists.
            if (bs && !dragonFreeNeighbours.empty()) {
				// Chooses a random Cell neighbouring the dragon cell to 
				//   spawn the Barrier Suit. 				
				int numFreeDragonNeighs = dragonFreeNeighbours.size();
                int index = rng(0, numFreeDragonNeighs - 1);
                pair<int, int> bsCoord = dragonFreeNeighbours[index];
                bsCell = &(floorMap[bsCoord.first][bsCoord.second]);

				cerr << "count of free cells before: " << vacantChamberCells[randomChamber].size() << endl;
                // Spawns the Barrier Suit.
				if (bsCell->getInfo().type == Type::Ground &&
                    bsCell->getObject() == nullptr) {
					bsCell->setObject(bs);
					
					// Adds the Barrier Suit to the Dragon's guarded items.
					guardedItemsLoca.push_back(bsCoord);

					// Sets a vector of Dragon aggro Cells through Barrier
					//   Suit Cell neighbours.
					bsAggroCells = getCellNeighbours(bsCell);

					// Remove this neighbour if barrier suit was created.
					dragonFreeNeighbours.erase(dragonFreeNeighbours.begin() + index);
					manualRemoveFreeCell(randomChamber, bsCell);
					cerr << "count of free cells after: " << vacantChamberCells[randomChamber].size() << endl;						
				}
            }
			int dragonAggroCount = dragonAggroCells.size();
			int bsAggroCount = bsAggroCells.size();

			vector<pair<int, int>> dragonActualAggro = dragonAggroCells;
			// If the Dragon and its hoard exists, sets up an aggro zone.
			if (dragonAggroCount != 0) {
				for (int bs = 0; bs < bsAggroCount; ++bs) {
					bool isDup = false; 
					for (int drag = 0; drag < dragonAggroCount; ++drag) {
						if (bsAggroCells[bs] == dragonAggroCells[drag]) {
							isDup = true;
							break;
						}
					}
					if (!isDup) {
						cerr << "adding berrier suit neighbours to dragon aggro zone" << endl;
						dragonActualAggro.push_back(bsAggroCells[bs]);
					}
				}
			}
			if (dragon) {
				cerr << "Printing Dragon aggro cells for the Dragon at: Row: " <<
						 dragon->getCord()[0] << " Col : " << dragon->getCord()[1] << endl; 
			}
			int sizeAggroZone = dragonActualAggro.size();
			for (int i = 0; i < sizeAggroZone; ++i) {
				cerr << "(" << dragonActualAggro[i].first << ", " <<
					 	dragonActualAggro[i].second << ")" << endl; 
			}
			Dragon *spawnedDragon = static_cast<Dragon *>(dragon);
			if (spawnedDragon) {
				cerr << "Aggro zone has been assigned" << endl;
				spawnedDragon->setAggroZone(dragonActualAggro);
				spawnedDragon->setGuarded(guardedItemsLoca);
			}
            ++goldCount;
        }
    }
} // Floor::spawnGold

void Floor::giveEnemyCompass(vector<Enemy *> enemies) {
	int enemiesCount = enemies.size();
	if (enemiesCount > 0) {
		int randomCompass = rng(0, enemiesCount - 1);
		Enemy *chosenEnemy = enemies[randomCompass];
		cout << chosenEnemy->getName() << endl;
		chosenEnemy->giveCompass();
	} else {
		return;
	}
} // Floor::giveEnemyCompass

void Floor::spawnEnemies() {
	int monsterCount = 0;
	vector<Enemy *> enemies;
	while (monsterCount < MAXENEMIES) {
		// Determine which chamber to spawn the Enemy in.
		int randomChamber = -1;
		int randomCell = -1;
		// Determines a random chamber and a random Cell in the chamber.
		createRandomPlacement(randomChamber, randomCell);
		// Determines which Enemy to spawn.
		int randomEnemy = rng(1, RANDOMENEMY);
		Enemy *currEnemy;
		if (randomEnemy >= 1 && randomEnemy <= 4) {
			currEnemy = createEnemy("W");
		} else if (randomEnemy >= 5 && randomEnemy <= 7) {
			currEnemy = createEnemy("V");
		} else if (randomEnemy >= 8 && randomEnemy <= 12) {
			currEnemy = createEnemy("G");
		} else if (randomEnemy >= 13 && randomEnemy <= 14) {
			currEnemy = createEnemy("T");
		} else if (randomEnemy >= 15 && randomEnemy <= 16) {
			currEnemy = createEnemy("X");
		} else {
			currEnemy = createEnemy("M");
		}
		if (currEnemy->getName() != "Merchant") {
			enemies.push_back(currEnemy);
		}
		// cerr << "Current Enemy address being placed: " << currEnemy << endl;
		occupyCell(randomChamber, randomCell, currEnemy);
		// cout << vacantChamberCells[randomChamber][randomCell] << endl;
		++monsterCount;
	}
	giveEnemyCompass(enemies);
} // Floor::spawnEnemies

void Floor::spawnManual(std::string mapName, PlayerCharacter *ptr,
                        int floorNum) {
	fstream mapin{mapName};
	int startRow = (floorNum - 1) * LASTROW;
	string dummy;
	for (int i = 0; i < startRow; i++) {
		getline(mapin, dummy);
	}
	vector<Enemy *> enemies;
	int row = 0;
	while (row < LASTROW) {
		string currLine;
		getline(mapin, currLine);

		for (int col = 0; col < LASTCOLUMN; col++) {
			char currBlock = currLine[col];
			string name = "";
			name.push_back(currBlock);
			if (name == "@") {
				floorMap[row][col].setObject(ptr);
				player = ptr;

			} else if (name == "\\") {

				Item *obj = createItem(STAIRS);
				cout << "creating stairs" << endl;
				floorMap[row][col].setObject(obj);
				Stairs *s = static_cast<Stairs *>(obj);
				stairs = s;

			} else if (name == "C") {

				Item *obj = createItem("compass");
				floorMap[row][col].setObject(obj);

			} else {
				// cerr << name << endl;
				CellObject *obj = createItem(name);
				if (!obj)
					obj = createEnemy(name);
				if (obj) {
					if (obj->getCtgy() == Category::Enemy) {
						Enemy *currEnemy = static_cast<Enemy *>(obj);
						if (currEnemy->getName() != "Merchant") {
							cout << currEnemy->getName() << endl;
							enemies.push_back(currEnemy);
						}
					}
					floorMap[row][col].setObject(obj);
				}
			}
		}
		row++;
	}
	// Gives a compass to a random enemy.
	giveEnemyCompass(enemies);
} // Floor::spawnManual

void Floor::determineInAggroZone(Enemy *enemy, bool &isInAggroZone) {
	Dragon *dragon = static_cast<Dragon *>(enemy);
	if (!dragon) {
		return;
	}
	vector<pair<int, int>> dragonAggroZone = dragon->getAggroZone(); 
	int numZones = dragonAggroZone.size();
	
	cerr << "At Row: " << dragon->getCord()[0] << " Col: " << dragon->getCord()[1]
		 << ", check the number of aggro zones for this dragon: " << numZones << endl;
	for (int i = 0; i < numZones; ++i) {
		int r = dragonAggroZone[i].first;
		int c = dragonAggroZone[i].second;
		Cell *currCell = &(floorMap[r][c]);
		
		if (currCell->getObject() == player) {
			cout << "Within aggro range for Dragon at Row: " << 
					dragon->getCord()[0] << " Col: " << dragon->getCord()[1] << endl;
			isInAggroZone = true;
		}
	}
} // Floor::determineInAggroZone

void Floor::enemyAction() {
    for (auto &row : floorMap) {
        for (auto &cell : row) {
            CellObject *obj = cell.getObject();
            if (obj == nullptr || obj->getCtgy() != Category::Enemy)
                continue;

            Enemy *enemy = static_cast<Enemy *>(obj);
            // Skip if this enemy has already acted this turn
            if (enemy->getCount() > RoundCounter)
                continue;

            vector<int> enemyPos = cell.getInfo().cellObject->getCord();
            vector<int> playerPos = player->getCord();
            int rowDiff = enemyPos[0] - playerPos[0];
            int colDiff = enemyPos[1] - playerPos[1];

			// Checks whether or not the Dragon is aggroed to the player based on
			//   whether or not.
			if (enemy->getName() == "Dragon") {
				Dragon *dragon = static_cast<Dragon *>(enemy);
				// Clears the dragon's aggro from last turn the dragon is aggroed 
				//   in the current turn. 
				dragon->setAggro(false);

				// Two determinants for dragon's current aggro status.
				bool isInAggroZone = false;
				bool isAggroByPlayer = false;

				// Checks if the player is within range of the dragon's horde.
				determineInAggroZone(dragon, isInAggroZone);

				// Checks if the player has attacked the dragon first.
				if (dragon->getAttacked()) {
					// Checks if the player is still within range for the dragon's aggro. 
					if ((rowDiff < -1 || rowDiff > 1 || colDiff < -1 || colDiff > 1) && 
						(!isInAggroZone)){
						dragon->setAttacked(false);
					} else {
						isAggroByPlayer = true;
						cerr << "Dragon has been attacked by player" << endl;
					}
				}

				// Determines the final aggro for dragon for this turn.
				if (isInAggroZone || isAggroByPlayer) {
					dragon->setAggro(true);
				} else {
					dragon->setAggro(false);
				}
			}

            // If the player is adjacent...
            if (rowDiff >= -1 && rowDiff <= 1 && colDiff >= -1 && colDiff <= 1) {
                // Otherwise, if the enemy is aggressive, attack normally.
                if (enemy->isAggro()) {
                    if (rng(0, 1) == 1) {
                        enemy->attackCharacter(player);
                    } else {
                        cout << enemy->getName() << " attacks but missed!" << endl;
                    }
                    enemy->increaseCount();
                    continue;
                }
            }

            // For enemies that are not adjacent, attempt to move if movable.
            if (enemy->isMovable() && enemy->getName() != "Dragon") {
                bool moved = false;
                while (!moved) {
					// Checks the current cell's free neighbours to see if the
					//   enemy can move.
					vector<pair<int, int>> currCellNeighbours = 
						getCellNeighbours(&cell);
					vector<pair<int, int>> freeCellNeighbours = 
						getFreeNeighbours(currCellNeighbours);
					
					// If the enemy cannot move, skip its turn.
					if (freeCellNeighbours.size() == 0) {
						cerr << enemy->getName() << " cannot move!" << endl;
						moved = true;
					} else {
						// Generates a potential new direction to move.
						vector<int> genDirection = generateDirection();
						int newR = enemyPos[0] + genDirection[0];
						int newC = enemyPos[1] + genDirection[1];

						if (newR < FIRSTROW || newR >= LASTROW ||
							newC < FIRSTCOLUMN || newC >= LASTCOLUMN)
							continue;

						Info target = floorMap[newR][newC].getInfo();
						if (target.type == Type::Ground && target.cellObject == nullptr) {
							floorMap[enemyPos[0]][enemyPos[1]].removeObject();
							floorMap[newR][newC].setObject(enemy);
							enemy->setCord(newR, newC);
							enemy->increaseCount();
							moved = true;
						}
					}					
                }
            }
        }
    }
    RoundCounter++;
} // Floor::enemyAction

bool Floor::tryAttack(vector<int> offset) {
    if (!player)
        cerr << "Player is nullptr" << endl;
    vector<int> playerCord = player->getCord();
    int r = playerCord[0] + offset[0];
    int c = playerCord[1] + offset[1];

    if (r < FIRSTROW || r >= LASTROW || c < FIRSTCOLUMN || c >= LASTCOLUMN) {
        return false;
    }

    Info target = floorMap[r][c].getInfo();
    if (target.cellObject != nullptr &&
        target.cellObject->getCtgy() == Category::Enemy) {
        Character *enemy = static_cast<Character *>(target.cellObject);
        player->attackCharacter(enemy);
		
		// If one merchant is attacked, the rest of the merchants, 
		//   even on different floors, will be hostile.
        if (enemy->getName() == "Merchant") {
            turnOnAggro(enemy->getName());
            merchantsAggro = true;
        }

		// If the dragon is attacked, becomes hostile until player
		//   moves out of its range.
		if (enemy->getName() == "Dragon") {
			Dragon * dragon = static_cast<Dragon *>(enemy);
			dragon->setAttacked(true);
			cout << "Dragon is now hostile!" << endl;
		}

        // Only remove the enemy if its HP is zero or less.
        if (enemy->getHP() <= 0) {
			// Removes the enemy from the Floor.
			floorMap[r][c].removeObject();
            if (enemy->getName() == "Dragon") {
				Enemy *dragon = static_cast<Enemy *>(enemy);
				if (dragon) {
					// Removes the Dragon from the floor and releases its guarded items.
					turnOffGuarded(dragon);
				}
            } else if (enemy->getName() == "Merchant") {
				// Merchants drop a Merchant Hoard upon death.
				Item *gold = createItem("merchantGold");
				floorMap[r][c].setObject(gold);
			} else {
                player->addGold(ENEMYGOLD);
            }
			Enemy *enemyCompass = static_cast<Enemy *>(enemy);
			if (enemyCompass && enemyCompass->hasCompass() == true) {
				cout << "Dropping compass" << endl;
				Item *compass = createItem("compass");
				floorMap[r][c].setObject(compass);
			}
            delete enemy;
        }
        return true;
    }
    return false;
} // Floor::tryAttack

int Floor::tryMove(vector<int> offset) {
	if (!player)
		cerr << "Player is nullptr" << endl;
	vector<int> playerCord = player->getCord();
	cerr << "Player Cord: " << playerCord[0] << ", " << playerCord[1] << endl;
	int r = playerCord[0] + offset[0];
	int c = playerCord[1] + offset[1];

	// Check if the Cell to interact with is out of range.
	if (r < FIRSTROW || r >= LASTROW || c < FIRSTCOLUMN || c >= LASTCOLUMN) {
		return false;
	}

	Info target = floorMap[r][c].getInfo();

	// Checks if the current cell can be occupied by the player.
	if (target.type == Type::Ground || target.type == Type::Door ||
	    target.type == Type::Way) {
		// If there is a non-Potion item on the cell, then use it.
		CellObject *obj = target.cellObject;
		// Checks if the object is an item that is not a potion.
		if (obj != nullptr && obj->getCtgy() == Category::Item &&
		    obj->getName() != "Potion") {
			if (obj->getName() == "Stairs") {
				return 2;
			}
			Item *item = static_cast<Item *>(obj);
			if (item->getName() == "Compass") {
				stairs->reveal();
				vector<int> cord = stairs->getCord();
				td->notify(floorMap[cord[0]][cord[1]]);
				floorMap[r][c].removeObject();
				delete obj;
			} else if (item->isGuarded()) {
				item->use(player);
			} else {
				item->use(player);
				floorMap[r][c].removeObject();
				delete obj;			
			}
		}
		if (floorMap[r][c].getInfo().cellObject == nullptr) { // Move operation.
			floorMap[playerCord[0]][playerCord[1]].removeObject();
			floorMap[r][c].setObject(player);
			return 1;
		}
	}
	detectGuardedObj();
	return 0;
} // Floor::tryMove

bool Floor::tryUse(vector<int> offset) {
	if (!player)
		cerr << "Player is nullptr" << endl;
	vector<int> playerCord = player->getCord();
	int r = playerCord[0] + offset[0];
	int c = playerCord[1] + offset[1];
	// cerr << "Target Cord: " << r << " " << c << endl;
	// Check if the Cell to interact with is out of range.
	if (r < FIRSTROW || r >= LASTROW || c < FIRSTCOLUMN || c >= LASTCOLUMN) {
		return false;
	}
	// Gets the info of the Cell that may contain the item that the
	//   player wants to use.
	Info target = floorMap[r][c].getInfo();

	cerr << "checking cellObject is nullptr" << endl;
	if (target.cellObject != nullptr &&
	    target.cellObject->getCtgy() == Category::Item &&
	    target.cellObject->getName() == "Potion") {
		// Cast object on cell to a potion pointer.
		Potion *pot = static_cast<Potion *>(target.cellObject);
		// cerr << "calling use" << endl;
		pot->use(player);
		floorMap[r][c].removeObject();
		// Deletes the potion from memory after usage.
		delete pot;
		return true;
	}
	return false;
} // Floor::tryUse

int Floor::tryBuy(vector<int> offset) {
	if (!player)
		cerr << "Player is nullptr" << endl;
	vector<int> playerCord = player->getCord();
	int r = playerCord[0] + offset[0];
	int c = playerCord[1] + offset[1];
	// cerr << "Target Cord: " << r << " " << c << endl;
	// Check if the Cell to interact with is out of range.
	if (r < FIRSTROW || r >= LASTROW || c < FIRSTCOLUMN || c >= LASTCOLUMN) {
		return false;
	}
	// Gets the info of the Cell that the Merchant may be on.
	Info target = floorMap[r][c].getInfo();
	int retVal = 0;

	cerr << "checking cellObject is nullptr" << endl;
    if (target.cellObject != nullptr &&
        target.cellObject->getCtgy() == Category::Enemy) {
        Character *enemy = static_cast<Character *>(target.cellObject);
		
		if (enemy->getName() == "Merchant") {
			Merchant *merchant = static_cast<Merchant *>(enemy);
			retVal = player->buyFrom(merchant);
        }
	}
	return retVal;
} // Floor::tryUse

void Floor::printMap() { cout << *td; }
// Floor::printMap

PlayerCharacter *Floor::getPlayerPtr() { return player; }
// Floor::getPlayerPtr

int Floor::getScore() {
	return this->getPlayerPtr()->getScore();
} // Floor::getScore

void Floor::turnOnAggro(std::string name) {
	cerr << "Trying to turn on aggro for " << name << endl;
	for (auto &row : floorMap) {
		for (auto &cell : row) {
			CellObject *target = cell.getObject();
			if (target && target->getName() == name) {
				Enemy *enemy = static_cast<Enemy *>(target);
				enemy->turnOnAggro();
				cerr << "Turned on aggro for " << enemy->getName() << " at ("
				     << cell.getInfo().r << ", " << cell.getInfo().c << ")"
				     << endl;
			}
		}
	}
	cerr << name << " Set to Aggressive." << endl;
} // Floor::turnOnAggro

void Floor::turnOffGuarded(Enemy *enemy) {
    cerr << "Trying to turn off a dragon's guarded items." << endl;
	Dragon *dragon = static_cast<Dragon *>(enemy);
	if (!dragon) {
		return;
	}
	vector<pair<int, int>> guardedItems = dragon->getGuarded(); 
	int numItems = guardedItems.size();
	cerr << "Number of items guarded that is being released: " << numItems << endl;
	
	cerr << "At Row: " << dragon->getCord()[0] << " Col: " << dragon->getCord()[1]
		 << ", check the number of guarded items for this dragon: " << numItems << endl;
	for (int i = 0; i < numItems; ++i) {
		int r = guardedItems[i].first;
		int c = guardedItems[i].second;
		Cell *currCell = &(floorMap[r][c]);

		CellObject *target = currCell->getObject();
		if (target && target->getCtgy() == Category::Item) {
			cerr << "Trying to release the item at (" << r << ", " << c << ")" << endl;
			Item *item = static_cast<Item*>(target);
			item->turnOffGuarded();
			cerr << "Checking if the item is still guarded: " << item->isGuarded() << endl;

			cerr << "Turned off guarded for " << item->getName() << " at ("
					<< currCell->getInfo().r << ", " << currCell->getInfo().c << ")"
					<< endl;
		}
	}
} // Floor::turnOffGuarded

bool Floor::isAggro(string name) {
	if (name == "Merchant") {
		return merchantsAggro;
	}
	return false;
} // Floor::isAggro

bool Floor::hasBarrierSuitFloor(string name) {
	if (name == "Barrier Suit") {
		return barrierSuit;
	}
	return false;
} // Floor::hasBarrierSuitFloor

void Floor::turnOnBarrierSuit() {
	barrierSuit = true;
} // Floor::turnOnBarrierSuit

void Floor::detectGuardedObj() {
    if (!this->player) return;

    int pr = player->getCord()[0];
    int pc = player->getCord()[1];

	for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            int rr = pr + dr;
            int cc = pc + dc;

			int rows = floorMap.size();
			int cols = floorMap[rr].size();

            if (rr < 0 || rr >= rows) continue;
            if (cc < 0 || cc >= cols) continue;

            CellObject *obj = floorMap[rr][cc].getObject();
            if (!obj) continue;

            // If it's gold and not accessible => guarded
            Gold *gold = dynamic_cast<Gold*>(obj);
            if (gold && !gold->isAccessible()) {
                cout << "Dragon is now hostile!" << endl;
                // We can keep checking or break out. We'll just keep checking.
            }
        }
	}
} // Floor::detectGuardedObj
