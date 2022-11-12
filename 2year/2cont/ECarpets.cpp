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
    uint32_t x = 0, y = 0;

    std::cin >> x >> y;
    ConectedList* graph = new ConectedList[x * y]();

    bool** info = new bool*[y]();
    for (uint32_t curY = 0; curY < y; curY++) {
        info[curY] = new bool[x]();
    }

    uint32_t eAmount = 0;
    uint32_t badAmount = 0;

    for (uint32_t curY = 0; curY < y; curY++) {
        for (uint32_t curX = 0; curX < x; curX++) {
            char curSym = 0;
            std::cin >> curSym;

            info[curY][curX] = (curSym == '+') ? 1 : 0;

            if (info[curY][curX]) {
                if ((curX > 0) && info[curY][curX - 1]) {
                    graph[curY * y + curX].push_back(curY * y + curX - 1);
                    graph[curY * y + curX - 1].push_back(curY * y + curX);

                    eAmount++;
                }

                if ((curY > 0) && info[curY - 1][curX]) {
                    graph[curY * y + curX].push_back((curY - 1) * y + curX);
                    graph[(curY - 1) * y + curX].push_back(curY * y + curX);

                    eAmount++;
                }
            }
            else {
                badAmount++;
            }
        }
    }
    

    uint32_t* colors  = new uint32_t[x * y]();
    DFS(graph, colors, x * y, eAmount);
       
    std::cout << Black - 1 - badAmount << std::endl;

    delete[] colors;

    delete[] graph;
}
