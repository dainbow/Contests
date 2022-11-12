#include <iostream>
#include <cstdint>

#include <unordered_map>

static inline uint8_t CalcLogarithm(const uint64_t elem) {
    return 63 - __builtin_clzll(elem);
}

void Solve(const uint64_t curS, std::unordered_map<uint64_t, uint64_t>& dp, const uint16_t fieldX, const uint16_t fieldY) {
    if (dp.find(curS) != dp.end()) {
        return;
    }

    uint8_t leftUpThing = CalcLogarithm(curS);

    uint16_t curX = leftUpThing % fieldX;
    uint16_t curY = leftUpThing / fieldX;

    uint64_t mask1 = 3ull << (leftUpThing - 1);
    uint64_t mask2 = 7ull << (leftUpThing - 2);
    uint64_t mask3 = (1ull << (curY * fieldX + curX)) | (1ull << ((curY - 1) * fieldX + curX));
    uint64_t mask4 = (1ull << ((curY - 2) * fieldX + curX)) | mask3; 

    uint64_t answer = 0;
    if (curX > 0) {
        if ((curS & mask1) == mask1) {
            uint64_t nextS = curS ^ mask1;
            auto it = dp.find(nextS);

            if (it == dp.end()) {
                Solve(nextS, dp, fieldX, fieldY);
                answer += dp.find(nextS)->second;
            }
            else {
                answer += it->second;
            }
        }
    }

    if (curX > 1) {
        if ((curS & mask2) == mask2) {
            uint64_t nextS = curS ^ mask2;
            auto it = dp.find(nextS);

            if (it == dp.end()) {
                Solve(nextS, dp, fieldX, fieldY);
                answer += dp.find(nextS)->second;
            }
            else {
                answer += it->second;
            }
        }
    }

    if (curY > 0) {
        if ((curS & mask3) == mask3) {
            uint64_t nextS = curS ^ mask3;
            auto it = dp.find(nextS);

            if (it == dp.end()) {
                Solve(nextS, dp, fieldX, fieldY);
                answer += dp.find(nextS)->second;
            }
            else {
                answer += it->second;
            }
        }
    }

    if (curY > 1) {
        if ((curS & mask4) == mask4) {
            uint64_t nextS = curS ^ mask4;
            auto it = dp.find(nextS);

            if (it == dp.end()) {
                Solve(nextS, dp, fieldX, fieldY);
                answer += dp.find(nextS)->second;
            }
            else {
                answer += it->second;
            }
        }
    }

    dp.insert({curS, answer});
}

int main() {
    uint16_t N = 0, M = 0;
    std::cin >> N >> M;

    if (N > M) {
        std::swap(N, M);
    }

    std::unordered_map<uint64_t, uint64_t> dp = {};
    dp.insert({0, 1});

    Solve((1ull << (N * M)) - 1, dp, N, M);
    std::cout << dp.find((1ull << (N * M)) - 1)->second << std::endl;
}
