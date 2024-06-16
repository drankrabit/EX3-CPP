#include "player.hpp"
#include "board.hpp"
#include <stdexcept>
#include <iostream>

namespace ariel {

Player::Player() : name(""), victoryPoints(0), totalResources(0) {
    std::fill(this->resources, this->resources + Constants::inventorySize, 0);
}

Player::Player(const std::string& name) : name(name), victoryPoints(0), totalResources(0) {
    std::fill(this->resources, this->resources + Constants::inventorySize, 0);
}

Player::~Player() {}

int Player::getVictoryPoints() const {
    return this->victoryPoints;
}

std::vector<Tile> Player::getSettlements() const {
    return this->settlements;
}

bool Player::canTrade(int resource, int amount) {
    return this->resources[resource] >= amount;
}

void Player::modifyResources(int myResource, int myAmount) {
    this->resources[myResource] += myAmount;
    if (Constants::WOOD <= myResource && myResource <= Constants::WOOL) {
        this->totalResources += myAmount;
    }
}

int Player::getResourceCount(int resource) {
    return this->resources[resource];
}

void Player::modifyVictoryPoints(int count) {
    this->victoryPoints += count;
}

int Player::getTotalResources() const {
    return this->totalResources;
}

void Player::placeSettlement(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
    // Implementation for placing a settlement
}

void Player::placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
    // Implementation for placing a road
}

std::string Player::getName() const {
    return name;
}

void Player::rollDice() {
    // Implementation for rolling dice
}

void Player::endTurn() {
    // Implementation for ending turn
}

void Player::printPoints() const {
    std::cout << name << " has " << victoryPoints << " points." << std::endl;
}

} // namespace ariel