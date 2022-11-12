#include <iostream>
#include <cstdint>

#include <vector>

int main() {
    uint64_t N = 0, K = 0;
    std::cin >> N >> K;

    if ((K == 0) && (N > 1)) {
        std::cout << -1 << std::endl;
        return 0;
    }

    if (K == 1) {
        std::cout << N - 1 << std::endl;
        return 0;
    }

    std::vector <uint32_t>* db = new std::vector <uint32_t>[2]();
    bool curDb = 0;

    uint32_t curFlor = 1;
    uint64_t sum = 1;
    db[curDb].push_back(1);

    for (uint32_t counter = K + 1; sum < N; counter = K + 1) {
        curFlor++;
        sum = 0;

        if (counter) {
            sum++;
            counter--;
        }
        db[!curDb].push_back(1);

        for (uint32_t curIdx = 1; curIdx < (curFlor - 1); curIdx++) {
            db[!curDb].push_back(db[curDb][curIdx - 1] + db[curDb][curIdx]);

            if (counter) {
                sum += db[curDb][curIdx - 1] + db[curDb][curIdx];
                counter--;
            }
        }

        if (counter) {
            sum++;
            counter--;
        }
        db[!curDb].push_back(1);

        db[curDb].clear();
        curDb = !curDb;
    }

    std::cout << curFlor - 1 << std::endl;

    delete[] db;
}