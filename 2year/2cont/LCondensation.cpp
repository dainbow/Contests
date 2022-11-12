#include <iostream>
#include <cstdint>
#include <cassert>

#include <vector>
#include <set>

const int64_t White = -1;

template <typename T>
class DFS {
    public:
        std::vector<int64_t> timeOut;
        std::vector<T>* graph;

        int64_t* colors;

        DFS(const T vAmount) :
            timeOut(),
            graph(new std::vector<T>[vAmount]()),
            colors(new int64_t[vAmount]())
            {
                for (int64_t curV = 0; curV < vAmount; curV++) {
                    colors[curV] = White;
                }
            }

        ~DFS() {
            delete[] colors;
            delete[] graph;
        }

        DFS(const DFS& dfs) = delete;
        DFS& operator=(const DFS& dfs) = delete;

        void operator()(const T vertex, const int64_t color) {
            colors[vertex] = color;
            
            for (auto& v : graph[vertex]) {
                if (colors[v] == White) {
                    this->operator()(v, color);
                }
            }

            timeOut.push_back(vertex);
        }
};

int32_t main() {
    int64_t vAmount = 0, eAmount = 0;
    std::cin >> vAmount >> eAmount;

    DFS<int64_t> dfs(vAmount);
    DFS<int64_t> tDFS(vAmount);

    for (int64_t curEdge = 0; curEdge < eAmount; curEdge++) {
        int64_t v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;

         dfs.graph[v1 - 1].push_back(v2 - 1);
        tDFS.graph[v2 - 1].push_back(v1 - 1);
    }

    int64_t blackColor = 0;
    for (int64_t curVertex = 0; curVertex < vAmount; curVertex++) {
        if (dfs.colors[curVertex] == White) {
            dfs(curVertex, blackColor);
        }
    }
    
    for (int64_t curN = (vAmount - 1); curN >= 0; curN--) {
        int64_t stackVertex = dfs.timeOut[curN];

        if (tDFS.colors[stackVertex] == White) {
            tDFS(stackVertex, blackColor++);
        }
    }

    std::set<std::pair<int64_t, int64_t>> answer;
    for (int64_t curV = 0; curV < vAmount; curV++) {
        for (auto& nextV : dfs.graph[curV]) {
            if (tDFS.colors[curV] != tDFS.colors[nextV]) {
                answer.insert(std::make_pair(tDFS.colors[curV], tDFS.colors[nextV]));
            }
        }
    }

    std::cout << answer.size() << std::endl;
}
