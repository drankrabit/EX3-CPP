#pragma once

#include <vector>
#include "tile.hpp"

class Board {
private:
    std::vector<Tile> tiles;
    int width;
    int height;

public:
    Board(int width, int height);
    Tile& getTile(int tileId);
    void addTile(Tile tile);
    void initializeTiles();
    void placeSettlement(int index);
    void placeRoad(int index1, int index2);
    std::vector<Tile>& getTiles();
};