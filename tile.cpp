#include "tile.hpp"

Tile::Tile(int id, Constants::TileType type) : id(id), type(type), resourceType(Constants::WOOD) {}

int Tile::getID() const {
    return id;
}

void Tile::setID(int id) {
    this->id = id;
}

Constants::TileType Tile::getType() const {
    return type;
}

void Tile::setType(Constants::TileType type) {
    this->type = type;
}

Constants::ResourceType Tile::getResourceType() const {
    return resourceType;
}

void Tile::setResourceType(Constants::ResourceType resourceType) {
    this->resourceType = resourceType;
}