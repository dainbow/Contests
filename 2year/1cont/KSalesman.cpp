#include <iostream>
#include <cstdint>

#include <vector>
#include <algorithm>

void FillAnswer(uint32_t answerRow, std::pair<int32_t, uint32_t>** matrix, uint32_t* answer, const uint32_t columns) {
    for (int32_t curColumn = columns - 1; curColumn >= 0; curColumn--) {
        answer[curColumn] = answerRow + 1;
        answerRow = matrix[answerRow][curColumn].second;
    }
}

bool myCmp (uint32_t* i, uint32_t* j) {
    for (uint32_t curNum = 0; curNum < UINT32_MAX; curNum++) {
        if (i[curNum] < j[curNum]) {
            return 1;
        }
        else if (i[curNum] > j[curNum]) {
            return 0;
        }
    }

    return 0;
}

void LeastOfThrees(std::pair<int32_t, uint32_t>& a, std::pair<int32_t, uint32_t>& b, std::pair<int32_t, uint32_t>& c, std::pair<int32_t, uint32_t>& d, const uint32_t curRow) {
    if (a.first <= b.first) {
        if (a.first <= c.first) {
            d.first += a.first;
            d.second = curRow - 1;
        }
        else {
            d.first += c.first;
            d.second = curRow + 1;
        }
    }
    else {
        if (b.first <= c.first) {
            d.first += b.first;
            d.second = curRow;
        }
        else {
            d.first += c.first;
            d.second = curRow + 1;
        }
    }
}

int main() {
    uint32_t rows = 0, columns = 0;
    std::cin >> rows >> columns;

    std::pair<int32_t, uint32_t>** matrix = new std::pair<int32_t, uint32_t>*[rows]();

    for (uint32_t curRow = 0; curRow < rows; curRow++) {
        matrix[curRow] = new std::pair<int32_t, uint32_t>[columns]();

        for (uint32_t curColumn = 0; curColumn < columns; curColumn++) {
            std::cin >> matrix[curRow][curColumn].first;
        }
    }

    for (uint32_t curColumn = 1; curColumn < columns; curColumn++) {
        if (matrix[0][curColumn - 1].first <= matrix[1][curColumn - 1].first) {
            matrix[0][curColumn].first += matrix[0][curColumn - 1].first;
            matrix[0][curColumn].second = 0;
        }
        else {
            matrix[0][curColumn].first += matrix[1][curColumn - 1].first;
            matrix[0][curColumn].second = 1;
        }

        for (uint32_t curRow = 1; curRow < (rows - 1); curRow++) {
            LeastOfThrees(matrix[curRow - 1][curColumn - 1], matrix[curRow][curColumn - 1], matrix[curRow + 1][curColumn - 1], matrix[curRow][curColumn], curRow);
        }

        if (matrix[rows - 1][curColumn - 1].first < matrix[rows - 2][curColumn - 1].first) {
            matrix[rows - 1][curColumn].first += matrix[rows - 1][curColumn - 1].first;
            matrix[rows - 1][curColumn].second = rows - 1;
        }
        else {
            matrix[rows - 1][curColumn].first += matrix[rows - 2][curColumn - 1].first;
            matrix[rows - 1][curColumn].second = rows - 2;
        }
    }

    std::vector<std::pair<int32_t, uint32_t>> min = {{INT32_MAX, 0}};
    for (uint32_t curRow = 0; curRow < rows; curRow++) {
        if (matrix[curRow][columns - 1].first < min[0].first) {
            min[0] = {matrix[curRow][columns - 1].first, curRow};
        }
    }

    for (uint32_t curRow = 0; curRow < rows; curRow++) {
        if ((matrix[curRow][columns - 1].first == min[0].first) && (curRow != min[0].second)) {
            min.push_back({matrix[curRow][columns - 1].first, curRow});
        }
    }

    uint32_t** answer = new uint32_t*[min.size()];
    for (uint32_t curMin = 0; curMin < min.size(); curMin++) {
        answer[curMin] = new uint32_t[columns];
        FillAnswer(min[curMin].second, matrix, answer[curMin], columns);
    }
    
    std::sort(answer, answer + min.size(), myCmp);

    for (uint32_t curColumn = 0; curColumn < columns; curColumn++) {
        std::cout << answer[0][curColumn] << " ";
    }
    std::cout << std::endl << min[0].first << std::endl; 
    
    for (uint32_t curMin = 0; curMin < min.size(); curMin++) {
        delete[] answer[curMin];
    }
    delete[] answer;
    for (uint32_t curRow = 0; curRow < rows; curRow++) {
        delete[] matrix[curRow];
    }
    delete[] matrix;
}
