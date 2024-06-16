#pragma once

#include "constants.hpp"

class Tile {
private:
    int id;
    Constants::TileType type;
    Constants::ResourceType resourceType;

public:
    Tile(int id, Constants::TileType type);

    int getID() const;
    void setID(int id);

    Constants::TileType getType() const;
    void setType(Constants::TileType type);

    Constants::ResourceType getResourceType() const;
    void setResourceType(Constants::ResourceType resourceType);
};