#include <cstdio>
#include <cstdint>
#include <cmath>

void Solve(uint64_t sum, long double** db, uint64_t tries) {
    for (uint64_t curTry = 1; curTry < tries; curTry++) {
        for (uint64_t curSum = curTry; curSum <= (6 * curTry); curSum++) {
            db[curTry][curSum] /= 6;

            for (uint64_t curAdd = 1; (curAdd <= 6) && ((curSum + curAdd) <= (6 * (curTry + 1))); curAdd++) {
                db[curTry + 1][curSum + curAdd] += db[curTry][curSum];
            }
        }
    }
}

int main() {
    uint64_t N = 0, M = 0;
    scanf("%lu %lu", &N, &M);

    if ((M <= (6 * N)) && (M >= N)) {
        long double** db = new long double*[N + 1]();
        for (uint64_t curAmount = 1; curAmount <= N; curAmount++) {
            db[curAmount] = new long double[6 * curAmount + 1]();
        }

        for (uint64_t curSum = 1; curSum <= 6; curSum++) {
            db[1][curSum] = static_cast<long double>(1);
        }
        
        Solve(M, db, N);

        printf("%.18Lf\n", db[N][M] / static_cast<long double>(6));

        for (uint64_t curAmount = 1; curAmount <= N; curAmount++) {
            delete[] db[curAmount];
        }
        delete[] db;
    }
    else {
        printf("%.10Lf\n", static_cast<long double>(0));
    }
}