#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <queue>
#include <queue>
#include <functional>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/



struct Receipe {
    int actionId; // the unique ID of this spell or recipe
    string actionType; // in the first league: BREW; later: CAST, OPPONENT_CAST, LEARN, BREW
    std::array<int, 4> tier;
    int price; // the price in rupees if this is a potion
    int tomeIndex; // in the first two leagues: always 0; later: the index in the tome if this is a tome spell, equal to the read-ahead tax; For brews, this is the value of the current urgency bonus
    int taxCount; // in the first two leagues: always 0; later: the amount of taxed tier-0 ingredients you gain from learning this spell; For brews, this is how many times you can still gain an urgency bonus
    bool castable; // in the first league: always 0; later: 1 if this is a castable player spell
    bool repeatable; // for the first two leagues: always 0; later: 1 if this is a repeatable player spell

    void dump() {
        std::cerr << "Action: " << actionId << " type:" << actionType
            << " Tier: [" <<
            tier[0] << "," << tier[1] << "," << tier[2] << "," << tier[3] <<
            "] "
            << "Price:" << price << " tomeIndex:" << tomeIndex << " Taxcount:" << taxCount
            << " Castable: " << castable << " repeatable:" << repeatable << std::endl;
    }
};


struct Inventory {
    std::array<int, 4> tier;
    int score;
    void dump() {
        std::cerr << "[" <<
            tier[0] << "," << tier[1] << "," << tier[2] << "," << tier[3] <<
            "]"
            << " Score: " << score << std::endl;
    }
    void subtract(const Receipe& receipe) {
        for (int i = 0; i < 4; i++) {
            tier[i] += receipe.tier[i];
        }
    }
};




bool comparePrice(const Receipe& left, const Receipe& right) {
    return left.price < right.price;
}


void convertInputs(std::priority_queue<Receipe, std::vector<Receipe>, std::function<bool(Receipe, Receipe)>>& actions, Inventory& inventory) {
    int actionCount; // the number of spells and recipes in play
    cin >> actionCount; cin.ignore();

    for (int i = 0; i < actionCount; i++) {
        Receipe receipe;
        cin >> receipe.actionId >> receipe.actionType >>
            receipe.tier[0] >> receipe.tier[1] >> receipe.tier[2] >> receipe.tier[3] >>
            receipe.price >> receipe.tomeIndex >> receipe.taxCount >> receipe.castable >>
            receipe.repeatable; cin.ignore();

        actions.emplace(std::move(receipe));
    }

    cin >> inventory.tier[0] >> inventory.tier[1] >> inventory.tier[2] >> inventory.tier[3] >> inventory.score; cin.ignore();
}

void print_queue(std::priority_queue<Receipe, std::vector<Receipe>, std::function<bool(Receipe, Receipe)>>& q) {
    while (!q.empty()) {
        Receipe action = q.top();
        action.dump();
        q.pop();
    }
}

bool canICraft(const Receipe& receipe, const Inventory& inventory) {
    bool check = true;
    for (int i = 0; i < 4; i++) {
        if (abs(receipe.tier[i]) > inventory.tier[i]) {
            check = false;
            break;
        }
    }
    return check;
}

void craft_queue(std::priority_queue<Receipe, std::vector<Receipe>, std::function<bool(Receipe, Receipe)>>& q, Inventory& inventory) {
    while (!q.empty()) {
        Receipe action = q.top();
        if (canICraft(action, inventory)) {
            std::cout << "BREW " << action.actionId << std::endl;
        }
        q.pop();
    }
}



int main()
{


    while (1) {

        std::priority_queue<Receipe, std::vector<Receipe>, std::function<bool(Receipe, Receipe)>> actions(comparePrice);
        Inventory inventory;

        convertInputs(actions, inventory);

        //inventory.dump();

        //print_queue(actions);
        craft_queue(actions, inventory);


    }
}
