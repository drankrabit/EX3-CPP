#pragma once

namespace Constants {
    enum TileType {
        EMPTY, SETTLEMENT, CITY, SEA, DESERT, FOREST, HILLS, MOUNTAINS, AGRICULTURAL_LAND, PASTURE_LAND, ROAD
    };

    enum ResourceType {
        WOOD, BRICK, WHEAT, ORE, WOOL
    };

    const int mapWidth = 5;
    const int mapHeight = 5;
    const int totalTiles = mapWidth * mapHeight;
    const int inventorySize = 5;

    // Adjust these constants to not conflict with the enums
    const int DESERT_RESOURCE = 4;
    const int WOOD_RESOURCE = 5;
    const int WOOL_RESOURCE = 9;
    const int knight = 0;
    const int victoryCard = 1;
}