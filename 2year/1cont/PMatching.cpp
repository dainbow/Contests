#include <iostream>
#include <cstdint>

#include <string>
#include <set>

int main() {
    std::string str1 = "", str2 = "";
    std::cin >> str1 >> str2;

    std::set<uint16_t>* db = new std::set<uint16_t>[str2.length() + 1];
    db[0].insert(0);

    for (uint16_t curIdx2 = 0; curIdx2 < str2.length(); curIdx2++) {
        for (auto& curIdx1 : db[curIdx2]) {
            if (str2[curIdx2] == '*') {
                for (uint16_t curNewIdx = curIdx1; curNewIdx < (str1.length() + 1); curNewIdx++) {
                    db[curIdx2 + 1].insert(curNewIdx);
                }
            }
            else if (str2[curIdx2] == '?') {
                if (curIdx1 < str1.length())
                    db[curIdx2 + 1].insert(curIdx1 + 1);
            }
            else {
                if ((curIdx1 < str1.length()) && (str1[curIdx1] == str2[curIdx2])) {
                    db[curIdx2 + 1].insert(curIdx1 + 1);
                }
            }
        }
    }

    if ((!db[str2.length()].empty()) && (db[str2.length()].find(str1.length()) != db[str2.length()].end())) {
        std::cout << "YES" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }

    delete[] db;
}
