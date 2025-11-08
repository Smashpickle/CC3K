#ifndef FLOOR_H
#define FLOOR_H
#include "Cell.h"
#include "PlayerCharacter.h"
#include "TextDisplay.h"
#include "Enemy.h"

#include <fstream>
#include <memory>
#include <vector>

class Stairs;

class Floor {
	std::vector<std::vector<Cell>> floorMap; // Vector of Cells on the floor.
	TextDisplay *td = nullptr;
	PlayerCharacter *player = nullptr;
	std::vector<std::vector<Cell *>> vacantChamberCells;
	std::vector<std::pair<int, int>> changedCells;
	std::vector<int> counterArr;
	Stairs *stairs= nullptr;
	bool merchantsAggro = false;
	bool barrierSuit = false;
	void createRandomPlacement(int &cellCount, int &randomCell,
	                           int playerRoom = -1);
	void occupyCell(int randomChamber, int randomCell, CellObject *co);
	int RoundCounter = 0;

  public:
	~Floor();
	void init(std::string mapName);
	std::vector<int> generateDirection();
	PlayerCharacter *spawnPlayer(std::string name); // generate and place
	int placePlayer();

	void setPlayer(PlayerCharacter *player);
	void spawnEnemies(); // generate and place
	void spawnStairs(int playerRoom);
	void spawnPotions();
	std::vector<std::pair<int, int>> getCellNeighbours(Cell* cell);
	std::vector<std::pair<int, int>> getFreeNeighbours
									 (std::vector<std::pair<int, int>> neigh);
									 
	void manualRemoveFreeCell(int chamberNumber, Cell* cellToRemove);
	bool determineSpawnBS(std::vector<std::pair<int, int>> freeGoldNeighbours,
						  int goldNumFreeNeigh);
	void spawnGold();
	void spawnManual(std::string mapName, PlayerCharacter *ptr, int floorNum);
	
	void determineInAggroZone(Enemy *enemy, bool &isInAggroZone);
	void enemyAction();

	void giveEnemyCompass(std::vector<Enemy*> enemies);
	bool tryAttack(std::vector<int> offset);
	int tryMove(std::vector<int> offset);
	bool tryUse(std::vector<int> offset);
	int tryBuy(std::vector<int> offset);
	void printMap();
	PlayerCharacter *getPlayerPtr();
	int getScore();
	void turnOnAggro(std::string name);
	bool isAggro(std::string name);
	bool hasBarrierSuitFloor(std::string name);
	void turnOnBarrierSuit();
	void turnOffGuarded(Enemy *enemy);
	void detectGuardedObj();
};

#endif
