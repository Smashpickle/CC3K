#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Floor.h"
#include <string>
#include <vector>


class PlayerCharacter;
class Floor;
class TextDisplay;

class Controller {
    std::string mapName = "";
    PlayerCharacter* player = nullptr;
    Floor* playground = nullptr;
    int floorNumber = 1;
    int score = 0;
    std::string playerRace = "";
    // convert from direction to 2 int=
    std::vector<int> convert(std::string direction);
    bool wasMerchantsAggro = false;
    bool hasBarrierSuit = false;
    bool gameIsOver = false;

  public:
    // Controller(std::string mn, std::fstream& mi);
    Controller(std::string mn);
    ~Controller(); 
    void start(); // initialize floor and objects, then call loop
    void loop(); // continuously ask for command and call fucntions
    void restart(); // reinitialize everything. Called when start or when
    void goDown();
    void gameOver();
};

#endif
