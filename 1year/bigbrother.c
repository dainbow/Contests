#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t maxValue;
} Elem;

uint64_t RoundSize(uint64_t size) {
    for (uint64_t curPower = 0; curPower < 65; curPower++) {
        if ((1 << curPower) >= size) {
            return (1 << curPower); 
        }
    }

    return 3;
}

void BuildDO(Elem* arr, uint64_t size, uint64_t index, int64_t* max) {
    if (index >= size) {
        *max = arr[index].maxValue;

        return;
    }

    int64_t curMax1 = 0;
    BuildDO(arr, size, 2 * index, &curMax1);

    int64_t curMax2 = 0;
    BuildDO(arr, size, 2 * index + 1, &curMax2);

    arr[index].maxValue = (curMax1 > curMax2) ? curMax1 : curMax2;

    *max = arr[index].maxValue;
}

void ChangeValue(Elem* arr, uint64_t size, uint64_t index, int64_t newValue) {
    index += size;
    
    arr[index].maxValue = newValue;

    index >>= 1;

    while (index) {
        arr[index].maxValue = (arr[2 * index].maxValue > arr[2 * index + 1].maxValue) ? arr[2 * index].maxValue : arr[2 * index + 1].maxValue; 

        index >>= 1;
    }
}

int64_t GetElem(Elem* arr, uint64_t size, uint64_t index, uint64_t neededIdx, int64_t elem, uint64_t curLeft, uint64_t curRight) {
    if (index >= size)
        return (1 + index - size);

    uint64_t curMiddle = (curRight + curLeft) / 2;
    int64_t retValue = INT64_MAX;

    if ((arr[2 * index].maxValue >= elem) && (curMiddle >= neededIdx)) {
        int64_t leftRecurs = GetElem(arr, size, 2 * index, neededIdx, elem, curLeft, curMiddle);

        retValue = (retValue < leftRecurs) ?
                    retValue : leftRecurs;
    }

    curMiddle++;
    if ((retValue == INT64_MAX) && (arr[2 * index + 1].maxValue >= elem)) {
        int64_t rightRecurs = GetElem(arr, size, 2 * index + 1, neededIdx, elem, curMiddle, curRight);
        
        retValue = (retValue < rightRecurs) ?
                    retValue : rightRecurs;
    }
    
    return retValue;
}   

int main() {
    uint32_t arrSize    = 0;
    uint32_t rqstAmount = 0;

    scanf("%u %u", &arrSize, &rqstAmount);
    uint64_t roundedArrSize = RoundSize(arrSize);

    Elem* arr = calloc(2 * roundedArrSize, sizeof(Elem));
    for (uint64_t curElem = 0; curElem < arrSize; curElem++) {
        scanf("%ld", &arr[roundedArrSize + curElem].maxValue);
    }

    int64_t trash1 = 0;
    BuildDO(arr, roundedArrSize, 1, &trash1);

    for (uint64_t curReq = 0; curReq < rqstAmount; curReq++) {
        uint32_t opId   = 0;
        uint32_t opIdx  = 0;
        int64_t  opElem = 0;

        scanf("%u %u %ld", &opId, &opIdx, &opElem);

        switch (opId) {
            case 0: {
                ChangeValue(arr, roundedArrSize, opIdx - 1, opElem);
            }
            break;

            case 1: {
                int64_t elemToPrint = GetElem(arr, roundedArrSize, 1, opIdx - 1, opElem, 0, roundedArrSize - 1);
                elemToPrint = (elemToPrint == INT64_MAX) ? -1 : elemToPrint;

                printf("%ld\n", elemToPrint);
            }
            break;
        }
    }

    free(arr);
}
