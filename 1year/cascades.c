#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>

// #pragma GCC optimize("O3")

typedef struct node {
    uint32_t value;

    uint16_t next;
    uint16_t down;
} Node;

typedef struct {
    Node* nodes;

    uint32_t size;
} NodeArr;

typedef struct {
    uint32_t* numbers;

    uint32_t size;
} Arr;

static inline void PutReal(NodeArr* prevResult, NodeArr* result, Arr* realArr, const uint32_t linkAmount, const uint32_t realAmount, const uint32_t resultAmount) {
    if (prevResult) {
        if (linkAmount > 0) {
            if (realArr->numbers[realAmount] < prevResult->nodes[2 * linkAmount - 1].value) {
                result->nodes[resultAmount].down = 2 * linkAmount - 1;
            }
            else if ((2 * linkAmount < prevResult->size) && 
                        (realArr->numbers[realAmount] < prevResult->nodes[2 * linkAmount].value)) {
                result->nodes[resultAmount].down = 2 * linkAmount;
            }
            else {
                result->nodes[resultAmount].down = 2 * linkAmount + 1;
            }
        }
        else {
            if (realArr->numbers[realAmount] <= prevResult->nodes[0].value) {
                result->nodes[resultAmount].down = 0;
            }
            else {
                result->nodes[resultAmount].down = 1;
            }
        }
    }

    result->nodes[resultAmount].next  = realAmount;
    result->nodes[resultAmount].value = realArr->numbers[realAmount];
}

static inline void PutLastReals(NodeArr* prevResult, NodeArr* result, Arr* realArr, const uint32_t linkAmount, const uint32_t realAmount, const uint32_t resultAmount) {
    if (prevResult) {
        if (linkAmount > 0) {
            if (realArr->numbers[realAmount] == prevResult->nodes[2 * linkAmount - 1].value) {
                result->nodes[resultAmount].down = 2 * linkAmount - 1;
            }
            else {
                result->nodes[resultAmount].down = 2 * linkAmount;
            }
        }
        else {
            if (realArr->numbers[realAmount] <= prevResult->nodes[0].value) {
                result->nodes[resultAmount].down = 0;
            }
            else {
                result->nodes[resultAmount].down = 1;
            }
        }
    }

    result->nodes[resultAmount].value = realArr->numbers[realAmount];
    result->nodes[resultAmount].next  = realAmount;
}

static inline void PutLink(NodeArr* result, Arr* linkArr, const uint32_t lastReal, const uint32_t linkAmount, const uint32_t resultAmount, const uint32_t realAmount) {
    if ((realAmount > 0) && (result->nodes[lastReal].value == linkArr->numbers[linkAmount]))
        result->nodes[resultAmount].next  = realAmount - 1;
    else 
        result->nodes[resultAmount].next  = realAmount;

    result->nodes[resultAmount].down  = 2 * linkAmount + 1;
    result->nodes[resultAmount].value = linkArr->numbers[linkAmount];
}


static inline void MergeArrs(Arr* realArr, Arr* linkArr, NodeArr* result, NodeArr* prevResult) {
    uint32_t realAmount = 0;
    uint32_t linkAmount = 0;

    int32_t resultAmount = 0;

    uint32_t lastReal = 0;

    result->size = realArr->size + linkArr->size;
    while ((realAmount < realArr->size) && (linkAmount < linkArr->size)) {
        if ((realArr->numbers[realAmount] <= linkArr->numbers[linkAmount])) {
            PutReal(prevResult, result, realArr, linkAmount, realAmount, resultAmount);

            lastReal = resultAmount;
            realAmount++;
        }
        else {
            PutLink(result, linkArr, lastReal, linkAmount, resultAmount, realAmount);

            linkAmount++;
        }

        resultAmount++;
    }

    while (realAmount < realArr->size) {
        PutLastReals(prevResult, result, realArr, linkAmount, realAmount, resultAmount);

        lastReal = resultAmount;

        realAmount++;
        resultAmount++;
    }

    while (linkAmount < linkArr->size) {
        PutLink(result, linkArr, lastReal, linkAmount, resultAmount, realAmount);

        linkAmount++;
        resultAmount++;
    }

    return;
}

static inline int32_t NodeBinSearch(NodeArr* arr, uint32_t value) {
    int32_t left = 0;
    int32_t right = arr->size - 1;

    int32_t middle = 0;
    while (left <= right) {
        middle = (left + right) / 2;

        if (arr->nodes[middle].value < value) {
            left = middle + 1;
        } 
        else if (arr->nodes[middle].value == value) {
            while ((middle > 0) && (arr->nodes[middle - 1].value == value)) {
                middle--;
            }
            break;
        }
        else {
            right = middle - 1;
        }
    }

    while ((middle < arr->size) && (arr->nodes[middle].value < value))
        middle++;
 
    return middle;
}

