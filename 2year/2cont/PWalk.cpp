#include <iostream>
#include <cstdint>
#include <cassert>

#include <queue>
#include <list>
#include <set>

const uint8_t White = 0;
const uint8_t Gray  = 1;
const uint8_t Black = 2;

const uint8_t MaxDistance = 11;

struct WEdge {
    uint16_t parentV;
    uint16_t curV;

    uint32_t weight;
};

using Pair = std::pair<uint16_t, uint16_t>;

class WEdgeCmp {
    public:
        bool operator()(const WEdge& p1, const WEdge& p2) {
            return p1.weight > p2.weight;
        }
};

class BFS {
    public:
        uint32_t* distances;
        uint16_t* parents;
        std::queue<WEdge>* queue;
        
        std::vector<WEdge>* graph;

        uint16_t vAmount;
        uint16_t eAmount;

        bool* color;
        bool* eColor;

        BFS(const uint16_t vertexAmount, const uint16_t edgeAmount) :
            distances(new uint32_t[vertexAmount]()),
            parents(new uint16_t[vertexAmount]()),
            queue(new std::queue<WEdge>[MaxDistance]),
            graph(new std::vector<WEdge>[vertexAmount]()),
            vAmount(vertexAmount), eAmount(edgeAmount),
            color(new bool[vertexAmount]()), eColor(new bool[edgeAmount]())
            {
                Clear();
            }

        ~BFS() {
            delete[] color;
            delete[] graph;
            delete[] queue;
            delete[] parents;
            delete[] distances;
        }

        BFS (const BFS& bfs) = delete;
        BFS operator=(const BFS& bfs) = delete;

        void Clear() {
            for (uint16_t curV = 0; curV < vAmount; curV++) {
                distances[curV] = UINT32_MAX;
                parents[curV]   = UINT16_MAX;

                color[curV] = White;
            }
        }

        uint32_t operator()(const uint16_t startV) {
            distances[startV] = 0;

            WEdge nextEdge = {0, startV, 0};
            queue[0].push(nextEdge);
            
            uint32_t answer = UINT32_MAX;

            uint32_t qSizes = 1;
            uint32_t curIdx = 0;
            while (qSizes) {
                while (queue[curIdx].empty()) {
                    curIdx = (curIdx + 1) % MaxDistance;
                }

                WEdge curV = queue[curIdx].front();


                queue[curIdx].pop();
                qSizes--;

                if (color[curV.curV] != White) {
                    continue;
                }

                color[curV.curV]   = Gray;

                if (curV.curV != startV) {
                    parents[curV.curV] = curV.parentV;
                }

                for (auto& newV : graph[curV.curV]) {
                    if ((distances[curV.curV] + newV.weight) < distances[newV.curV]) {
                        distances[newV.curV] = distances[curV.curV] + newV.weight;

                        WEdge newEdge = {newV.parentV, newV.curV, uint16_t((distances[curV.curV] + newV.weight) % MaxDistance)};
                        
                        queue[distances[newV.curV] % MaxDistance].push(newEdge);
                        qSizes++;
                    }
                    else if (curV.parentV != newV.parentV) {
                        answer = std::min(answer, distances[curV.curV] + distances[newV.curV] + newV.weight);
                    }
                }
            }

            return answer;
        }
};

int32_t main() {
    uint16_t vAmount = 0, eAmount = 0;
    std::cin >> vAmount >> eAmount;

    BFS bfs(vAmount, eAmount);
    for (uint16_t curEdge = 0; curEdge < eAmount; curEdge++) {
        uint16_t v1 = 0, v2 = 0, w = 0;
        std::cin >> v1 >> v2 >> w;
        
        v1--;
        v2--;

        bfs.graph[v1].push_back({curEdge, v2, w});
        bfs.graph[v2].push_back({curEdge, v1, w});
    }

    uint32_t answer = UINT32_MAX;
    for (uint16_t curV = 0; curV < vAmount; curV++) {
        bfs.Clear();

        answer = std::min(answer, bfs(curV));
    }

    std::cout << answer << std::endl;
}
