#include <iostream>
#include <cstdint>

int main() {
    int32_t amount = 0;
    std::cin >> amount;

    uint8_t* db = new uint8_t[amount + 1];
    db[1] = 1;

    for (uint32_t curPoint = 2; curPoint <= amount; curPoint++) {
        uint8_t max = 0;

        for (uint32_t curTake = 1; curTake * curTake <= curPoint; curTake++) {
            max = std::max(max, db[curPoint - curTake]);
        }

        db[curPoint] = (max == 2) ? 1 : 2;
    }

    if (db[amount] == 1)
        std::cout << "First" << std::endl;
    else
        std::cout << "Second" << std::endl;

    delete[] db;
}