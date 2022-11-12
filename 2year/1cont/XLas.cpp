#include <iostream>
#include <cstdint>

uint32_t BinarySearch(const int64_t* array, const uint32_t size, const int64_t value) {
    int64_t left  = 0;
    int64_t right = size;

    while (left <= right) {
        int64_t middle = (left + right) / 2;

        if (array[middle] < value) {
            left = middle + 1;
        }
        else if (array[middle] > value) {
            right = middle - 1;
        }
        else {
            return middle;
        }
    }

    return left;
}

int main() {
    uint32_t N = 0;
    std::cin >> N;

    int64_t* array = new int64_t[N]();
    for (uint32_t curIdx = 0; curIdx < N; curIdx++) {
        std::cin >> array[curIdx];
    }


    uint32_t* db = new uint32_t[N]();

    int64_t* lengthsMinValues = new int64_t[N]();
    for (uint32_t curIdx = 0; curIdx < N; curIdx++) {
        lengthsMinValues[curIdx] = INT64_MAX;
    }

    db[0] = 0;
    lengthsMinValues[0] = array[0];

    uint32_t maxLength = 1;
    for (uint32_t curIdx = 1; curIdx < N; curIdx++) {
        int64_t findedIdx = BinarySearch(lengthsMinValues, N, array[curIdx]);

        while (lengthsMinValues[findedIdx] < array[curIdx]) {
            findedIdx++;
        }
        
        if (lengthsMinValues[findedIdx] == INT64_MAX) {
            maxLength = findedIdx + 1;
        }

        lengthsMinValues[findedIdx]  = array[curIdx];
        db[curIdx] = findedIdx;
    }

    std::cout << maxLength << std::endl;

    int64_t lastInt = INT64_MAX;
    uint32_t* answer = new uint32_t[maxLength]();
    for (int64_t curIdx = N - 1, remain = maxLength; (curIdx >= 0) && remain; curIdx--) {
        if ((db[curIdx] == (remain - 1)) && (array[curIdx] < lastInt)) {
            answer[remain - 1] = curIdx;

            remain--;
            lastInt = array[curIdx];
        }
    }
    for (uint32_t curIdx = 0; curIdx < maxLength; curIdx++) {
        std::cout << answer[curIdx] << " ";
    }
    std::cout << std::endl;

    delete[] answer;
    delete[] lengthsMinValues;
    delete[] db;
    delete[] array;
}
