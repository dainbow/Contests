#include <iostream>
#include <cstdlib>

#include <vector>
#include <set>

enum class Color {
    White = 0,
    Grey,
    Black
};

using Graph = std::vector<std::set<int32_t>>;

template <class T>
class FastQueue {
    private:
        T* dataBegin;
        T* dataEnd;

        T* begin;
        T* end;
    public:
        explicit FastQueue(uint64_t size) {
            dataBegin = new T[size]();
            
            begin = dataBegin;
            end   = dataBegin;

            dataEnd = dataBegin + size;
        }
        ~FastQueue() {
            delete[] dataBegin;
        }

        void Enqueue(const T& elem) {
            *end++ = elem;
        }

        T Dequeue() {
            return *begin++;
        }

        bool IsEmpty() const {
            return begin == end;
        }
};

void BFS(const Graph& graph, const uint16_t vertex, uint16_t* distances, Color* colors, uint16_t* pi) {
    distances[vertex] = 0;
    pi[vertex] = vertex;

    FastQueue<uint16_t> queue(2 * graph.size());
    queue.Enqueue(vertex);

    while (!queue.IsEmpty()) {
        uint16_t curVertex = queue.Dequeue();

        for (auto& v: graph[curVertex]) {
            if (colors[v] == Color::White) {
                queue.Enqueue(v);
                
                distances[v] = distances[curVertex] + 1;
                pi[v] = curVertex;
                colors[v] = Color::Grey;
            }
        }

        colors[curVertex] = Color::Black;
    }
}

int main() {
    int32_t fieldSize = 0;
    std::cin >> fieldSize;

    char row = 0;
    int32_t column = 0;

    std::cin >> row >> column;
    uint16_t startVertex = (row - 'A') * fieldSize + (column - 1);

    std::cin >> row >> column;
    uint16_t endVertex = (row - 'A') * fieldSize + (column - 1);

    Graph graph(fieldSize * fieldSize);
    for (int32_t curY = 0; curY < fieldSize; curY++) {
        for (int32_t curX = 0; curX < fieldSize; curX++) {
            if ((curX + 2) < fieldSize) {
                if ((curY + 1) < fieldSize) {
                    graph[curY * fieldSize + curX].insert((curY + 1) * fieldSize + curX + 2);
                    graph[(curY + 1) * fieldSize + curX + 2].insert(curY * fieldSize + curX);
                }

                if ((curY - 1) >= 0) {
                    graph[curY * fieldSize + curX].insert((curY - 1) * fieldSize + curX + 2);
                    graph[(curY - 1) * fieldSize + curX + 2].insert(curY * fieldSize + curX);
                }
            }

            if ((curY + 2) < fieldSize) {
                if ((curX + 1) < fieldSize) {
                    graph[curY * fieldSize + curX].insert((curY + 2) * fieldSize + curX + 1);
                    graph[(curY + 2) * fieldSize + curX + 1].insert(curY * fieldSize + curX);
                }

                if ((curX - 1) >= 0) {
                    graph[curY * fieldSize + curX].insert((curY + 2) * fieldSize + curX - 1);
                    graph[(curY + 2) * fieldSize + curX -1].insert(curY * fieldSize + curX);
                }
            }
        }
    }

    uint16_t* distances = new uint16_t[fieldSize * fieldSize]();
    Color* colors = new Color[fieldSize * fieldSize]();
    uint16_t* pi  = new uint16_t[fieldSize * fieldSize]();

    BFS(graph, startVertex, distances, colors, pi);
    
    uint16_t* answer = new uint16_t[distances[endVertex]];
    int32_t curAnswer = distances[endVertex] - 1;

    for (uint16_t curV = endVertex; curAnswer >= 0; curV = pi[curV]) {
        answer[curAnswer--] = curV;
    }
    
    std::cout << distances[endVertex] << std::endl;
    for (uint16_t curV = 0; curV < distances[endVertex]; curV++) {
        std::cout << (char)('A' + (answer[curV] / fieldSize)) << answer[curV] % fieldSize + 1 << std::endl;
    }
    std::cout << std::endl;


    delete[] answer;
    delete[] pi;
    delete[] colors;
    delete[] distances;
}

