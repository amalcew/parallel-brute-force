#include <iostream>
#include <cmath>
#include <unistd.h>
#include <omp.h>

#define ASCII_START 97 // a
#define ASCII_END 122  // z
#define PASS_LEN 7

int* iterator(int* arr, int len) {
    for (int x = 0; x < len; x++) {
        bool carry;
        // set carry to false, if current bit is the last bit in the array
        if (x == len - 1) {
            carry = false;
        } else {
            carry = true;
            // if any of the bits on the right from current bit is not equal to ASCII_END value, abort the carry operation
            for (int y = len - 1; y > x; y--) {
                if (arr[y] != ASCII_END) {
                    carry = false;
                }
            }
        }
        // if carry have been detected, add 1 to current value and reset all bits on the right from the current bit
        if (carry) {
            arr[x] += 1;
            for (int y = len - 1; y > x; y--) {
                if (y == len - 1) {
                    // TODO: investigate, why last bit needs to be additionally subtracted by one
                    arr[y] = ASCII_START - 1;
                } else {
                    arr[y] = ASCII_START;
                }
            }
        // if carry haven't been detected, add 1 to the last bit
        } else if (x == len-1) {
            arr[x] += 1;
        };
    }
    return arr;
}

void iterativeBrute(std::string cipher, bool verbose=true, bool flsh=true) {
    int len;
    bool found = false;
    #pragma omp parallel for shared(found) private(len)
    // iterate over possible pass lengths
    for (len = 1; len <= PASS_LEN; len++) {
        if (found) continue;
        long int totalComb = std::pow((ASCII_END - ASCII_START + 1), len);
        int charArr [len];
        std::fill_n(charArr, len, ASCII_START);
        // iterate over all possible combinations for current length of the password
        for (int i = 0; i < totalComb; i++) {
            if (found) continue;
            std::string currStr;
            for (int x : charArr) currStr += char(x);
            if (verbose && flsh) std::cout << "\r" << "current: " << currStr << std::flush;
            if (verbose && !flsh) std::cout << currStr << std::endl;
            if (currStr == cipher) {
                if (verbose) std::cout << "\n" << std::endl;
                // return currStr;
                std::cout << "password found: " << currStr << std::endl;
                found = true;
                break;
            }
            iterator(charArr, len);
            // usleep(100000);
        }
    }
    // return "";
}

void bruteForce(std::string cipher, bool verbose, bool flsh) {

    // std::string found = iterativeBrute(cipher=cipher, verbose=verbose, flsh=flsh);
    // if (!found.empty()) {
    //     std::cout << "password found: " << found << std::endl;
    // } else {
    //     std::cout << "password not found!" << std::endl;
    // }

    iterativeBrute(cipher=cipher, verbose=verbose, flsh=flsh);
}

int main() {
    std::string plain = "abcdefg";
    bool verbose = false;
    bool flsh = true;
    bruteForce(plain, verbose, flsh);
    return 0;
}