static inline int32_t ArrBinSearch(Arr* arr, uint32_t value) {
    int32_t left = 0;
    int32_t right = arr->size - 1;

    int32_t middle = 0;
    while (left <= right) {
        middle = (left + right) / 2;

        if (arr->numbers[middle] < value) {
            left = middle + 1;
        } 
        else if (arr->numbers[middle] == value) {
            while ((middle > 0) && (arr->numbers[middle - 1] == value)) {
                middle--;
            }
            break;
        }
        else {
            right = middle - 1;
        }
    }

    while ((middle < arr->size) && (arr->numbers[middle] < value))
        middle++;
 
    return middle;
}

static inline void FindElem(NodeArr* nodeArrs, Arr* numberArr, const uint32_t arrAmount, const uint32_t value, int64_t* answers, const uint64_t answSize) {
    int32_t idx = NodeBinSearch(nodeArrs, value);

    int32_t curAnsw  = 0;
    int32_t nextAnsw = 0;
    
    if (idx != nodeArrs->size) {
        curAnsw  = nodeArrs->nodes[idx].next;
        nextAnsw = nodeArrs->nodes[idx].down;

        if (curAnsw != numberArr->size) {
            answers[answSize] += numberArr->numbers[curAnsw];
        }
        else {
            answers[answSize] += -1;
        }
    }
    else {
        curAnsw  = numberArr->size;

        if (arrAmount > 1)
            nextAnsw = nodeArrs[1].size - 1;

        answers[answSize] = -1;
    }

    for (uint32_t curArr = 1; curArr < arrAmount; curArr++) {
        if (nextAnsw < 1) {
            curAnsw  = nodeArrs[curArr].nodes[0].next;
            nextAnsw = nodeArrs[curArr].nodes[0].down;
        }
        else if ((nodeArrs[curArr].nodes[nextAnsw - 1].value >= value)) {
            curAnsw  = nodeArrs[curArr].nodes[nextAnsw - 1].next;
            nextAnsw = nodeArrs[curArr].nodes[nextAnsw - 1].down;
        }
        else if ((nextAnsw != nodeArrs[curArr].size) && 
                 (nodeArrs[curArr].nodes[nextAnsw].value >= value)) {
            curAnsw  = nodeArrs[curArr].nodes[nextAnsw].next;
            nextAnsw = nodeArrs[curArr].nodes[nextAnsw].down;
        }
        else {
            curAnsw = numberArr[curArr].size;

            if (curArr != (arrAmount - 1)) {
                nextAnsw = nodeArrs[curArr + 1].size - 1;
            }
        }

        if (curAnsw != numberArr[curArr].size)
            answers[answSize] += numberArr[curArr].numbers[curAnsw];
        else {
            answers[answSize] += -1;
        }
    }
}

int main() {
    setvbuf(stdout, NULL, _IOFBF, 0);

    uint32_t arrAmount  = 0;
    uint32_t rqstAmount = 0;
    scanf("%u %u", &arrAmount, &rqstAmount);

    Arr* arrs = calloc(arrAmount, sizeof(Arr));
    for (uint32_t curArr = 0; curArr < arrAmount; curArr++) {
        scanf("%u", &arrs[curArr].size); 

        arrs[curArr].numbers = calloc(arrs[curArr].size, sizeof(uint32_t));
        for (uint32_t curNumber = 0; curNumber < arrs[curArr].size; curNumber++) {
            scanf("%u", arrs[curArr].numbers + curNumber);
        }
    }

    NodeArr* nodes   = calloc(arrAmount, sizeof(NodeArr));

    Arr mergeArr = {};
    mergeArr.numbers = calloc(20000, sizeof(uint32_t)); 
    mergeArr.size    = 0;

    for (int32_t curArr = arrAmount - 1; curArr >= 0; curArr--) {
        nodes[curArr].nodes = calloc(arrs[curArr].size + mergeArr.size, sizeof(Node));

        if (curArr != arrAmount - 1)
            MergeArrs(arrs + curArr, &mergeArr, nodes + curArr, nodes + curArr + 1);  
        else
            MergeArrs(arrs + curArr, &mergeArr, nodes + curArr, NULL);  

        mergeArr.size = 0;
        for (uint32_t curReal = 1; curReal < nodes[curArr].size; curReal += 2) {
            mergeArr.numbers[mergeArr.size++] = nodes[curArr].nodes[curReal].value;
        }      
    }
    free(mergeArr.numbers);

    // FillNodesArr(nodes, arrs, arrAmount);

    // for (int32_t curArr = arrAmount - 1; curArr >= 0; curArr--) {
    //     for (uint32_t curNode = 0; curNode < nodes[curArr].size; curNode++) {
    //         printf("[%u]{%u, %d, %d}; ", curNode, nodes[curArr].nodes[curNode].value, nodes[curArr].nodes[curNode].next, nodes[curArr].nodes[curNode].down);
    //     }
    //     printf("\n\n");
    // }

    int64_t* answers = calloc(rqstAmount, sizeof(int64_t));

    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        uint32_t findValue = 0;
        scanf("%u", &findValue);

        FindElem(nodes, arrs, arrAmount, findValue, answers, curRqst);

        printf("%ld\n", answers[curRqst]);
    }

    free(answers);

    for (uint32_t curArr = 0; curArr < arrAmount; curArr++) {
        free(nodes[curArr].nodes);
        free(arrs[curArr].numbers);
    }

    free(nodes);
    free(arrs);
}
