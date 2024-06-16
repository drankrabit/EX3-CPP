#include "catan.hpp"

namespace ariel {

Catan::Catan(Player p1, Player p2, Player p3) {
    this->players[0] = p1;
    this->players[1] = p2;
    this->players[2] = p3;
    minCard = Constants::knight;
    maxCard = Constants::victoryCard;
    std::fill_n(this->turnCounter, 3, 0);
    currentTurn = 0;

    board = new Board();
    board->initializeTiles();
}

Catan::~Catan() {
    delete board;
}

void Catan::rollDice(int cheat) {
    int roll = cheat;
    if (roll == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 12);
        roll = dis(gen);
    }

    std::cout << "Rolled: " << roll << std::endl;

    for (Player& player : this->players) {
        for (Tile& settlement : player.getSettlements()) {
            int tileId = settlement.getId();
            auto neighbors = tiles[tileId].getNeighbors();
            int amount = settlement.getClassification() == Constants::settlement ? 1 : 2;

            for (Tile* p : neighbors) {
                if (p != nullptr && p->getId() == roll) {
                    player.modifyResources(p->getClassification(), amount);
                }
            }
        }
    }

    if (roll == 7) {
        for (Player& player : this->players) {
            if (player.getTotalResources() >= 7) {
                int discard = player.getTotalResources() / 2;
                std::cout << player.getName() << " needs to discard " << discard << " resources." << std::endl;
            }
        }
    }
}

void Catan::placeSettlement(int tileId) {
    // Implement placing a settlement
    if (players[currentTurn].canTrade(Constants::wheat, 1) &&
        players[currentTurn].canTrade(Constants::wood, 1) &&
        players[currentTurn].canTrade(Constants::brick, 1) &&
        players[currentTurn].canTrade(Constants::wool, 1)) {

        players[currentTurn].modifyResources(Constants::wheat, -1);
        players[currentTurn].modifyResources(Constants::wood, -1);
        players[currentTurn].modifyResources(Constants::brick, -1);
        players[currentTurn].modifyResources(Constants::wool, -1);

        players[currentTurn].getSettlements().push_back(tiles[tileId]);
        players[currentTurn].modifyVictoryPoints(1);

        std::cout << "Settlement placed on tile " << tileId << std::endl;
    } else {
        std::cout << "Not enough resources to place a settlement." << std::endl;
    }
}

void Catan::buildCity(int tileId) {
    // Implement building a city
    if (players[currentTurn].canTrade(Constants::wheat, 2) &&
        players[currentTurn].canTrade(Constants::ore, 3)) {

        players[currentTurn].modifyResources(Constants::wheat, -2);
        players[currentTurn].modifyResources(Constants::ore, -3);

        auto& settlements = players[currentTurn].getSettlements();
        auto it = std::find_if(settlements.begin(), settlements.end(),
                               [tileId](const Tile& tile) { return tile.getId() == tileId; });
        if (it != settlements.end()) {
            it->setID(Constants::city);
            players[currentTurn].modifyVictoryPoints(1);
            std::cout << "City built on tile " << tileId << std::endl;
        } else {
            std::cout << "No settlement on the specified tile to upgrade to a city." << std::endl;
        }
    } else {
        std::cout << "Not enough resources to build a city." << std::endl;
    }
}

void Catan::placeRoad(int tileId1, int tileId2, bool isFree) {
    // Implement placing a road
    if (isFree || (players[currentTurn].canTrade(Constants::wood, 1) &&
                   players[currentTurn].canTrade(Constants::brick, 1))) {

        if (!isFree) {
            players[currentTurn].modifyResources(Constants::wood, -1);
            players[currentTurn].modifyResources(Constants::brick, -1);
        }

        tiles[tileId1].addNeighbor(&tiles[tileId2]);
        tiles[tileId2].addNeighbor(&tiles[tileId1]);

        std::cout << "Road placed between tile " << tileId1 << " and tile " << tileId2 << std::endl;
    } else {
        std::cout << "Not enough resources to place a road." << std::endl;
    }
}

void Catan::trade(Player* me, Player* other, int myResource, int myAmount, int theirResource, int theirAmount) {
    // Implement trading resources between players
    if (me->canTrade(myResource, myAmount) && other->canTrade(theirResource, theirAmount)) {
        me->modifyResources(myResource, -myAmount);
        other->modifyResources(theirResource, -theirAmount);

        me->modifyResources(theirResource, theirAmount);
        other->modifyResources(myResource, myAmount);

        std::cout << me->getName() << " traded " << myAmount << " of " << myResource << " with " << other->getName()
                  << " for " << theirAmount << " of " << theirResource << std::endl;
    } else {
        std::cout << "Trade cannot be completed. Not enough resources." << std::endl;
    }
}

void Catan::buyDevelopmentCard() {
    // Implement buying a development card
    if (players[currentTurn].canTrade(Constants::wheat, 1) &&
        players[currentTurn].canTrade(Constants::ore, 1) &&
        players[currentTurn].canTrade(Constants::wool, 1)) {

        players[currentTurn].modifyResources(Constants::wheat, -1);
        players[currentTurn].modifyResources(Constants::ore, -1);
        players[currentTurn].modifyResources(Constants::wool, -1);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minCard, maxCard);

        int card = dis(gen);
        players[currentTurn].modifyResources(card, 1);

        std::cout << "Bought a development card: " << card << std::endl;
    } else {
        std::cout << "Not enough resources to buy a development card." << std::endl;
    }
}

void Catan::useDevelopmentCard(int card) {
    // Implement using a development card
    if (players[currentTurn].getResourceCount(card) > 0) {
        players[currentTurn].modifyResources(card, -1);

        switch (card) {
            case Constants::knight:
                std::cout << "Using Knight card" << std::endl;
                break;
            case Constants::victoryCard:
                players[currentTurn].modifyVictoryPoints(1);
                std::cout << "Using Victory Point card" << std::endl;
                break;
            case Constants::roadBuilding:
                std::cout << "Using Road Building card" << std::endl;
                placeRoad(0, 1, true); // Example, actual implementation would need user input
                placeRoad(1, 2, true); // Example, actual implementation would need user input
                break;
            case Constants::monopoly:
                std::cout << "Using Monopoly card" << std::endl;
                break;
            case Constants::yearOfPlenty:
                std::cout << "Using Year of Plenty card" << std::endl;
                break;
            default:
                std::cout << "Unknown development card" << std::endl;
                break;
        }
    } else {
        std::cout << "You do not have this development card" << std::endl;
    }
}

void Catan::printTurn() {
    players[currentTurn].printPoints();
}

void Catan::endTurn() {
    players[currentTurn].endTurn();
    currentTurn = (currentTurn + 1) % 3;
}

} // namespace ariel