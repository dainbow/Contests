#include <iostream>
#include <cstdint>

int main() {
    uint16_t sizesAmount = 0;
    std::cin >> sizesAmount;
    
    uint16_t* matriceSizes = new uint16_t[sizesAmount]();
    for (uint16_t curSize = 0; curSize < sizesAmount; curSize++) {
        std::cin >> matriceSizes[curSize];
    }

    uint16_t matricesAmount = sizesAmount - 1;
    uint32_t** db = new uint32_t*[matricesAmount]();
    for (uint16_t curRow = 0; curRow < matricesAmount; curRow++) {
        db[curRow] = new uint32_t[matricesAmount]();
    }

    for (uint16_t curMul = 0; curMul < (matricesAmount - 1); curMul++) {
        db[curMul][curMul + 1] = matriceSizes[curMul] * matriceSizes[curMul + 1] * matriceSizes[curMul + 2];
    }

    for (uint16_t curColumn = 2; curColumn < matricesAmount; curColumn++) {
        for (int32_t curRow = (curColumn - 2); curRow >= 0; curRow--) {
            uint32_t min = UINT32_MAX;
            
            for (uint16_t curDivider = curRow; curDivider < curColumn; curDivider++) {
                min = std::min(min, db[curRow][curDivider] + db[curDivider + 1][curColumn] + 
                                matriceSizes[curRow] * matriceSizes[curDivider + 1] * matriceSizes[curColumn + 1]);
            }

            db[curRow][curColumn] = min;
        }
    }

    std::cout << db[0][matricesAmount - 1] << std::endl;

    for (uint16_t curRow = 0; curRow < matricesAmount; curRow++) {
        delete[] db[curRow];
    }
    delete[] db;

    delete[] matriceSizes;
}
