#include <iostream>
#include <cstdlib>
#include <cassert>

#include <vector>
#include <list>
#include <array>

#include <queue>
#include <unordered_map>

const bool White = 0;
const bool Grey  = 1;

const std::string answer = "123456789\b";

static inline void Check(std::unordered_map<std::string, bool>& colors, std::unordered_map<std::string, uint32_t>& distances, const std::string& curV, const std::string& newV, std::queue<std::string>& queue, uint32_t& minDistance) {
    if (colors.find(newV) == colors.end()) {
        queue.push(newV);
        
        uint32_t newDistance = 0;
        auto it = distances.find(curV);
        if (it != distances.end()) {
            newDistance = it->second;
        }
        newDistance++;

        distances.insert({newV, newDistance});

        if (newV == answer) {
            minDistance = std::min(minDistance, newDistance);
        }

        colors.insert({newV, Grey});
    }
}

uint32_t BFS(std::queue<std::string>& myQueue, std::unordered_map<std::string, uint32_t>& distances, std::unordered_map<std::string, bool>& colors) {    
    uint32_t minDistance = UINT32_MAX;

    while (!myQueue.empty()) {
        if (minDistance != UINT32_MAX) {
            break;
        }

        std::string curVertex = myQueue.front();
        myQueue.pop();

        colors.insert({curVertex, Grey});

        std::string newVertex = curVertex;

        if (curVertex[9] >= 3) {
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] - 3]);
            newVertex[9] -= 3;

            Check(colors, distances, curVertex, newVertex, myQueue, minDistance);

            newVertex[9] += 3;
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] - 3]);
        }

        if (curVertex[9] < 6) {
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] + 3]);
            newVertex[9] += 3;

            Check(colors, distances, curVertex, newVertex, myQueue, minDistance);

            newVertex[9] -= 3;
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] + 3]);          
        }

        if ((curVertex[9] % 3) > 0) {
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] - 1]);
            newVertex[9] -= 1;

            Check(colors, distances, curVertex, newVertex, myQueue, minDistance);

            newVertex[9] += 1;
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] - 1]);          
        }

        if ((curVertex[9] % 3) < 2) {
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] + 1]);
            newVertex[9] += 1;

            Check(colors, distances, curVertex, newVertex, myQueue, minDistance);

            newVertex[9] -= 1;
            std::swap(newVertex[curVertex[9]], newVertex[curVertex[9] + 1]);          
        }
    }

    return minDistance;
}

int32_t main() {
    std::string startState(10, 'a');
    for (uint8_t curChar = 0; curChar < 9; curChar++) {
        int32_t inChar = getchar();
        
        if (inChar == '\n') {
            curChar--;
            continue;
        }
        else if (inChar == ' ') {
            startState[curChar] = '9';
            startState[9] = curChar;
        }
        else {
            startState[curChar] = char(inChar);
        }
    }

    std::unordered_map<std::string, bool> colors;
    std::unordered_map<std::string, uint32_t> distances;

    std::queue<std::string> myQueue;
    myQueue.push(startState);

    uint32_t potionAnswer = BFS(myQueue, distances, colors);
    if (potionAnswer == UINT32_MAX) {
        std::cout << "-1" << std::endl;
    }
    else {
        std::cout << potionAnswer << std::endl;
    }
}
