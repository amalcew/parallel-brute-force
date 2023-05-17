#include <iostream>
#include <unistd.h>

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

void bruteForce(std::string cipher, bool verbose, bool flsh) {
    int k = ASCII_START;
    while (1) {
        std::cout << char(k) << std::endl;
        k = iterator(k);
        //std::cout << '\r' << k << std::flush;
        usleep(100000);
    }
}

int main() {
    std::string plain = "zzzz";
    bool verbose = false;
    bool flsh = true;
    bruteForce(plain, verbose, flsh);
    return 0;
}