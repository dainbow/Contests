#include <iostream>
#include <cstdint>

#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string str1 = "", str2 = "";
    std::cin >> str1 >> str2;

    std::vector<std::vector<std::pair<uint16_t, uint16_t>>> db(2);

    for (uint16_t curChar1 = 0; curChar1 < str1.length(); curChar1++) {
        for (uint16_t curChar2 = 0; curChar2 < str2.length(); curChar2++) {
            if (str1[curChar1] == str2[curChar2]) {
                db[0].push_back({curChar1, curChar2});
            }
        }
    }    
    uint32_t maxLength = 1;

    if (!db[0].empty()) {
        while(true) {
            for (auto it = db[0].begin(); it != db[0].end(); it++) {
                if (((it->first + maxLength) < str1.length()) && ((it->second + maxLength) < str2.length()) &&
                    (str1[it->first + maxLength] == str2[it->second + maxLength])) {
                    db[1].push_back(*it);
                }
            }

            if (db[1].empty()) {
                break;
            }

            db.erase(db.begin());
            db.push_back({});

            maxLength++;
        }

        std::vector<std::string> answer(0);
        for (auto it = db[0].begin(); it != db[0].end(); it++) {
            answer.push_back(str1.substr(it->first, maxLength));
        }

        std::cout << *std::min_element(answer.begin(), answer.end()) << std::endl;
    }
    else {
        std::cout << "" << std::endl;
    }
}