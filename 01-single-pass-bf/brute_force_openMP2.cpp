#include <iostream>
#include <cmath>
#include <unistd.h>
#include <omp.h>

#define ASCII_START 97 // a
#define ASCII_END 122  // z
#define PASS_LEN 8
#define ALPHABET_SIZE (ASCII_END - ASCII_START + 1)

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
    bool found = false;
    // iterate over possible pass lengths
    for (int len = 1; len <= PASS_LEN; len++) {
        if (found) continue;
        long int totalComb = (std::pow((ALPHABET_SIZE), len) / ALPHABET_SIZE);

        // split possible combinations starting with given letter, (i.e. 'aaaaa', 'baaaa', 'caaaa', ..., 'zaaaa')
        // optimizes the algorithm for long passwords
        int charArr [ASCII_END - ASCII_START + 1][len];
        int val = ASCII_START;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            charArr[i][0] = val++;
            for (int j = 1; j < len; j++) charArr[i][j] = ASCII_START;
        }
        // iterate over all prebuilt password strings, starting from the end
        int i;
        #pragma omp parallel for shared(found) private(i)
        for (i = ALPHABET_SIZE - 1; i >= 0; i--) {
        // for (i = 0; i < ALPHABET_SIZE; i++) {
            if (found) continue;
            // iterate over all possible combinations for current string
            for (int j = 0; j < totalComb; j++) {
                if (found) continue;
                std::string currStr;
                for (int x : charArr[i]) currStr += char(x);
                if (verbose && flsh) std::cout << "\r" << "current: " << currStr << std::flush;
                if (verbose && !flsh) std::cout << currStr << std::endl;
                if (currStr == cipher) {
                    if (verbose) std::cout << "\n" << std::endl;
                    std::cout << "password found: " << currStr << std::endl;
                    found = true;
                    continue;
                }
                iterator(charArr[i], len);
            }
        }
    }
}

void bruteForce(std::string cipher, bool verbose, bool flsh) {
    iterativeBrute(cipher=cipher, verbose=verbose, flsh=flsh);
}

int main() {
    std::string plain = "yyyyyyy";
    bool verbose = false;
    bool flsh = false;
    bruteForce(plain, verbose, flsh);
    return 0;
}