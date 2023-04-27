#include <iostream>

#define START 97 //33
#define END 122 // 126
#define LENGTH 4

std::string recursiveBrute(std::string cipher, std::string str="", bool verbose=true) {
    std::string found;
    if (str.length() < LENGTH) {
        for (int asciiCode = START; asciiCode <= END; ++asciiCode) {
            std::string next = str + char(asciiCode);
            if (verbose) std::cout << "\r" << "current: " << next << std::flush;
            if (next == cipher) {
                // if (verbose) std::cout << "password found: " << next << std::endl;
                if (verbose) std::cout << "\n" << std::endl;
                return next;
            }

            found = recursiveBrute(cipher, next, verbose);
            if (found.length() > 0) {
                return found;
            }
        }
    }
    return "";
}

void bruteForce(std::string cipher, bool verbose) {
    std::string str;
    std::string found = recursiveBrute(cipher=cipher, str=str, verbose=verbose);
    if (found.length() > 0) {
        std::cout << "password found: " << found << std::endl;
    } else {
        std::cout << "password not found!" << std::endl;
    }
}

int main() {
    std::string plain = "hjkl";
    bool verbose = true;
    bruteForce(plain, verbose);
    return 0;
}
