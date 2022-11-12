#include <iostream>
#include <cstdint>

class BigInt {
    public:
        std::string data;
        BigInt() {
            data = "0";
        }

        BigInt(const std::string& newData) {
            for (uint32_t curIdx = 0; curIdx < newData.length(); curIdx++) {
                data.push_back('0');
                data[curIdx] = newData[newData.length() - curIdx - 1]; 
            }
        }

        void operator+=(const BigInt& number) {
            while (data.length() < number.data.length())
                data.push_back('0');

            uint32_t thisLength   = data.length();
            uint32_t numberLength = number.data.length();

            uint32_t min = std::min(thisLength, numberLength);

            bool shiftValue = 0;
            for (uint32_t curIdx = 0; curIdx < min; curIdx++) {
                uint8_t curChar = data[curIdx] - '0';
                curChar += shiftValue + (number.data[curIdx] - '0');

                shiftValue = ((curChar / 10) != 0);
                data[curIdx] = (curChar % 10) + '0';
            }

            uint32_t curIdx = min;
            while (shiftValue != 0) {
                if (curIdx == thisLength)
                    data.push_back('0');

                uint8_t curChar = data[curIdx] - '0';
                curChar += shiftValue;

                shiftValue = (curChar / 10) != 0;
                data[curIdx++] = (curChar % 10) + '0';
            }
        }

        BigInt operator+(const BigInt& number) const {
            BigInt result = *this;
            result += number;

            return result;
        }
};

std::ostream& operator<<(std::ostream& outStream, const BigInt& number) {
    for (int64_t curIdx = number.data.length() - 1; curIdx >= 0; curIdx--) {
        outStream << number.data[curIdx];
    }           

    return outStream;
}

int main() {
    uint16_t ticketSize = 0, numeralAmount = 0;
    std::cin >> ticketSize >> numeralAmount;

    BigInt** db = new BigInt*[ticketSize]();
    for (uint32_t curSize = 0; curSize < ticketSize; curSize++) {
        db[curSize] = new BigInt[numeralAmount * (curSize + 1)];
    }

    for (uint32_t curNumber = 0; curNumber < numeralAmount; curNumber++) {
        db[0][curNumber] = {"1"};

        for (uint32_t curNextNumber = 0; (curNextNumber < numeralAmount) && ((curNumber + curNextNumber) < 2 * numeralAmount); curNextNumber++)
            db[1][curNumber + curNextNumber] += db[0][curNumber];
    }

    for (uint32_t curSize = 1; curSize < uint32_t(ticketSize - 1); curSize++) {
        for (uint32_t curNumber = 0; curNumber < ((curSize + 1) * numeralAmount); curNumber++) {
            for (uint32_t curNextNumber = 0; (curNextNumber < numeralAmount) && ((curNumber + curNextNumber) < (curSize + 2) * numeralAmount); curNextNumber++)
                db[curSize + 1][curNumber + curNextNumber] += db[curSize][curNumber];
        }
    }
   
    std::cout << db[ticketSize - 1][(ticketSize / 2) * (numeralAmount - 1)] << std::endl;

    for (uint32_t curSize = 0; curSize < ticketSize; curSize++) {
        delete[] db[curSize];
    }
    delete[] db;
}
