#include <iostream>
#include <cstdint>

#include <string>
#include <vector>
#include <map>

struct Trio {
    std::pair<uint8_t, uint8_t> pair;
    std::map<uint8_t, uint64_t> lengths;
};

int main() {
    std::string str = "";
    std::cin >> str;

    std::vector<Trio> differentPals = {};
    uint64_t answer = str.length();

    for (uint8_t curIdx = 0; curIdx < str.length(); curIdx++) {
        for (uint8_t curRight = curIdx + 1; curRight < str.length(); curRight++) {
            if (str[curIdx] == str[curRight]) {
                differentPals.push_back({{curIdx, curRight}, {{2, 1}}});
                answer++;
            }
        }
    }

    for (uint8_t curLength = 3; curLength <= str.length(); curLength++) {
        if ((curLength % 2) == 0) {
            for (auto& curTrio : differentPals) {
                auto iterOutside = curTrio.lengths.find(curLength - 2);

                if (iterOutside != curTrio.lengths.end()) {
                    for (auto& insideTrio : differentPals) {
                        if ((insideTrio.pair.first > curTrio.pair.first) && (insideTrio.pair.second < curTrio.pair.second)) {
                            auto iterInside = insideTrio.lengths.find(curLength);

                            if (iterInside != insideTrio.lengths.end()) {
                                iterInside->second += iterOutside->second;
                            }
                            else {
                                insideTrio.lengths.insert({curLength, iterOutside->second});
                            }

                            answer += iterOutside->second;
                        }
                    }
                }
            }
        }
        else {
            for (auto& curTrio : differentPals) {
                auto iter = curTrio.lengths.find(curLength - 1);

                if (iter != curTrio.lengths.end()) {
                    for (uint8_t curIdx = 0; curIdx < str.length(); curIdx++) {
                        if ((curIdx > curTrio.pair.first) && (curIdx < curTrio.pair.second)) {
                            answer += iter->second;
                        }
                    }
                }
            }
        }
    }

    std::cout << answer << std::endl;
}
