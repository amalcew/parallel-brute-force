#include <iostream>
#include <unistd.h>
#include <cmath>

#define ASCII_START 97 // a
#define ASCII_END 122  // z
#define PASS_LEN 6

int* iterator(int* arr) {
    for (int x = 0; x < PASS_LEN; x++) {
        bool carry;
        // set carry to false, if current bit is the last bit in the array
        if (x == PASS_LEN - 1) {
            carry = false;
        } else {
            carry = true;
            // if any of the bits on the right from current bit is not equal to ASCII_END value, abort the carry operation
            for (int y = PASS_LEN - 1; y > x; y--) {
                if (arr[y] != ASCII_END) {
                    carry = false;
                }
            }
        }
        // if carry have been detected, add 1 to current value and reset all bits on the right from the current bit
        if (carry) {
            arr[x] += 1;
            for (int y = PASS_LEN - 1; y > x; y--) {
                if (y == PASS_LEN - 1) {
                    // TODO: investigate, why last bit needs to be additionally subtracted by one
                    arr[y] = ASCII_START - 1;
                } else {
                    arr[y] = ASCII_START;
                }
            }
        // if carry haven't been detected, add 1 to the last bit
        } else if (x == PASS_LEN-1) {
            arr[x] += 1;
        };
    }
    return arr;
}

std::string iterativeBrute(std::string cipher, bool verbose=true, bool flsh=true) {
    int totalComb = std::pow((ASCII_END - ASCII_START + 1), PASS_LEN);
    int charArr [PASS_LEN];
    std::fill_n(charArr, PASS_LEN, ASCII_START);

    for (int i = 0; i < totalComb; i++) {
        std::string currStr;
        for (int x : charArr) currStr += char(x);
        if (verbose && flsh) std::cout << "\r" << "current: " << currStr << std::flush;
        if (verbose && !flsh) std::cout << currStr << std::endl;
        if (currStr == cipher) {
            if (verbose) std::cout << "\n" << std::endl;
            return currStr;
        }
        iterator(charArr);
        //usleep(500000);
    }
    return "";
}

void bruteForce(std::string cipher, bool verbose, bool flsh) {
    std::string found = iterativeBrute(cipher=cipher, verbose=verbose, flsh=flsh);
    if (!found.empty()) {
        std::cout << "password found: " << found << std::endl;
    } else {
        std::cout << "password not found!" << std::endl;
    }
}

int main() {
    std::string plain = "hjkl";
    bool verbose = true;
    bool flsh = false;
    bruteForce(plain, verbose, flsh);
    return 0;
}