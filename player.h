#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <vector>
#include <utility>
#include <sstream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "dice.h"
#include "tile.h"

extern const int numresocType;

class Player {
    Color color;
    Dice dice;
    std::map<Resource, int> resocMap;
    std::vector<int> occupiedTiles;
    int buildingPoints = 0, resocTotal = 0;
 public:
    void setDice(std::string cmd);
    explicit Player(Color color);
    Player(std::istringstream &playerData, Color color);
    int roll(); //returns tilevalue rolled
    // adds tileNum to vector of occupiedTiles, doesn't add it if it already exists
    void addOccupiedTiles(int tileNum);
    void addBuildingPoints(int num);

    void updateResocMap(const std::pair<Resource, int> &gainedResoc);
    std::map<Resource, int>& getResocMap();
    void getStatus(std::ostream &out);
    // accessors
    std::vector<int>& getOccupiedTiles();
    int getResocTotal();
    Color getColour();

    // geese functions
    std::vector<std::pair<std::string, int>> removeHalfResocs();

    bool hasRes(int tileNum);

    std::string stealResoc();
    void addResoc(std::string resoc);

    std::string getDiceType();

    void removeResoc(std::string resoc);

    int fairRoll();
};

#endif
