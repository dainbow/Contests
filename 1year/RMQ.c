#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static inline uint32_t CalcLogarithm(const uint32_t elem) {
    return 31 - __builtin_clz(elem);
}

static inline void FillRMQ(int32_t* sparseTable, const uint32_t elemAmount, const uint32_t logOfElem) {
    for (uint32_t curTable = 1; curTable < 1 + logOfElem; curTable++) {
        uint32_t shift        = 1 << (curTable - 1);

        for (uint32_t curElem = 0; curElem < elemAmount - shift; curElem++) {
            sparseTable[curTable * elemAmount + curElem] = 
                (sparseTable[(curTable - 1) * elemAmount + curElem] > sparseTable[(curTable - 1) * elemAmount + curElem + shift]) ?
                 sparseTable[(curTable - 1) * elemAmount + curElem] : sparseTable[(curTable - 1) * elemAmount + curElem + shift];
        }
    }
}

static inline int32_t CalcRMQ(int32_t* sparseTable, const uint32_t elemAmount, const uint32_t left, const uint32_t right) {
    uint32_t curLog = CalcLogarithm(1 + right - left);

    int32_t leftThing  = sparseTable[curLog * elemAmount + left];
    int32_t rightThing = sparseTable[curLog * elemAmount + (1 + right) - (1 << curLog)];

    return (leftThing > rightThing) ? leftThing : rightThing; 
}

int main() {
    uint32_t elemAmount = 0;
    uint32_t rqstAmount = 0;
    scanf("%u %u", &elemAmount, &rqstAmount);

    uint32_t logOfElem    = CalcLogarithm(elemAmount);
    int32_t* sparseTable  = calloc(logOfElem + 1, sizeof(int32_t*));

    sparseTable = calloc(elemAmount * (logOfElem + 1), sizeof(int32_t));
    for (uint32_t curElem = 0; curElem < elemAmount; curElem++) {
        scanf("%d", sparseTable + curElem);
    }
    FillRMQ(sparseTable, elemAmount, logOfElem);

    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        uint32_t left  = 0;
        uint32_t right = 0;
        scanf("%u %u", &left, &right);

        printf("%d\n", CalcRMQ(sparseTable, elemAmount, left, right));
    }

    free(sparseTable);
}
