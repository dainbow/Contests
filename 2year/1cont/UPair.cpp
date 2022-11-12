#include <iostream>
#include <iomanip>
#include <bit>

#include <cstdint>
#include <cmath>

#include <unordered_map>

using Coords = std::pair<float, float>;
using Map = std::unordered_map<uint32_t, float>;

static inline uint8_t CalcLogarithm(const uint32_t elem) {
    return 31 - __builtin_clz(elem);
}

void Solve(const uint32_t curS, Map& dp) {
    if (dp.find(curS) != dp.end()) {
        return;
    }

    uint8_t leftBit = CalcLogarithm(curS);
    float answer = MAXFLOAT;

    for (int16_t rightBit = leftBit - 1; rightBit >= 0; rightBit--) {
        if (curS & (1 << rightBit)) {
            uint32_t mask = (1 << leftBit) | (1 << rightBit);
            uint32_t next = curS ^ mask;

            auto it = dp.find(next);

            if (it == dp.end()) {
                Solve(next, dp);

                answer = std::min(answer, dp.find(next)->second + dp.find(mask)->second);
            }
            else {
                answer = std::min(answer, it->second + dp.find(mask)->second);
            }
        }
    }

    dp.insert({curS, answer});
}

int main() {
    uint16_t N = 0;
    std::cin >> N;

    Coords* coords = new Coords[N]();
    for (uint32_t curCoord = 0; curCoord < N; curCoord++) {
        std::cin >> coords[curCoord].first >> coords[curCoord].second;
    }

    Map dp = {};

    for (uint32_t curRow = 0; curRow < N; curRow++) {
        for (uint32_t curColumn = curRow + 1; curColumn < N; curColumn++) {
            dp[(1 << curRow) | (1 << curColumn)] = sqrtf(powf(coords[curColumn].first - coords[curRow].first, 2) +
                                                         powf(coords[curColumn].second - coords[curRow].second, 2));
        }
    }

    Solve((1 << N) - 1, dp);
    std::cout << std::setprecision(4) << dp[(1 << N) - 1] << std::endl;

    delete[] coords;
}
