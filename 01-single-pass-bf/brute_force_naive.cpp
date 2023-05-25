#include <iostream>

#define ASCII_START 97 // a
#define ASCII_END 122  // z
#define PASS_LEN 4

int iterator(int k) {
    if (k < ASCII_END) {
        return ++k;
    } else {
        return ASCII_START;
    }
}

std::string iterativeBrute(std::string cipher, bool verbose=true, bool flsh=true) {
    for (int i = ASCII_START; i <= ASCII_END; i++) {
        for (int j = ASCII_START; j <= ASCII_END; j++) {
            for (int k = ASCII_START; k <= ASCII_END; k++) {
                for (int l = ASCII_START; l <= ASCII_END; l++) {
                    char arr [] = {char(i), char(j), char(k), char(l)};
                    std::string currStr;
                    for (char x : arr) {
                        currStr += x;
                    }
                    if (verbose && flsh) std::cout << "\r" << "current: " << currStr << std::flush;
                    if (verbose && !flsh) std::cout << currStr << std::endl;
                    if (currStr == cipher) {
                        if (verbose) std::cout << "\n" << std::endl;
                        return currStr;
                    }
                }
            }
        }
    }
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
    bool flsh = true;
    bruteForce(plain, verbose, flsh);
    return 0;
}