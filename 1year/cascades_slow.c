#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int32_t uintCmp(const void* elem1, const void* elem2) {
    return *(uint32_t*)elem1 > *(uint32_t*)elem2;
}

int main() {
    srand(clock());

    uint32_t arrAmount  = rand() % 10000 + 2;
    uint32_t rqstAmount = rand() % 10000 + 1;
    uint32_t arrSize    = rand() % 10000 + 1;

    FILE* test = fopen("cascadesF/text.txt", "w");
    fprintf(test, "%u %u\n", arrAmount, rqstAmount);

    uint32_t** arrs = (uint32_t**)calloc(arrAmount, sizeof(uint32_t*));

    for (uint32_t curArr = 0; curArr < arrAmount; curArr++) {
        arrs[curArr] = (uint32_t*)calloc(arrSize, sizeof(uint32_t));

        for (uint32_t curElem = 0; curElem < arrSize; curElem++) {
            arrs[curArr][curElem] = rand() % 1000000;
        }

        qsort(arrs[curArr], arrSize, sizeof(uint32_t), uintCmp);

        fprintf(test, "%u ", arrSize);
        for (uint32_t curElem = 0; curElem < arrSize; curElem++) {
            fprintf(test, "%u ", arrs[curArr][curElem]);
        }
        fprintf(test, "\n");
    }

    uint32_t* rqstS = (uint32_t*)calloc(rqstAmount, sizeof(uint32_t));
    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        rqstS[curRqst] = rand() % 1000000;
        fprintf(test, "%u\n", rqstS[curRqst]);
    }    

    fclose(test);

    system("./cascFast.out < ./cascadesF/text.txt > ./cascadesF/resultMy.txt");
    FILE* result = fopen("cascadesF/result.txt", "w");

    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        for (uint32_t curArr = 0; curArr < arrAmount; curArr++) {
            char isFound = 0;

            for (uint32_t curElem = 0; curElem < arrSize; curElem++) {
                if (arrs[curArr][curElem] >= rqstS[curRqst]) {
                    isFound = 1;
                    
                    fprintf(result, "%u ", arrs[curArr][curElem]);
                    break;
                }
            }

            if (isFound == 0) {
                fprintf(result, "-1 ");
            }
        }
        fprintf(result, "\n");
    }

    fclose(result);

    FILE* slowResult = fopen("./cascadesF/result.txt", "r");
    FILE* fastResult = fopen("./cascadesF/resultMy.txt", "r");
    
    uint32_t stringCounter = 0;
    for (;;) {
        char* slowBuffer = (char*)calloc(10000000, sizeof(char));
        char* fastBuffer = (char*)calloc(10000000, sizeof(char));

        if (fgets(slowBuffer, 10000000, slowResult) == NULL) {
            break;
        }

        if (fgets(fastBuffer, 10000000, fastResult) == NULL) {
            break;
        }
        stringCounter++;

        if (strcmp(slowBuffer, fastBuffer) != 0) {
            printf("BAD AT %u STRING\n", stringCounter);
        }
    }


    fclose(fastResult);
    fclose(slowResult);
}
