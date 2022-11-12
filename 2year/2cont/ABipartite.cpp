#include <iostream>
#include <cstdlib>

#include <vector>

enum class Color {
    White = 0,
    Grey,
    Black
};

using Graph = std::vector<std::vector<uint8_t>>;

bool DFS(const uint16_t& vertex, const Graph& graph, uint32_t& time, Color* colors, uint32_t* timeIn, uint32_t* timeOut) {
    colors[vertex] = Color::Grey;
    
    time++;
    timeIn[vertex] = time;

    bool result = 0;
    for (auto& v : graph[vertex]) {
        if (colors[v] == Color::White) {
            result |= DFS(v, graph, time, colors, timeIn, timeOut);
        }
        else if (colors[v] == Color::Grey) {
            if ((timeIn[vertex] - timeIn[v] + 1) % 2) {
                result = 1;
            }
        }
    }

    colors[vertex] = Color::Black;

    time++;
    timeOut[vertex] = time;

    return result;
}

int main() {
    uint16_t vAmount = 0, eAmount = 0;

    std::cin >> vAmount >> eAmount;
    Graph graph(vAmount);

    for (uint16_t edgeNumber = 0; edgeNumber < eAmount; edgeNumber++) {
        uint16_t v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;

        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    Color* colors = new Color[vAmount]();
    uint32_t* timeIn  = new uint32_t[vAmount]();
    uint32_t* timeOut = new uint32_t[vAmount]();

    uint32_t time = 0;

    bool result = 0;
    for (uint16_t v = 0; v < vAmount; v++) {
        if (colors[v] == Color::White) {
            result |= DFS(v, graph, time, colors, timeIn, timeOut);
        }
    }

    if (result) {
        std::cout << "NO" << std::endl;
    }
    else {
        std::cout << "YES" << std::endl;
    }

    delete[] timeOut;
    delete[] timeIn;

    delete[] colors;
}
