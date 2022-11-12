#include <cstdio>
#include <cstdint>
#include <algorithm>

struct MyCashe {
    uint32_t papersAmount;
    uint32_t lastIdx;
};

void Solve(uint32_t sum, MyCashe* db, const uint32_t amount, const uint32_t* papers) {
    if (db[sum].papersAmount != 0) {
        return;
    }

    MyCashe min    = {UINT32_MAX, 0};
    for (uint32_t curPaper = 0; curPaper < amount; curPaper++) {
        if (sum <= papers[curPaper]) {
            continue;
        }

        uint32_t newSum = sum - papers[curPaper];
        if (db[newSum].papersAmount == 0) {
            Solve(newSum, db, amount, papers);
        }

        if (db[newSum].papersAmount < min.papersAmount) {
            min = {db[newSum].papersAmount + 1, newSum};
        }
    }

    db[sum] = min;
}

int main() {
    uint32_t amount = 0;
    scanf("%u", &amount);

    uint32_t* papers = new uint32_t[amount]();
    for (uint32_t curPaper = 0; curPaper < amount; curPaper++) {
        scanf("%u", papers + curPaper);
    }

    uint32_t sum = 0;
    scanf("%u", &sum);

    MyCashe* db = new MyCashe[sum + 1]();
    for (uint32_t curPaper = 0; curPaper < amount; curPaper++) {
        if (papers[curPaper] > sum) {
            continue;
        }

        db[papers[curPaper]].papersAmount = 1;
        db[papers[curPaper]].lastIdx      = 0;
    }

    Solve(sum, db, amount, papers);

    if (db[sum].papersAmount != UINT32_MAX) {
        printf("%u\n", db[sum].papersAmount);

        while(db[sum].lastIdx) {
            printf("%u ", sum - db[sum].lastIdx);

            sum = db[sum].lastIdx;
        }
        printf("%u\n", sum);
    }
    else {
        printf("-1\n");
    }


    delete[] db;
    delete[] papers;
}