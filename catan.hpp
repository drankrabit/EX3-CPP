#pragma once

#include <vector>
#include "player.hpp"
#include "board.hpp"
#include "tile.hpp"

namespace ariel {

class Catan {
private:
    Player players[3];
    Board* board;
    int currentTurn;
    int minCard;
    int maxCard;
    int turnCounter[3];
    std::vector<Tile> tiles;

public:
    Catan(Player p1, Player p2, Player p3);
    ~Catan();

    void rollDice(int cheat = 0);
    void placeSettlement(int tileId);
    void buildCity(int tileId);
    void placeRoad(int tileId1, int tileId2, bool isFree = false);
    void trade(Player* me, Player* other, int myResource, int myAmount, int theirResource, int theirAmount);
    void buyDevelopmentCard();
    void useDevelopmentCard(int card);
    void printTurn();
    void endTurn();
};

} // namespace ariel