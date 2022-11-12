#include <iostream>
#include <cstdlib>


int main() {
    uint16_t rows = 0, columns = 0;
    std::cin >> rows >> columns;

    int64_t** matrix = new int64_t*[rows]();
    int64_t answer = 0;

    for (uint16_t curRow = 0; curRow < rows; curRow++) {
        matrix[curRow] = new int64_t[columns]();

        for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
            std::cin >> matrix[curRow][curColumn];
            // matrix[curRow][curColumn] = std::rand() - (RAND_MAX / 2);
        }
    }

    for (uint16_t curRow = 0; curRow < rows; curRow++) {
        for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
            if ((curRow == 0) && (curColumn == 0)) {
                continue;
            }
            else if ((curRow != 0) && (curColumn != 0)) {
                matrix[curRow][curColumn] += matrix[curRow][curColumn - 1] + matrix[curRow - 1][curColumn] - matrix[curRow - 1][curColumn - 1];
            }
            else if (curRow == 0) {
                matrix[curRow][curColumn] += matrix[curRow][curColumn - 1];
            }
            else if (curColumn == 0) {
                matrix[curRow][curColumn] += matrix[curRow - 1][curColumn];
            }
        }
    }

    // for (uint16_t curRow = 0; curRow < rows; curRow++) {
    //     for (uint16_t curColumn = 0; curColumn < columns; curColumn++) {
    //         std::cout << matrix[curRow][curColumn] << " ";
    //     }

    //     std::cout << std::endl;
    // }

    for (uint16_t x1 = 0; x1 < columns; x1++) {
        for (uint16_t y1 = 0; y1 < rows; y1++) {
            for (uint16_t x2 = x1; x2 < columns; x2++) {
                for (uint16_t y2 = y1; y2 < rows; y2++) {
                    int64_t curSum = 0;

                    if ((x1 == 0) && (y1 == 0)) {
                        curSum = matrix[y2][x2];
                    }
                    else if (x1 == 0) {
                        curSum = matrix[y2][x2] - matrix[y1 - 1][x2];
                    }
                    else if (y1 == 0) {
                        curSum = matrix[y2][x2] - matrix[y2][x1 - 1];
                    }
                    else {
                        curSum = matrix[y2][x2] - matrix[y2][x1 - 1] - matrix[y1 - 1][x2] + matrix[y1 - 1][x1 - 1];
                    }

                    answer = std::max(curSum, answer);
                }
            }
        }
    }

    std::cout << answer << std::endl;

    for (uint16_t curRow = 0; curRow < rows; curRow++) {
        delete[] matrix[curRow];
    }
    delete[] matrix;
}
