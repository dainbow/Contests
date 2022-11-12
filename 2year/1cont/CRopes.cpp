#include <iostream>
#include <cstdint>
#include <algorithm>

int main() {
    uint32_t ropesAmount;
    std::cin >> ropesAmount;

    int32_t* ropesCoords = new int32_t[ropesAmount]();
    for (uint32_t curRope = 0; curRope < ropesAmount; curRope++) {
        std::cin >> ropesCoords[curRope];
    }
    std::sort(ropesCoords, ropesCoords + ropesAmount);

    uint32_t* db = new uint32_t[ropesAmount]();
    db[1] = ropesCoords[1] - ropesCoords[0];
    db[2] = db[1] + (ropesCoords[2] - ropesCoords[1]);

    for (uint32_t curRope = 3; curRope < ropesAmount; curRope++) {
        db[curRope] = (ropesCoords[curRope] - ropesCoords[curRope - 1]) + std::min(db[curRope - 2], db[curRope - 1]);
    }

    std::cout << db[ropesAmount - 1];

    delete[] db;
    delete[] ropesCoords;
}