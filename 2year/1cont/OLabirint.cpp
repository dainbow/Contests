#include <iostream>
#include <cstdint>

int main() {
    uint16_t rows = 0, columns = 0, amount = 0;
    std::cin >> rows >> columns >> amount;

    std::pair<uint16_t, uint16_t> entrance = {};
    std::pair<uint16_t, uint16_t> exit = {};
    
    uint8_t** matrix = new uint8_t*[rows]();
    for (uint16_t curRow = 0; curRow < rows; curRow++) {
        matrix[curRow] = new uint8_t[columns]();

        for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
            std::cin >> matrix[curRow][curColumn];

            if (matrix[curRow][curColumn] == '@') {
                entrance = {curRow, curColumn};
            }

            if (matrix[curRow][curColumn] == '#') {
                exit = {curRow, curColumn};
            }
        }
    }

    uint64_t*** db = new uint64_t**[amount + 1]();
    for (uint16_t curAmount = 0; curAmount <= amount; curAmount++) {
        db[curAmount] = new uint64_t*[rows]();

        for (uint16_t curRow = 0; curRow < rows; curRow++) {
            db[curAmount][curRow] = new uint64_t[columns]();
        }
    }
    db[0][entrance.first][entrance.second] = 1;

    for (uint16_t curAmount = 1; curAmount <= amount; curAmount++) {
        for (uint16_t curRow = 0; curRow < rows; curRow++) {
            for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
                if (db[curAmount - 1][curRow][curColumn]) {
                    if ((curRow != 0) && (matrix[curRow - 1][curColumn] != '+')) {
                        db[curAmount][curRow - 1][curColumn] += db[curAmount - 1][curRow][curColumn];
                    }

                    if ((curColumn != 0) && (matrix[curRow][curColumn - 1] != '+')) {
                        db[curAmount][curRow][curColumn - 1] += db[curAmount - 1][curRow][curColumn];
                    }

                    if ((curRow != (rows - 1)) && (matrix[curRow + 1][curColumn] != '+')) {
                        db[curAmount][curRow + 1][curColumn] += db[curAmount - 1][curRow][curColumn];
                    }

                    if ((curColumn != (columns - 1)) && (matrix[curRow][curColumn + 1] != '+')) {
                        db[curAmount][curRow][curColumn + 1] += db[curAmount - 1][curRow][curColumn];
                    }
                }
            }
        }

        // for (uint16_t curRow = 0; curRow < rows; curRow++) {
        //     for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
        //         std::cout << db[curAmount][curRow][curColumn] << " ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;
    }

    std::cout << db[amount][exit.first][exit.second] << std::endl;

    for (uint16_t curAmount = 0; curAmount <= amount; curAmount++) {
        for (uint16_t curRow = 0; curRow < rows; curRow++) {
            delete [] db[curAmount][curRow];
        }

        delete[] db[curAmount];   
    }
    delete[] db;

    for (uint16_t curRow = 0; curRow < rows; curRow++) {
        delete[] matrix[curRow];
    }
    delete[] matrix;
}
