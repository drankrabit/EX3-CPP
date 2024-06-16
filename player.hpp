#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "constants.hpp"
#include "tile.hpp"
#include "board.hpp"

namespace ariel {

class Player {
private:
    int victoryPoints;
    std::string name;
    std::vector<Tile> settlements;
    int resources[Constants::inventorySize];
    int totalResources;

public:
    Player(); // Default constructor
    Player(const std::string& name);
    ~Player();

    int getTotalResources() const;
    int getVictoryPoints() const;
    std::vector<Tile> getSettlements() const;
    bool canTrade(int resource, int amount);
    void modifyResources(int myResource, int myAmount);
    int getResourceCount(int resource);
    void modifyVictoryPoints(int count);

    void placeSettlement(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
    void placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
    std::string getName() const;

    void rollDice();
    void endTurn();
    void printPoints() const;
};

} // namespace ariel