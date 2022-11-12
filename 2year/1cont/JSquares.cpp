#include <iostream>
#include <cstdint>

#include <vector>

int main() {
    uint16_t matrixSize = 0;
    std::cin >> matrixSize;

    std::vector<std::pair<uint16_t, uint16_t>> ones[2] = {};

    bool** matrix = new bool*[matrixSize]();
    for (uint32_t curRow = 0; curRow < matrixSize; curRow++) {
        matrix[curRow] = new bool[matrixSize]();
    }


    for (uint32_t curRow = 0; curRow < matrixSize; curRow++) {
        for (uint32_t curColumn = 0; curColumn < matrixSize; curColumn++) {
            bool curNumber = 0;
            std::cin >> curNumber;

            if (curNumber == 1) {
                matrix[curRow][curColumn] = 1;
                ones[0].push_back({curColumn, curRow});
            }
        }
    }

    uint16_t maxSize = 1;
    bool curOnes = 0;

    while (true) {
        for (auto& curMatrix : ones[curOnes]) {
            bool flag = 1;

            if ((curMatrix.second + maxSize) >= matrixSize)
                continue;

            if ((curMatrix.first + maxSize) >= matrixSize)
                continue;
            
            for (uint16_t curX = 0; (curX < (maxSize + 1)) && ((curMatrix.first + curX) < matrixSize); curX++) {
                if (matrix[curMatrix.second + maxSize][curMatrix.first + curX] == 0) {
                    flag = 0;
                    break;
                }
            }

            for (uint16_t curY = 0; (curY < (maxSize + 1)) && ((curMatrix.second + curY) < matrixSize); curY++) {
                if (matrix[curMatrix.second + curY][curMatrix.first + maxSize] == 0) {
                    flag = 0;
                    break;
                }
            }

            if (flag) {
                ones[!curOnes].push_back(curMatrix);
            }
        }       

        if (ones[!curOnes].empty())
            break;

        ones[curOnes].clear();
        curOnes = !curOnes;

        maxSize++;
    }

    std::cout << maxSize << std::endl;

    for (uint32_t curRow = 0; curRow < matrixSize; curRow++) {
        delete[] matrix[curRow];
    }
    delete[] matrix;
}
