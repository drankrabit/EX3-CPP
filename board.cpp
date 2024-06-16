#include "board.hpp"
#include <random>

Board::Board(int width, int height) : width(width), height(height) {
    tiles.reserve(width * height);
}

Tile& Board::getTile(int tileId) {
    return tiles[tileId];
}

void Board::addTile(Tile tile) {
    tiles.push_back(tile);
}

void Board::initializeTiles() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 12);

    for (Tile& tile : tiles) {
        int classification = tile.getType();
        if (Constants::FOREST <= classification && classification <= Constants::PASTURE_LAND) {
            tile.setResourceType(static_cast<Constants::ResourceType>(classification));
        } else {
            tile.setResourceType(Constants::WOOD); // Default to wood if undefined
        }
    }
}

void Board::placeSettlement(int index) {
    tiles[index].setType(Constants::SETTLEMENT);
}

void Board::placeRoad(int index1, int index2) {
    tiles[index1].setType(Constants::ROAD);
    tiles[index2].setType(Constants::ROAD);
}

std::vector<Tile>& Board::getTiles() {
    return tiles;
}