#include <iostream>
#include <cstdlib>
#include <cassert>

#include <vector>
#include <list>
#include <array>

#include <queue>
#include <unordered_map>
#include <algorithm>

const bool White = 0;
const bool Grey  = 1;

std::string answer;

using Pair  = std::pair<std::string, uint8_t>;

std::unordered_map<std::string, uint8_t> distances;

class PairCmp {
    public:
        bool operator()(const Pair& p1, const Pair& p2) {
            return (p1.second) > (p2.second);
        }
}; 

using Queue = std::priority_queue<Pair, std::vector<Pair>, PairCmp>;

uint8_t GetEuristic(std::string& newString) {
    uint8_t result = 0;
    for (uint8_t curChar = 0; curChar < newString.size(); curChar++) {
        if (answer[curChar] != newString[curChar]) {
            // assert(result < UINT8_MAX);
            result++;
        }   
        else {
            
        }
    }

    return result;
}

uint32_t BFS(Queue& myQueue) {    
    while (!myQueue.empty()) {
        Pair curVertex = myQueue.top();
        myQueue.pop();
        
        if (curVertex.first == answer) {
            return distances[curVertex.first];
        }

        std::string newVertex = curVertex.first;
        for (uint8_t curLeft = 0; curLeft < newVertex.size(); curLeft++) {
            for (uint8_t curRight = curLeft + 1; curRight < newVertex.size(); curRight++) {
                std::reverse(newVertex.begin() + curLeft, newVertex.begin() + curRight + 1);
                
                uint8_t newDistance = distances[curVertex.first] + 1;
                // std::cou.t << (uint16_t)(newDistance) << std::endl;
                if ((distances.find(newVertex) == distances.end()) || (distances[newVertex] > newDistance)) {
                    distances[newVertex] = newDistance;

                    myQueue.push({newVertex, newDistance + GetEuristic(newVertex)});
                }

                std::reverse(newVertex.begin() + curLeft, newVertex.begin() + curRight + 1);
            }
        }
    }

    assert(0);
    return UINT32_MAX;
}

int32_t main() {
    uint16_t stringSize = 0;
    std::cin >> stringSize;

    std::string startState(stringSize, 'a');
    std::string endState(stringSize, 'a');

    for (uint16_t curChar = 0; curChar < (2 * stringSize); curChar++) {
        uint16_t inChar = 0;
        std::cin >> inChar;

        if (curChar < stringSize) {
            startState[curChar] = uint8_t('0' + (inChar - 1));
        }
        else {
            endState[curChar - stringSize] = uint8_t('0' + (inChar - 1));
        }
    }

    std::unordered_map<std::string, std::string> parents;
    std::unordered_map<std::string, bool> colors;

    Queue myQueue;

    answer = endState;
    if (answer == startState) {
        std::cout << "0" << std::endl;

        return 0;
    }

    myQueue.push({startState, 0 + GetEuristic(startState)});
    distances[startState] = 0;

    uint32_t potionAnswer = BFS(myQueue);
    std::cout << potionAnswer << std::endl;

    // while(potionAnswer) {
    //     std::cout << answer << std::endl;
    //     answer = parents[answer];

    //     potionAnswer--;
    // }

    // std::cout << answer << std::endl;
}

//
// TEST
// 10
// 1 2 3 4 5 6 7 8 9 10
// 7 2 9 5 6 10 4 3 1 8
