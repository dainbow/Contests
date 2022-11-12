#include <iostream>
#include <cstdlib>
#include <cassert>

#include <vector>
#include <list>
#include <array>

#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

std::unordered_set<std::string> d1;
std::unordered_set<std::string> d2;

using Queue = std::queue<std::string>;

uint32_t BFS(Queue& q1, Queue& q2, const uint16_t stringSize) {  
    uint16_t qMax = 0;

    while (!q1.empty() && !q2.empty()) {
        if (q1.size() > q2.size()) {
            std::swap(q1, q2); std::swap(d1, d2);
        }

        for (uint64_t curQSize = q1.size(); curQSize; curQSize--) {
            std::string curVertex = q1.front(); q1.pop();

            for (uint8_t curLeft = 0; curLeft < (stringSize - 1); curLeft++) {
                for (uint8_t curRight = curLeft + 1; curRight < stringSize; curRight++) {
                    std::string newVertex = curVertex;
                    std::reverse(newVertex.begin() + curLeft, newVertex.begin() + curRight + 1);
                    
                    if (d2.find(newVertex) != d2.end()) {
                        return qMax + 1;
                    }   

                    if ((d1.find(newVertex) == d1.end())) {
                        q1.push(newVertex);
                        d1.insert(newVertex);
                    }
                }
            }
        }

        ++qMax;
        if (qMax >= (stringSize - 1)) {
            return (stringSize - 1);
        }
    }

    return UINT32_MAX;
}

int32_t main() {
    uint16_t stringSize = 0;
    std::cin >> stringSize;

    std::string startState;
    std::string endState;

    for (uint16_t curChar = 0; curChar < (2 * stringSize); curChar++) {
        uint16_t inChar = 0;
        std::cin >> inChar;

        if (curChar < stringSize) {
            startState.push_back(uint8_t('0' + (inChar - 1)));
        }
        else {
            endState.push_back(uint8_t('0' + (inChar - 1)));
        }
    }

    if (startState == endState) {
        std::cout << "0" << std::endl;
        
        return 0;
    }

    std::unordered_map<std::string, std::string> parents;
    std::unordered_map<std::string, bool> colors;

    Queue q1;
    Queue q2;

    q1.push(startState);
    d1.insert(startState);

    q2.push(endState);
    d2.insert(endState);

    uint32_t potionAnswer = BFS(q1, q2, stringSize);
    std::cout << potionAnswer << std::endl;
}

//
// TEST
// 10
// 1 2 3 4 5 6 7 8 9 10
// 10 8 9 5 7 3 4 2 6 1
