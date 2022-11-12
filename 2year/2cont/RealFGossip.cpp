#include <iostream>
#include <cstdlib>
#include <cassert>

#include <list>
#include <vector>
#include <queue>

const uint64_t SHIFT = 6;
const uint64_t MASK  = (1ull << 6) - 1;

class BFS {
    public:
        uint32_t x;
        uint32_t y;

        std::queue<uint32_t> distances;
        uint64_t* colors;

        uint16_t maxDistance;

        BFS(const uint32_t maxX, const uint32_t maxY) :
            x(maxX), y(maxY),
            distances(),
            colors(new uint64_t[((x * y) >> SHIFT) + 1]()),
            maxDistance(0) 
            {}

        ~BFS() {
            delete[] colors;
        }

        BFS (const BFS& bfs) = delete;
        BFS operator=(const BFS& bfs) = delete;

        uint16_t operator()() {
            maxDistance = 0;
            
            while (!distances.empty()) {
                uint32_t curVertex = distances.front();
                distances.pop();
                if (curVertex == UINT32_MAX) {
                    if (!distances.empty()) {
                        maxDistance++;
                        distances.push({UINT32_MAX});
                    }

                    continue;
                }

                uint32_t curX = curVertex % x;
                uint32_t curY = curVertex / x;

                uint32_t newV = 0;
                if (curY > 0) {
                    newV = (curY - 1) * x + curX;

                    if ((colors[newV >> SHIFT] & (1ull << (newV & MASK))) == 0) {
                        colors[newV >> SHIFT] ^= (1ull << (newV & MASK));
                        distances.push({newV});
                    }
                }   

                if (curY < (y - 1)) {
                    newV = (curY + 1) * x + curX;
                    
                    if ((colors[newV >> SHIFT] & (1ull << (newV & MASK))) == 0) {
                        colors[newV >> SHIFT] ^= (1ull << (newV & MASK));
                        distances.push({newV});
                    }
                }

                if (curX > 0) {
                    newV = curY * x + (curX - 1);

                    if ((colors[newV >> SHIFT] & (1ull << (newV & MASK))) == 0) {
                        colors[newV >> SHIFT] ^= (1ull << (newV & MASK));
                        distances.push({newV});
                    }
                }

                if (curX < (x - 1)) {
                    newV = curY * x + (curX + 1);
                   
                    if ((colors[newV >> SHIFT] & (1ull << (newV & MASK))) == 0) {
                        colors[newV >> SHIFT] ^= (1ull << (newV & MASK));
                        distances.push({newV});
                    }
                }
            }

            return maxDistance;
        }
};  

int32_t main() {
    uint32_t x = 0, y = 0;
    uint32_t startAmount = 0;

    std::cin >> x >> y >> startAmount;
    BFS bfs(x, y);
    
    uint32_t curX = 0, curY = 0;
    for (uint32_t curStart = 0; curStart < startAmount; curStart++) {
        std::cin >> curX >> curY;
        
        bfs.distances.push(curY * x + curX);
        bfs.colors[(curY * x + curX) >> SHIFT] ^= (1ull << ((curY * x + curX) & MASK));
    }
    bfs.distances.push(UINT32_MAX);

    std::cout << bfs() << std::endl;
}
