#include <cstdint>
#include <iostream>

#include <algorithm>

#include <stack>
#include <vector>
#include <unordered_set>

std::unordered_set<uint32_t>* graph = nullptr;
std::vector<uint32_t> answer;

void FindEulerPath(const uint32_t startVertex) {
    while(!graph[startVertex].empty()) {
        uint32_t curVertex = *graph[startVertex].begin();
        graph[startVertex].erase(curVertex);

        FindEulerPath(curVertex);
    }

    answer.push_back(startVertex + 1);
}

int32_t main() {
    uint32_t planetsAmount = 0, startPlanet = 0;
    std::cin >> planetsAmount >> startPlanet;

    graph = new std::unordered_set<uint32_t>[planetsAmount]();
    for (uint32_t curPlanet = 0; curPlanet < planetsAmount; curPlanet++) {
        for (uint32_t anotherPlanet = 0; anotherPlanet < planetsAmount; anotherPlanet++) {
            uint8_t curChar = 0;
            std::cin >> curChar;

            if ((curChar == '0') && (curPlanet != anotherPlanet)) {
                graph[curPlanet].insert(anotherPlanet);
            }
        }
    }

    FindEulerPath(startPlanet - 1);

    for (uint32_t curAnswer = uint32_t(answer.size() - 1); curAnswer > 0; curAnswer--) {
        std::cout << answer[curAnswer] << " " << answer[curAnswer - 1] << std::endl;
    }

    delete[] graph;
}

