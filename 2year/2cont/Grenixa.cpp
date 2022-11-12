#include <iostream>
#include <cstdlib>

#include <vector>
#include <algorithm>

const uint8_t White = 0;
const uint8_t Grey  = 1;
const uint8_t Black = 2;

template <typename T>
class DFS {
    public:
        uint32_t* timeIn;
        uint32_t* timeOut;
        uint32_t time;

        std::vector<T>* graph;

        uint8_t* ёcolors;

        T* pi;

        DFS(const T vAmount) :
            timeIn(new uint32_t[vAmount]()),
            timeOut(new uint32_t[vAmount]()),
            time(0),
            graph(new std::vector<T>[vAmount]()),
            colors(new uint8_t[vAmount]()),
            pi(new T[vAmount]())
            {}

        ~DFS() {
            delete[] pi;
            delete[] colors;
            delete[] graph;
            delete[] timeOut;
            delete[] timeIn;
        }

        DFS(const DFS& dfs) = delete;
        DFS& operator=(const DFS& dfs) = delete;

        void operator()(const T vertex) {
            colors[vertex] = Grey;
            timeIn[vertex] = (time++);
            
            for (auto v : graph[vertex]) {
                if (colors[v] == White) {
                    this->operator()(v);

                    pi[v] = vertex;
                }
            }

            colors[vertex] = Black;
            timeOut[vertex] = (time++);
        }
};

int32_t main() {
    uint8_t vSize = 0, wAmount = 0;

    std::cin >> (uint16_t&)vSize;
    std::cin >> (uint16_t&)wAmount;

    DFS<uint8_t> dfs(vSize);

    std::string* words = new std::string[wAmount]();

    std::cin >> words[0];
    for (uint32_t wordNumber = 1; wordNumber < wAmount; wordNumber++) {
        std::cin >> words[wordNumber];

        for (uint32_t curChar = 0; curChar < std::min(words[wordNumber - 1].size(), words[wordNumber].size()); curChar++) {
            if (words[wordNumber - 1][curChar] != words[wordNumber][curChar]) {
                dfs.graph[words[wordNumber - 1][curChar] - 'A'].push_back(uint8_t(words[wordNumber][curChar] - 'A'));

                break;
            }
        }
    }

    for (uint8_t v = 0; v < vSize; v++) {
        if (dfs.colors[v] == White) {
            dfs(v);
        }
    }

    uint32_t* copyTime = new uint32_t[vSize]();
    std::copy(dfs.timeOut, dfs.timeOut + vSize, copyTime);
    std::sort(copyTime, copyTime + vSize);

    for (uint8_t curV = 0; curV < vSize; curV++) {
        for (uint8_t curAnotherV = 0; curAnotherV < vSize; curAnotherV++) {
            if (dfs.timeOut[curAnotherV] == copyTime[vSize - 1 - curV]) {
                std::cout << (char)('A' + curAnotherV);
            }
        }
    }
    std::cout << std::endl;

    delete[] copyTime;
    delete[] words;
}
