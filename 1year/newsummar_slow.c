#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main() {
    srand(time(NULL));

    uint32_t arrSize    = rand() % 100;
    uint32_t rqstAmount = rand() % 100;

    FILE* text = fopen("./newsummarF/text.txt", "w");
    fprintf(text, "%u %u\n", arrSize, rqstAmount);

    int32_t* arr = calloc(arrSize, sizeof(int32_t));

    for (uint32_t curElem = 0; curElem < arrSize; curElem++) {
        arr[curElem] = rand() % 1000 * ((rand() % 2) * 2 - 1);
        fprintf(text, "%d ", arr[curElem]);
    }
    fprintf(text, "\n");

    FILE* result = fopen("./newsummarF/result.txt", "w");

    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        uint32_t rqst = rand() % 2 + 1;
        fprintf(text, "%u ", rqst);

        if (rqst == 1) {
            uint32_t curIdx  = rand() % arrSize;
            int32_t newValue = rand() % 1000 * ((rand() % 2) * 2 - 1);

            fprintf(text, "%u %d\n", curIdx, curRqst);

            arr[curIdx] = newValue;
        }
        else {
            uint32_t left = rand() % arrSize;
            uint32_t right = left + rand() % (arrSize - left);

            fprintf(text, "%u %u\n", left, right);

            int32_t answer = INT32_MIN;
            for (uint32_t curSize = 1; curSize < (right + 1 - left); curSize++) {
                for (uint32_t curSubArr = left; curSubArr <= right + 1 - curSize; curSubArr++) {
                    int32_t curSum = 0;

                    for (uint32_t curElem = curSubArr; curElem < curSubArr + curSize; curElem++) {
                        curSum += arr[curElem];
                    }

                    answer = (curSum > answer) ? curSum : answer;
                }
            }

            fprintf(result, "%d\n", answer);
        }
    }

    fclose(text);
    fclose(result);

    system("./newsummar.out < ./newsummarF/text.txt > ./newsummarF/myResult.txt");
}
