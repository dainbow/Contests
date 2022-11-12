#include <iostream>
#include <cstdint>
#include <cassert>

#include <bit>
#include <set>

static inline uint32_t CalcLogarithm(const uint32_t elem) {
    return 31 - __builtin_clz(elem);
}

int main() {
    uint32_t shopsAmount = 0, thingsAmount = 0;
    std::cin >> shopsAmount >> thingsAmount;

    uint32_t* tripCosts = new uint32_t[shopsAmount]();

    uint32_t** shopsAndPrices = new uint32_t*[shopsAmount]();

    for (uint32_t curShop = 0; curShop < shopsAmount; curShop++) {
        std::cin >> tripCosts[curShop];
        
        shopsAndPrices[curShop] = new uint32_t[thingsAmount]();
        for (uint32_t curThing = 0; curThing < thingsAmount; curThing++) {
            std::cin >> shopsAndPrices[curShop][curThing];
        }
    }
    uint32_t** db = new uint32_t*[shopsAmount];
    for (uint32_t curShop = 0; curShop < shopsAmount; curShop++) {
        db[curShop]    = new uint32_t[1 << thingsAmount];
        db[curShop][0] = tripCosts[curShop];
    }

    for (int64_t curCase = 1; curCase < (1 << thingsAmount); curCase++) {
        uint32_t min = UINT32_MAX;

        for (uint32_t curBit = 0; curBit < thingsAmount; curBit++) {
            if (curCase & (1 << curBit)) {
                min = std::min(db[0][curCase ^ (1 << curBit)] + shopsAndPrices[0][curBit], min);
            }
        }

        db[0][curCase] = min;
    }

    for (uint32_t curShop = 1; curShop < shopsAmount; curShop++) {
        for (int64_t curCase = 1; curCase < (1 << thingsAmount); curCase++) {
            uint32_t min = UINT32_MAX;

            for (uint32_t curBit = 0; curBit < thingsAmount; curBit++) {
                if (curCase & (1 << curBit)) {
                    min = std::min(db[curShop - 1][curCase ^ (1 << curBit)] + 
                                    tripCosts[curShop] + shopsAndPrices[curShop][curBit], min);
                }
            }  

            for (uint32_t curBit = 0; curBit < thingsAmount; curBit++) {
                if (curCase & (1 << curBit)) {
                    min = std::min(db[curShop][curCase ^ (1 << curBit)] + shopsAndPrices[curShop][curBit], min);
                }
            }

            db[curShop][curCase] = min;
            
        }

        for (int64_t curCase = 1; curCase < (1 << thingsAmount); curCase++) {
            db[curShop][curCase] = std::min(db[curShop][curCase], db[curShop - 1][curCase]);
        }
    }

    std::cout << db[shopsAmount - 1][(1 << thingsAmount) - 1] << std::endl;

    for (uint32_t curShop = 0; curShop < shopsAmount; curShop++) {
        delete[] db[curShop];
    }
    delete[] db;

    for (uint32_t curShop = 0; curShop < shopsAmount; curShop++) {
        delete[] shopsAndPrices[curShop];
    }
    delete[] shopsAndPrices;
    
    delete[] tripCosts;
}