#include <iostream>
#include <cstdint>

uint8_t FindOne(uint8_t** db, int32_t curX, int32_t curY, int32_t x, int32_t y) {
    int32_t curXCopy = curX;
    for (; curXCopy < x; curXCopy++) {
        if (db[curY][curXCopy] == 2) {
            return 1;
        }
    }

    int32_t curYCopy = curY;
    for (; curYCopy >= 0; curYCopy--) {
        if (db[curYCopy][curX] == 2) {
            return 1;
        }
    }

    for (; (curX < x) && (curY >= 0); curX++, curY--) {
        if (db[curY][curX] == 2) {
            return 1;
        }
    }

    return 2;
}

int main() {
    int32_t x = 0, y = 0;
    std::cin >> x >> y;

    uint8_t** db = new uint8_t*[y]();
    for (uint32_t curRow = 0; curRow < y; curRow++) {
        db[curRow] = new uint8_t[x]();
    }
    db[0][x - 1] = 2;

    for (int32_t curX = x - 1; curX >= 0; curX--) {
        for (int32_t curY = 0; curY < y; curY++) {
            if ((curX == x - 1) && (curY == 0))
                continue;

            db[curY][curX] = FindOne(db, curX, curY, x, y);
        }
    }

    if (db[y - 1][0] == 1) {
        std::cout << "F" << std::endl;
    }
    else {
        std::cout << "S" << std::endl;
    }

    for (uint32_t curRow = 0; curRow < y; curRow++) {
        delete[] db[curRow];
    }
    delete[] db;
}