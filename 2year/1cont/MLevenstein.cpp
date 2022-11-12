#include <iostream>
#include <cstdint>

#include <string>

uint16_t LeastOfThrees(const uint16_t a, const uint16_t b, const uint16_t c) {
    if (a <= b) {
        if (a <= c) {
            return a;
        }
        else {
            return c;
        }
    }
    else {
        if (b <= c) {
            return b;
        }
        else {
            return c;
        }
    }
}

int main() {
    std::string str1 = "", str2 = "";
    std::cin >> str1 >> str2;

    uint16_t rows = str1.length() + 1, columns = str2.length() + 1;

    uint16_t** matrix = new uint16_t*[rows];
    for (uint16_t curRow = 0; curRow < rows; curRow++) {
        matrix[curRow] = new uint16_t[columns];

        matrix[curRow][0] = curRow;
    }

    for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
        matrix[0][curColumn] = curColumn;
    }

    for (uint16_t curColumn = 1; curColumn < columns; curColumn++) {
        for (uint16_t curRow = 1; curRow < rows; curRow++) {
            matrix[curRow][curColumn] = LeastOfThrees(
                                        matrix[curRow - 1][curColumn - 1] + (str1[curRow - 1] != str2[curColumn - 1]), 
                                        matrix[curRow][curColumn - 1] + 1, matrix[curRow - 1][curColumn] + 1);
        }
    }

    // for (uint16_t curRow = 0; curRow < rows; curRow++) {
    //     for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
    //         std::cout << matrix[curRow][curColumn] << " ";
    //     }

    //     std::cout << std::endl;
    // }

    std::cout << matrix[rows - 1][columns - 1] << std::endl;

    for (uint16_t curRow = 0; curRow < str1.length(); curRow++) {
        delete[] matrix[curRow];
    }
    delete[] matrix;
}
