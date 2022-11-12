#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    int64_t** sums;
    int64_t** numbers;

    int64_t xSize;
    int64_t ySize;
} FTree;

typedef struct {
    int64_t x;
    int64_t y;
} Pair;

FTree* CreateTree(int64_t xSize, int64_t ySize) {
    FTree* curTree = calloc(1, sizeof(FTree));

    curTree->sums    = calloc(ySize, sizeof(int64_t*));
    curTree->numbers = calloc(ySize, sizeof(int64_t*));

    for (int64_t curY = 0; curY < ySize; curY++) {
        curTree->sums[curY] = calloc(xSize, sizeof(int64_t));
        curTree->numbers[curY] = calloc(xSize, sizeof(int64_t));
    }

    curTree->xSize = xSize;
    curTree->ySize = ySize;

    return curTree;
}

FTree* DeleteTree(FTree* curTree) {
    if (curTree == NULL)
        return curTree;

    for (int64_t curY = 0; curY < curTree->ySize; curY++) {
        free(curTree->sums[curY]);
        free(curTree->numbers[curY]);
    } 

    free(curTree->numbers);
    free(curTree->sums);

    curTree->xSize = 0;
    curTree->ySize = 0;

    free(curTree);

    return NULL;
}

static inline int64_t f(int64_t x) {
    return x & (x + 1);
}

static inline int64_t g(int64_t x) {
    return x | (x + 1);
}

void Assign(Pair* curPair, int64_t weight, FTree* tree) {
    int64_t weightDiff = weight - tree->numbers[curPair->y][curPair->x];
    tree->numbers[curPair->y][curPair->x] = weight;
    
    for (int64_t curY = curPair->y; curY < tree->ySize; curY = g(curY)) {
        for (int64_t curX = curPair->x; curX < tree->xSize; curX = g(curX)) {
            tree->sums[curY][curX] += weightDiff;
        }
    }
}

void Increase(Pair* curPair, int64_t diff, FTree* tree) {
    tree->numbers[curPair->y][curPair->x] += diff;

    for (int64_t curY = curPair->y; curY < tree->ySize; curY = g(curY)) {
        for (int64_t curX = curPair->x; curX < tree->xSize; curX = g(curX)) {
            tree->sums[curY][curX] += diff;
        }
    }
}

int64_t GetPrefix(Pair* curPair, FTree* tree) {
    int64_t ret = 0;

    for (int64_t curY = curPair->y; curY >= 0; curY = f(curY) - 1) {
        for (int64_t curX = curPair->x; curX >= 0; curX = f(curX) - 1) {
            ret += tree->sums[curY][curX];
        }
    }

    return ret;
}

int64_t GetSum(Pair* l1r1Pair, Pair* l2r2Pair, FTree* tree) {
    Pair l1r2Pair = {l1r1Pair->x, l2r2Pair->y};
    Pair l2r1Pair = {l2r2Pair->x, l1r1Pair->y};

    return GetPrefix(l1r1Pair, tree)  + GetPrefix(l2r2Pair, tree) 
         - GetPrefix(&l1r2Pair, tree) - GetPrefix(&l2r1Pair, tree);
}

int main() {
    FTree* curTree = CreateTree(1000, 1000);

    for (int64_t curChar = getchar(); curChar != EOF; curChar = getchar()) {
        switch (curChar) {
            case 'A': {
                int64_t diff = 0;
                Pair curPair = {};

                scanf("DD %ld AT %ld %ld", &diff, &curPair.x, &curPair.y);

                Increase(&curPair, diff, curTree);
            }
            break;

            case 'R': {
                Pair curPair = {};

                scanf("EMOVE %ld %ld", &curPair.x, &curPair.y);

                Assign(&curPair, 0, curTree);
            }
            break;

            case 'C': {
                int64_t newWeight = 0;
                Pair curPair      = {};

                scanf("HANGE AT %ld %ld TO %ld", &curPair.x, &curPair.y, &newWeight);

                Assign(&curPair, newWeight, curTree);
            }
            break;

            case 'S': {
                Pair l1r1Pair = {};
                Pair l2r2Pair = {};

                scanf("UM FROM %ld %ld TO %ld %ld", &l1r1Pair.x, &l1r1Pair.y, &l2r2Pair.x, &l2r2Pair.y);
                l1r1Pair.x--;
                l1r1Pair.y--;

                printf("%ld\n", GetSum(&l1r1Pair, &l2r2Pair, curTree));
            }
            break;

            default:
                break;
        }
    }

    curTree = DeleteTree(curTree);
}
