#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int32_t answer;
    int32_t sum;
    
    int32_t maxPre;
    int32_t maxPost;
} Elem;

int32_t MAX(int32_t a, int32_t b) {
    return (a > b) ? a : b;
}

uint64_t RoundSize(uint64_t size) {
    for (uint64_t curPower = 0; curPower < 65; curPower++) {
        if (((uint64_t)1 << curPower) >= size) {
            return (1 << curPower); 
        }
    }

    return 3;
}

int32_t UpdateAnswer(Elem* elem1, Elem* elem2, Elem* result) {
    if (result) {
        result->sum = elem1->sum + elem2->sum;

        result->maxPre  = MAX(elem1->maxPre,  elem1->sum     + elem2->maxPre);
        result->maxPost = MAX(elem2->maxPost, elem1->maxPost + elem2->sum);
    }

    return MAX(MAX(elem1->answer, elem2->answer), elem1->maxPost + elem2->maxPre);
}

Elem* BuildDO(Elem* arr, const uint64_t size, const uint64_t index) {
    if (index >= size) {
        return arr + index;
    }

    BuildDO(arr, size, 2 * index);
    BuildDO(arr, size, 2 * index + 1);

    arr[index].answer  = UpdateAnswer(arr + 2 * index, arr + 2 * index + 1, arr + index);

    return arr + index;
}

void ChangeValue(Elem* arr, uint64_t size, uint64_t index, int32_t newValue) {
    index += size;
    
    arr[index].sum     = newValue;
    arr[index].maxPost = newValue;
    arr[index].maxPre  = newValue;
    arr[index].answer  = newValue;

    index >>= 1;

    while (index) {
        arr[index].answer  = UpdateAnswer(arr + 2 * index, arr + 2 * index + 1, arr + index);

        index >>= 1;
    }
}

Elem* GetElem(Elem* arr, uint64_t index, uint64_t left, uint64_t right, uint64_t curLeft, uint64_t curRight) {
    if ((left <= curLeft) && (right >= curRight)) {
        return arr + index;
    }

    uint64_t curMiddle = (curLeft + curRight) / 2;

    Elem* leftRecurs  = NULL;
    Elem* rightRecurs = NULL;

    if (left <= curMiddle) {
        leftRecurs = GetElem(arr, 2 * index, left, (curMiddle < right) ? curMiddle : right, curLeft, curMiddle);
    }

    curMiddle++;

    if (right >= curMiddle) {
        rightRecurs = GetElem(arr, 2 * index + 1, MAX(left, curMiddle), right, curMiddle, curRight);
    }

    Elem* retElem = NULL;

    if (leftRecurs && rightRecurs) {
        retElem = calloc(1, sizeof(Elem));

        retElem->answer = UpdateAnswer(leftRecurs, rightRecurs, retElem);
    }
    else {
        if (leftRecurs) {
            retElem = leftRecurs;
        }
        else {
            retElem = rightRecurs;
        }
    }

    return retElem;
}   

int main() {
    uint32_t arrSize    = 0;
    uint32_t rqstAmount = 0;
    scanf("%u %u", &arrSize, &rqstAmount);

    uint64_t roundedArrSize = RoundSize(arrSize);

    Elem* arr = calloc(2 * roundedArrSize, sizeof(Elem));

    for (uint32_t curElem = 0; curElem < arrSize; curElem++) {
        scanf("%d", &arr[roundedArrSize + curElem].sum);

        arr[roundedArrSize + curElem].answer  = arr[roundedArrSize + curElem].sum;
        arr[roundedArrSize + curElem].maxPost = arr[roundedArrSize + curElem].sum;
        arr[roundedArrSize + curElem].maxPre  = arr[roundedArrSize + curElem].sum;
    }

    BuildDO(arr, roundedArrSize, 1);

    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        int32_t curCmd = 0;
        scanf("%d", &curCmd);

        switch (curCmd) {
            case 1: {
                uint64_t index   = 0;
                int32_t newValue = 0;

                scanf("%lu %d", &index, &newValue);
                ChangeValue(arr, roundedArrSize, index, newValue);
            }
            break;

            case 2: {
                uint64_t left  = 0;
                uint64_t right = 0;

                scanf("%lu %lu", &left, &right);

                Elem* answer = GetElem(arr, 1, left, right, 0, roundedArrSize - 1);

                printf("%d\n", answer->answer);

                if ((answer < arr) || (answer > (arr + 2 * roundedArrSize - 1))) {
                    free(answer);
                }
            }
            break;
        }
    }

    free(arr);
}