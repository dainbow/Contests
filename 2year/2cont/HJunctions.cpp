#include <iostream>
#include <cstdlib>

#include <vector>
#include <algorithm>
#include <set>
#include <map>

const uint8_t White = 0;
const uint8_t Grey  = 1;
const uint8_t Black = 2;

template <typename T>
class DFS {
    public:
        uint32_t* timeIn;
        uint32_t* ret;
        uint32_t time;

        std::map<uint32_t, uint32_t>* graph;

        uint8_t* colors;

        T* pi;

        std::vector<std::pair<uint32_t, uint32_t>> answer;

        DFS(const T vAmount) :
            timeIn(new uint32_t[vAmount]()),
            ret(new uint32_t[vAmount]()),
            time(0),
            graph(new std::map<uint32_t, uint32_t>[vAmount]),
            colors(new uint8_t[vAmount]()),
            pi(new T[vAmount]()),
            answer()
            {
                for (uint32_t curVertex = 0; curVertex < vAmount; curVertex++) {
                    ret[curVertex] = UINT32_MAX;
                }
            }

        ~DFS() {
            delete[] pi;
            delete[] colors;
            delete[] graph;
            delete[] ret;
            delete[] timeIn;
        }

        DFS(const DFS& dfs) = delete;
        DFS& operator=(const DFS& dfs) = delete;

        void operator()(const T vertex, const T rootVertex) {
            colors[vertex] = Grey;
            timeIn[vertex] = (time++);
            uint32_t childrenAmount = 0;
           
            for (auto& v : graph[vertex]) {
                if (v.first == rootVertex)
                    continue;

                if (colors[v.first] == White) {
                    this->operator()(v.first, vertex);

                    childrenAmount++;
                    ret[vertex] = std::min(ret[vertex], ret[v.first]);
                    if (ret[v.first] > timeIn[vertex]) {
                        answer.push_back({vertex, v.first});
                    }

                    pi[v.first] = vertex;
                }
                else {
                    ret[vertex] = std::min(ret[vertex], timeIn[v.first]);
                }
            }
        }
            
        
};

int32_t main() {
    uint32_t vAmount = 0, eAmount = 0;

    std::cin >> vAmount;
    std::cin >> eAmount;

    DFS<uint32_t> dfs(vAmount);

    for (uint32_t curEdge = 0; curEdge < eAmount; curEdge++) {
        uint32_t v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;

        dfs.graph[v1 - 1].insert({v2 - 1, curEdge + 1});
        dfs.graph[v2 - 1].insert({v1 - 1, curEdge + 1});
    }

    for (uint32_t curVertex = 0; curVertex < vAmount; curVertex++) {
        if (dfs.colors[curVertex] == White) {
            dfs(curVertex, UINT32_MAX);
        }
    }
    
    std::set<uint32_t> answer;
    for (auto it = dfs.answer.begin(); it != dfs.answer.end(); it++) {
        answer.insert(dfs.graph[it->first][it->second]);
    }

    std::cout << answer.size() << std::endl;

    for (auto it = answer.begin(); it != answer.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
