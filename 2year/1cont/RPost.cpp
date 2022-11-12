#include <iostream>
#include <cstdint>

void FillSums(uint16_t* ctrtyCoords, uint64_t** sums, const uint32_t ctryAmount) {
    for (uint32_t curLeft = 0; curLeft < (ctryAmount + 2); curLeft++) {
        if (curLeft == 0) {
            for (uint32_t curRight = (curLeft + 1); curRight < (ctryAmount + 1); curRight++) {
                for (uint32_t curMiddle = (curLeft + 1); curMiddle < curRight; curMiddle++) {
                    sums[curLeft][curRight] += ctrtyCoords[curRight - 1] - ctrtyCoords[curMiddle - 1];
                }
            }
        }
        else {
            for (uint32_t curRight = (curLeft + 1); curRight < (ctryAmount + 1); curRight++) {
                for (uint32_t curMiddle = (curLeft + 1); curMiddle < curRight; curMiddle++) {
                    uint32_t coordMiddle = (ctrtyCoords[curLeft - 1] + ctrtyCoords[curRight - 1]) / 2;

                    if (ctrtyCoords[curMiddle - 1] <= coordMiddle) {
                        sums[curLeft][curRight] += ctrtyCoords[curMiddle - 1] - ctrtyCoords[curLeft - 1];
                    }
                    else {
                        sums[curLeft][curRight] += ctrtyCoords[curRight - 1] - ctrtyCoords[curMiddle - 1];
                    }
                }
            }

            for (uint32_t curMiddle = (curLeft + 1); curMiddle < ctryAmount + 1; curMiddle++) {
                sums[curLeft][ctryAmount + 1] += ctrtyCoords[curMiddle - 1] - ctrtyCoords[curLeft - 1];
            }
        }
    }
}

int main() {
    uint16_t ctryAmount = 0, postAmount = 0;
    std::cin >> ctryAmount >> postAmount;
    
    uint16_t* ctrtyCoords = new uint16_t[ctryAmount]();
    for (uint16_t curCtry = 0; curCtry < ctryAmount; curCtry++) {
        std::cin >> ctrtyCoords[curCtry];
    }

    uint64_t** sums = new uint64_t*[ctryAmount + 2]();
    for (int32_t curCtry = 0; curCtry < (ctryAmount + 2); curCtry++) {
        sums[curCtry] = new uint64_t[ctryAmount + 2]();
    }

    FillSums(ctrtyCoords, sums, ctryAmount);

    std::pair<uint64_t, uint16_t>** db = new std::pair<uint64_t, uint16_t>*[postAmount]();
    for (uint16_t curPost = 0; curPost < postAmount; curPost++) {
        db[curPost] = new std::pair<uint64_t, uint16_t>[ctryAmount]();
    }

    for (uint32_t curRight = 0; curRight < ctryAmount; curRight++) {
        db[0][curRight].first = sums[0][curRight + 1];
    }

    for (uint16_t curPost = 1; curPost < postAmount; curPost++) {
        for (uint16_t curRight = curPost; curRight < ctryAmount; curRight++) { 
            uint64_t leftSum = UINT64_MAX;
            uint16_t leastIdx = 0;

            for (uint16_t curLeft = 0; curLeft < curRight; curLeft++) {
                if ((db[curPost - 1][curLeft].first + sums[curLeft + 1][curRight + 1]) < leftSum) {
                    leftSum = db[curPost - 1][curLeft].first + sums[curLeft + 1][curRight + 1];
                    leastIdx = curLeft;
                }
            }

            db[curPost][curRight] = {leftSum, leastIdx};   
        }
    }

    uint64_t answer = UINT64_MAX;
    uint16_t answerIdx = 0;

    for (uint32_t curRight = 0; curRight < ctryAmount; curRight++) {
        if (db[postAmount - 1][curRight].first + sums[curRight + 1][ctryAmount + 1] < answer) {
            answer = db[postAmount - 1][curRight].first + sums[curRight + 1][ctryAmount + 1];
            answerIdx = curRight;
        }
    }
 
    std::cout << answer << std::endl;

    uint16_t* answers = new uint16_t[postAmount];
    for (int32_t curPost = postAmount - 1; (curPost >= 0); curPost--) {
        answers[curPost] = ctrtyCoords[answerIdx];
        answerIdx = db[curPost][answerIdx].second;
    }

    for (uint16_t curPost = 0; curPost < postAmount; curPost++) {
        std::cout << answers[curPost] << " ";
    }
    std::cout << std::endl;



    delete[] answers;
    for (uint16_t curPost = 0; curPost < postAmount; curPost++) {
        delete[] db[curPost];
    }
    delete[] db;

    for (int32_t curCtry = 0; curCtry < (ctryAmount + 2); curCtry++) {
        delete [] sums[curCtry];
    }
    delete[] sums;

    delete[] ctrtyCoords;
}