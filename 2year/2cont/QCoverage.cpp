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

        T verAmount;

        Kuhn(const T vAmount) :
            pairs(new T[vAmount]()),
            graph(new std::vector<T>[vAmount]()),
            colors(new bool[vAmount]()),
            verAmount(vAmount)
            {
                for (uint32_t curV = 0; curV < vAmount; curV++) {
                    pairs[curV] = UINT32_MAX;
                }
            }

        ~Kuhn() {
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

        void operator()(const T vertex) {
            colors[vertex] = Black;

            for (auto& v : graph[vertex]) {
                if (colors[v] == White) {
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
    uint32_t vAmount = 0, eAmount = 0;

    std::cin >> vAmount >> eAmount;
    Kuhn<uint32_t> kh(2 * vAmount);

    uint32_t v1 = 0, v2 = 0;
    for (uint32_t curE = 0; curE < eAmount; curE++) {
        std::cin >> v1 >> v2;

        kh.graph[v1 - 1].push_back(vAmount + v2 - 1);
    }

    for (uint32_t curV = 0; curV < vAmount; curV++) {
        if (kh.colors[curV] == White) {
            kh(curV);
        }
    }

    for (uint32_t curV = 0; curV < vAmount; curV++) {
        if (kh.pairs[curV] == UINT32_MAX) {
            kh.ClearColors();
            kh.DoKuhn(curV);
        }
    }

    uint32_t isolatedAmount = 0;
    for (uint32_t curV = 0; curV < (2 * vAmount); curV++) {
        if (kh.pairs[curV] == UINT32_MAX) {
            isolatedAmount++;
        }
    }

    std::cout << (isolatedAmount / 2) << std::endl;
}
