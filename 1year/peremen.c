#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int32_t evenSum;
    int32_t oddSum;
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

void BuildDO(Elem* arr, const uint64_t size, const uint64_t index) {
    if (index >= size) {
        return;
    }

    BuildDO(arr, size, 2 * index);
    BuildDO(arr, size, 2 * index + 1);

    arr[index].evenSum = arr[2 * index].evenSum + arr[2 * index + 1].evenSum;
    arr[index].oddSum  = arr[2 * index].oddSum  + arr[2 * index + 1].oddSum;

    return;
}

void ChangeValue(Elem* arr, uint64_t size, uint64_t index, int32_t newValue) {
    index += size;
    
    if ((index % 2) == 0) {
        arr[index].evenSum = newValue;
        arr[index].oddSum  = 0;
    }
    else {
        arr[index].oddSum  = newValue;
        arr[index].evenSum = 0;
    }

    index >>= 1;

    while (index) {
        arr[index].evenSum = arr[2 * index].evenSum + arr[2 * index + 1].evenSum;
        arr[index].oddSum  = arr[2 * index].oddSum  + arr[2 * index + 1].oddSum;

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

        retElem->oddSum  = leftRecurs->oddSum  + rightRecurs->oddSum;
        retElem->evenSum = leftRecurs->evenSum + rightRecurs->evenSum; 
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
    scanf("%u", &arrSize);

    uint64_t roundedArrSize = RoundSize(arrSize);

    Elem* arr = calloc(2 * roundedArrSize, sizeof(Elem));

    for (uint32_t curElem = 0; curElem < arrSize; curElem++) {
        int32_t tempValue = 0;

        scanf("%d", &tempValue);

        if (curElem % 2) {
            arr[roundedArrSize + curElem].oddSum = tempValue;
        }
        else {
            arr[roundedArrSize + curElem].evenSum = tempValue;
        }
    }

    BuildDO(arr, roundedArrSize, 1);
    
    uint32_t rqstAmount = 0;
    scanf("%u", &rqstAmount);

    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        int32_t curCmd = 0;
        scanf("%d", &curCmd);

        switch (curCmd) {
            case 0: {
                uint64_t index   = 0;
                int32_t newValue = 0;

                scanf("%lu %d", &index, &newValue);

                index--;
                ChangeValue(arr, roundedArrSize, index, newValue);
            }
            break;

            case 1: {
                uint64_t left  = 0;
                uint64_t right = 0;

                scanf("%lu %lu", &left, &right);

                left--;
                right--;

                Elem* answer = GetElem(arr, 1, left, right, 0, roundedArrSize - 1);

                int32_t res = 0;
                if (left % 2) {
                    res = answer->oddSum - answer->evenSum;
                }
                else {
                    res = answer->evenSum - answer->oddSum;
                }

                printf("%d\n", res);

                if ((answer < arr) || (answer > (arr + 2 * roundedArrSize - 1))) {
                    free(answer);
                }
            }
            break;
        }
    }

    free(arr);
}