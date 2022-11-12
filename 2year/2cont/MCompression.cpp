#include <iostream>
#include <cstdint>
#include <cassert>

#include <sstream>

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

class CompressionDfs {
    public:
        bool* inV;
        bool* outV;

        int64_t* inspectedNeiborgh;
        bool* endOfNeiborghs;

        int64_t* colors;
        int64_t* visited;

        std::vector<int64_t>* graph;

        std::vector<int64_t> drainNumbers;
        std::vector<int64_t> sourceNumbers;

        int64_t verAmount;
        int64_t cAmount;

        CompressionDfs(const CompressionDfs& cdfs) = delete;
        CompressionDfs& operator=(const CompressionDfs& cdfs) = delete;

        CompressionDfs(int64_t vAmount, int64_t condAmount, std::vector<int64_t>* curGraph, int64_t* curColor) :
        inV(new bool[condAmount]()), outV(new bool[condAmount]()),
        inspectedNeiborgh(new int64_t[vAmount]()),
        endOfNeiborghs(new bool[vAmount]()),
        colors(curColor),
        visited(new int64_t[vAmount]()),
        graph(curGraph),
        drainNumbers(), sourceNumbers(),
        verAmount(vAmount), cAmount(condAmount)
        {
            for (int64_t curV = 0; curV < vAmount; curV++) {
                for (auto& nextV : graph[curV]) {
                    if (colors[curV] != colors[nextV]) {
                        outV[colors[curV]] = 1;
                        inV[colors[nextV]] = 1;
                    }
                }
            }
        }

        ~CompressionDfs() {
            delete[] visited;
            delete[] endOfNeiborghs;
            delete[] inspectedNeiborgh;
            delete[] outV;
            delete[] inV;
        }

        int64_t CalculateAnswer() {
            int64_t isolatedAmount = 0;
            int64_t sourceAmount   = 0;
            int64_t drainAmount    = 0;

            for (int64_t curColor = 0; curColor < cAmount; curColor++) {
                if (outV[curColor] ^ inV[curColor]) {
                    if (outV[curColor]) {
                        sourceAmount++;
                    }
                    else {
                        drainAmount++;
                    }
                }  
                else if (!outV[curColor]) {
                    isolatedAmount++;
                }
            }

            return std::max(isolatedAmount + sourceAmount, isolatedAmount + drainAmount);
        }

        void FillNewEdges() {
            int64_t curColor = 0;
            
            for (int64_t curV = 0; curV < verAmount; curV++) {
                if ((inV[colors[curV]] == 0) && !endOfNeiborghs[curV] && FindDrain(curV, ++curColor)) {
                    sourceNumbers.push_back(curV);
                    inV[colors[curV]] = 1;
                }
            }
        }

        bool FindDrain(int64_t curV, int64_t curColor) {
            if (endOfNeiborghs[curV] || visited[curV])
                return 0;

            visited[curV] = curColor;
            if (outV[colors[curV]] == 0) {
                drainNumbers.push_back(curV);
                outV[colors[curV]] = 1;

                return 1;
            }

            for (; inspectedNeiborgh[curV] < int64_t(graph[curV].size()); inspectedNeiborgh[curV]++) {
                if (FindDrain(graph[curV][inspectedNeiborgh[curV]], curColor)) {
                    break;
                }
            }

            if (inspectedNeiborgh[curV] == int64_t(graph[curV].size())) {
                endOfNeiborghs[curV] = 1;
            }

            return !endOfNeiborghs[curV];
        }
};

int32_t main() {
    int64_t vAmount = 0;
    std::cin >> vAmount;

    DFS<int64_t> dfs(vAmount);
    DFS<int64_t> tDFS(vAmount);

    int64_t v1 = 0, v2 = 0;
    while (std::cin >> v1 >> v2) {
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

    if (blackColor == 1) {
        std::cout << "0" << std::endl;
        return 0;
    }

    CompressionDfs cDFS(vAmount, blackColor, dfs.graph, tDFS.colors);
    std::cout << cDFS.CalculateAnswer() << std::endl;

    cDFS.FillNewEdges();

    for (int64_t curV = 0; curV < int64_t(cDFS.sourceNumbers.size()); curV++) {
        std::cout << cDFS.drainNumbers[curV] + 1 << " " << cDFS.sourceNumbers[(curV + 1) % cDFS.sourceNumbers.size()] + 1 << std::endl;
    }

    std::vector<int64_t> remainSources(0);
    std::vector<int64_t> remainDrains(0);

    for (int64_t curV = 0; curV < vAmount; curV++) {
        if (cDFS.inV[cDFS.colors[curV]] == 0) {
            remainSources.push_back(curV);

            cDFS.inV[cDFS.colors[curV]] = 1;
        }

        if (cDFS.outV[cDFS.colors[curV]] == 0) {
            remainDrains.push_back(curV);
            
            cDFS.outV[cDFS.colors[curV]] = 1;
        }
    }

    while(remainDrains.size() && remainSources.size()) {
        std::cout << remainDrains.back() + 1 << " " << remainSources.back() + 1 << std::endl;
        
        remainSources.pop_back();
        remainDrains.pop_back();
    }

    while (remainSources.size()) {
        std::cout << cDFS.drainNumbers.back() + 1 << " " << remainSources.back() + 1 << std::endl;

        remainSources.pop_back();
    }

    while (remainDrains.size()) {
        std::cout << remainDrains.back() + 1 << " " << cDFS.sourceNumbers.back() + 1 << std::endl;

        remainDrains.pop_back();
    }
}
