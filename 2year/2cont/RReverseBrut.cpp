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

uint32_t BFS(std::queue<std::string>& myQueue, std::unordered_map<std::string, uint32_t>& distances, std::unordered_map<std::string, bool>& colors, std::unordered_map<std::string, std::string>& parents) {    
    uint32_t minDistance = UINT32_MAX;

    while (!myQueue.empty()) {
        if (minDistance != UINT32_MAX) {
            break;
        }

        std::string curVertex = myQueue.front();
        myQueue.pop();

        colors.insert({curVertex, Grey});

        std::string newVertex = curVertex;
        for (uint8_t curLeft = 0; curLeft < newVertex.size(); curLeft++) {
            for (uint8_t curRight = curLeft + 1; curRight < newVertex.size(); curRight++) {
                std::reverse(newVertex.begin() + curLeft, newVertex.begin() + curRight + 1);

                if (colors.find(newVertex) == colors.end()) {
                    myQueue.push(newVertex);
                    
                    uint32_t newDistance = 0;
                    auto it = distances.find(curVertex);
                    if (it != distances.end()) {
                        newDistance = it->second;
                    }
                    newDistance++;

                    distances.insert({newVertex, newDistance});
                    parents[newVertex] = curVertex;
 
                    if (newVertex == answer) {
                        minDistance = std::min(minDistance, newDistance);

                        return minDistance;
                    }

                    colors.insert({newVertex, Grey});
                }

                std::reverse(newVertex.begin() + curLeft, newVertex.begin() + curRight + 1);
            }
        }
    }

    return minDistance;
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

    std::unordered_map<std::string, bool> colors;
    std::unordered_map<std::string, uint32_t> distances;
    std::unordered_map<std::string, std::string> parents;

    std::queue<std::string> myQueue;

    answer = endState;
    if (answer == startState) {
        std::cout << "0" << std::endl;

        return 0;
    }

    myQueue.push(startState);

    uint32_t potionAnswer = BFS(myQueue, distances, colors, parents);
    std::cout << potionAnswer << std::endl;

    while (potionAnswer) {
        std::cout << answer << std::endl;
        answer = parents[answer];

        potionAnswer--;
    }
}
