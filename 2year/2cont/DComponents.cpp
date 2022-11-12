#include <iostream>
#include <cstdlib>

#include <vector>

const uint64_t White = 0;
const uint64_t Grey = 1;

uint32_t Black = 1;

using ConectedList = std::vector<uint32_t>;

template <class T>
class FastQueue {
    private:
        T* dataBegin;
        T* dataEnd;

        T* begin;
        T* end;
    public:
        explicit FastQueue(uint64_t size) :
            dataBegin(new T[size]()),
            dataEnd(dataBegin + size),
            begin(dataBegin),
            end(dataBegin) 
            {}

        FastQueue(const FastQueue<T>& queue) = delete;
        FastQueue& operator=(const FastQueue<T>& queue) = delete;

        ~FastQueue() {
            delete[] dataBegin;
        }

        void PushBack(const T& elem) {
            *end++ = elem;
        }

        T PopBack() {
            return *(--end);
        }

        T PopFront() {
            return *begin++;
        }

        bool IsEmpty() const {
            return begin == end;
        }
};

const uint32_t MARK = (1ull << 31);

void DFS(const ConectedList* graph, uint32_t* colors, const uint32_t vAmount, const uint32_t eAmount) {
    FastQueue<uint32_t> queue(eAmount);

    for (uint32_t curVertex = 0; curVertex < vAmount; curVertex++) {
        if (colors[curVertex] != White) {
            continue;
        }

        Black++;

        queue.PushBack(curVertex | MARK);
        colors[curVertex] = Grey;

        while(!queue.IsEmpty()) {
            uint32_t v = queue.PopBack();

            if (v & MARK) {
                v &= ~MARK;
                queue.PushBack(v);

                for (auto u : graph[v]) {
                    if (colors[u] == White) {
                        colors[u] = Grey;

                        queue.PushBack(u | MARK);
                    }
                }
            }
            else {
                colors[v] = Black;
            }
        }
    }
}

int main() {
    uint32_t vAmount = 0, eAmount = 0;

    std::cin >> vAmount >> eAmount;
    ConectedList* graph = new ConectedList[vAmount]();

    for (uint32_t edgeNumber = 0; edgeNumber < eAmount; edgeNumber++) {
        uint32_t v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;

        graph[v1 - 1].push_back(v2 - 1);
        graph[v2 - 1].push_back(v1 - 1);
    }

    uint32_t* colors  = new uint32_t[vAmount]();
    DFS(graph, colors, vAmount, eAmount);
       
    std::cout << Black - 1 << std::endl;
    for (uint32_t curVertex = 0; curVertex < vAmount; curVertex++) {
        std::cout << colors[curVertex] - 1 << " ";
    }
    std::cout << std::endl;

    delete[] colors;

    delete[] graph;
}
