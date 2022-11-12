#include <cstdint>
#include <cstdio>

void Solve(int32_t N, const int32_t M, uint32_t* db) {
    if (db[N] != 0) {
        return;
    }

    int8_t leastN = ((N - M) >= 0) ? (N - M) : 0; 
    
    for (; leastN < N; leastN++) {
        if (db[leastN] == 0) {
            Solve(leastN, M, db);
        }

        db[N] += db[leastN];
    }
}

int main() {
    int32_t N = 0, M = 0;
    scanf("%d %d", &N, &M);

    uint32_t* db = new uint32_t[N + 1];
    db[0] = 1;

    Solve(N, M, db);
    printf("%u\n", db[N]);

    delete[] db;
}
