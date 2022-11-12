#include <iostream>

#include <set>
#include <vector>
#include <string>

void Solve(std::set<std::vector<char>>& answer, std::vector<char>& curState, const std::vector<char>& vocab) {
    if (curState.size() == 8) {
        for (auto curChar : curState) {
            std::cout << curChar << " ";
        }
        std::cout << std::endl;

        answer.insert(curState);
        
        return;
    }

    for (auto& curFig : vocab) {
        uint32_t amount = 0;

        for (auto& curString : curState) {
            if (curString == curFig) {
                amount++;
            }

            if ((curFig == 'p') || (curFig == 'q')) {
                if (amount == 1) {
                    break;
                }
            }
            else {
                if (amount == 2) {
                    break;
                }
            }
        }

        if ((curFig == 'p') || (curFig == 'q')) {
            if (amount == 1) {
                continue;
            }
        }
        else {
            if (amount == 2) {
                continue;
            }
        }

        std::vector<char> newState = curState;
        newState.push_back(curFig);

        Solve(answer, newState, vocab);
    }
}

int main() {
    std::vector<char> vocab = {'l', 'p', 'q', 's', 'k'};

    std::set<std::vector<char>> answer;
    std::vector<char> nullState = {};

    Solve(answer, nullState, vocab);

    uint64_t number = 0;

    int64_t pIdx  = -1;
    int64_t qIdx  = -1;
    int64_t l1Idx = -1;
    int64_t l2Idx = -1;

    for (auto& curVector : answer) {
        for (int8_t curIdx = 0; curIdx < 8; curIdx++) {
            if (curVector[curIdx] == 'p') {
                pIdx = curIdx;
            }
            else if (curVector[curIdx] == 'q') {
                qIdx = curIdx;
            }
            else if (curVector[curIdx] == 'l') {
                if (l1Idx == -1) {
                    l1Idx = curIdx;
                }
                else {
                    l2Idx = curIdx;
                }
            }
        }

        if ((((8 + qIdx - pIdx) % 2) == 1) && (l1Idx < pIdx) && (l1Idx < qIdx) && (l2Idx > pIdx) && (l2Idx > qIdx)) {
            for (auto& curString : curVector) {
                std::cout << curString << " ";
            }
            std::cout << std::endl;
            
            number++;
        }
    }   

    std::cout << number << std::endl;

    uint64_t myNumber = 0;
    for (uint16_t i = 0; i <= 4; i += 2) {
        for (uint16_t j = 2; j <= (6 - i); j++) {
            myNumber += (j - 1) * (8 - (j + i + 1));
        }
    }

    myNumber *= 2;
    myNumber *= 6;

    std::cout << myNumber << std::endl;
}