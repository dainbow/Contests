#include <iostream>
#include <cstdint>

int main() {
    uint16_t M = 0, N = 0;
    std::cin >> M >> N;

    if (N > M) {
        std::swap(N, M);
    }

    uint32_t** db = new uint32_t*[2]();
    for (uint32_t curM = 0; curM < 2; curM++) {
        db[curM] = new uint32_t[1 << N]();
    }

    for (int64_t curMask = 0; curMask < (1 << N); curMask++) {
        db[0][curMask] = 1;
    }

    bool curDb = 0;
    for (int64_t curM = 1; curM < M; curM++) {
        for (int64_t curMask = 0; curMask < (1 << N); curMask++) {
            for (int64_t prevMask = 0; prevMask < (1 << N); prevMask++) {
                bool flag = 1;

                for (int64_t curN = 0; (curN < (N - 1)) && flag; curN++) {
                    bool bits[4] = {(prevMask & (1 << curN)) != 0, (prevMask & (1 << (curN + 1))) != 0,
                                     (curMask & (1 << curN)) != 0, (curMask & (1 << (curN + 1))) != 0};

                    if ((bits[0] == bits[1]) && (bits[1] == bits[2]) && (bits[2] == bits[3])) {
                        flag = 0;
                    }
                }

                db[!curDb][curMask] += db[curDb][prevMask] * flag;
            }
        }

        for (int64_t curMask = 0; curMask < (1 << N); curMask++) {
            db[curDb][curMask] = 0;
        }

        curDb = !curDb;
    }

    uint32_t answer = 0;
    for (int64_t curMask = 0; curMask < (1 << N); curMask++) {
        answer += db[curDb][curMask];
    }
    std::cout << answer << std::endl;

    for (uint32_t curM = 0; curM < 2; curM++) {
        delete[] db[curM];
    }
    delete[] db;
}
