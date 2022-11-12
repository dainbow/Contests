#include <iostream>
#include <cstdlib>

int main() {
    uint32_t number = 0;
    std::cin >> number;

    uint32_t* db = new uint32_t[number + 1];
    for (uint32_t curNumber = 1; curNumber * curNumber <= number; curNumber++) {
        db[curNumber * curNumber] = 1;
    }

    for (uint32_t curNumber = 1; curNumber <= number; curNumber++) {
        for (uint32_t curSqr = 1; (curNumber + curSqr * curSqr) <= number; curSqr++) {
            if (db[curNumber + curSqr * curSqr] == 0) {
                db[curNumber + curSqr * curSqr] = db[curNumber] + 1;
            }
            else {
                db[curNumber + curSqr * curSqr] = std::min(db[curNumber + curSqr * curSqr], db[curNumber] + 1);
            }
        }
    }

    std::cout << db[number] << std::endl;

    delete[] db;
}
