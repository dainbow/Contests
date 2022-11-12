#include <iostream>
#include <cstdlib>

#include <vector>

const uint8_t White = 0;
const uint8_t Grey  = 1;
const uint8_t Black = 2;

template <typename T>
class DFS {
    public:
        std::vector<T>* graph;
        uint8_t* colors;
        T* pi;

        std::pair<T, T> answer;

        DFS(const T vAmount) :
            graph(new std::vector<T>[vAmount]),
            colors(new uint8_t[vAmount]),
            pi(new T[vAmount]),
            answer(UINT32_MAX, UINT32_MAX) 
            {}

        ~DFS() {
            delete[] pi;
            delete[] colors;
            delete[] graph;
        }

        DFS(const DFS& dfs) = delete;
        DFS& operator=(const DFS& dfs) = delete;

        void operator()(const T vertex) {
            if ((answer.first != UINT32_MAX) && (answer.second != UINT32_MAX)) {
                return;
            }
            
            colors[vertex] = Grey;
            
            for (auto v : graph[vertex]) {
                if (colors[v] == White) {
                    this->operator()(v);

                    pi[v] = vertex;
                }
                else if (colors[v] == Grey) {
                    answer = {v, vertex};

                    break;
                }
            }

            colors[vertex] = Black;
        }
};

int32_t main() {
    uint32_t vAmount = 0, eAmount = 0;

    std::cin >> vAmount >> eAmount;
    DFS<uint32_t> dfs(vAmount);
    
    for (uint32_t edgeNumber = 0; edgeNumber < eAmount; edgeNumber++) {
        uint32_t v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;

        dfs.graph[v1 - 1].push_back(v2 - 1);
    }

    for (uint32_t v = 0; v < vAmount; v++) {
        if (dfs.colors[v] == White) {
            dfs(v);
        }
    }

    if ((dfs.answer.first == UINT32_MAX) && (dfs.answer.second == UINT32_MAX)) {
        std::cout << "NO" << std::endl;
    }
    else {
        std::cout << "YES" << std::endl;

        std::vector<uint32_t> results(0);
        for (uint32_t curVertex = dfs.answer.second; curVertex != dfs.answer.first; curVertex = dfs.pi[curVertex]) {
            results.push_back(curVertex + 1);
        }
        results.push_back(dfs.answer.first + 1);

        // for(auto it = results.rbegin(); it != it.rend(); it++){
        //     std::cout << *it;
        // }

        for (int64_t curElem = (results.size() - 1); curElem >= 0; curElem--) {
            std::cout << results[curElem] << " ";
        }
        std::cout << std::endl;
    }
}
