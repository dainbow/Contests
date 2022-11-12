#include <iostream>
#include <cstdint>
#include <cassert>

#include <vector>
#include <set>

const bool White = 0;
const bool Black = 1;

template <typename T>
class Kuhn {
    public:
        T* pairs;
        std::vector<T>* graph;

        bool* colors;
        bool* isExist;

        T verAmount;

        Kuhn(const T vAmount) :
            pairs(new T[vAmount]()),
            graph(new std::vector<T>[vAmount]()),
            colors(new bool[vAmount]()),
            isExist(new bool[vAmount]()),
            verAmount(vAmount)
            {
                for (uint32_t curV = 0; curV < vAmount; curV++) {
                    pairs[curV] = UINT32_MAX;
                }
            }

        ~Kuhn() {
            delete[] isExist;
            delete[] colors;
            delete[] graph;
            delete[] pairs;
        }

        Kuhn(const Kuhn& dfs) = delete;
        Kuhn& operator=(const Kuhn& dfs) = delete;

        void ClearColors() {
            for (T curV = 0; curV < verAmount; curV++) {
                colors[curV] = White;
            }
        }

        void Check(const T oldCords, const T newCords) {
            if (isExist[newCords]) {
                graph[oldCords].push_back(newCords);
                graph[newCords].push_back(oldCords);
            }
        }

        void operator()(const T vertex) {
            colors[vertex] = Black;

            for (auto& v : graph[vertex]) {
                if (isExist[v] && (colors[v] == White)) {
                    if (pairs[vertex] == UINT32_MAX) {
                        pairs[vertex] = v;
                        pairs[v]      = vertex;
                    }

                    this->operator()(v);
                }
            }
        }

        bool DoKuhn(const T vertex) {
            if (colors[vertex] == Black) {
                return 0;
            }

            colors[vertex] = Black;
            for (auto v : graph[vertex]) {
                if ((pairs[v] == UINT32_MAX) || DoKuhn(pairs[v])) {
                    pairs[v] = vertex;
                    pairs[vertex] = v;

                    return 1;
                }
            }

            return 0;
        }
};

int main() {
    uint32_t x = 0, y = 0;
    int64_t aCoef = 0, bCoef = 0;

    std::cin >> y >> x >> aCoef >> bCoef;
    Kuhn<uint32_t> kh(x * y);

    uint8_t curChar = 0;
    uint32_t existAmount = 0;
    for (uint32_t curY = 0; curY < y; curY++) {
        for (uint32_t curX = 0; curX < x; curX++) {
            std::cin >> curChar;
            
            if (curChar == '*') {
                existAmount++;
                uint32_t curCords = curY * x + curX;
                kh.isExist[curCords] = 1;

                uint32_t newCords = 0;
                if (curY > 0) {
                    newCords = (curY - 1) * x + curX;

                    kh.Check(curCords, newCords);
                }

                if (curX > 0) {
                    newCords = curY * x + (curX - 1);

                    kh.Check(curCords, newCords);
                }
            }
        }
    }

    for (uint32_t curV = 0; curV < (x * y); curV++) {
        if (kh.isExist[curV] && (kh.colors[curV] == White)) {
            kh(curV);
        }
    }

    for (uint32_t curV = 0; curV < (x * y); curV++) {
        if (kh.isExist[curV] && (kh.pairs[curV] == UINT32_MAX)) {
            kh.ClearColors();
            kh.DoKuhn(curV);
        }
    }

    uint32_t isolatedAmount = 0;
    for (uint32_t curV = 0; curV < (x * y); curV++) {
        if (kh.isExist[curV] && (kh.pairs[curV] == UINT32_MAX)) {
            isolatedAmount++;
        }
    }

    std::cout << std::min(bCoef * int64_t(existAmount), bCoef * int64_t(isolatedAmount) + aCoef * int64_t((existAmount - isolatedAmount) / 2)) << std::endl;
}
