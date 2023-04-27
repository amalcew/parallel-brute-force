#include <iostream>

#define START 97 //33
#define END 122 // 126
#define LENGTH 4

std::string recursiveBrute(std::string cipher, bool verbose=true, std::string currStr="") {
    std::string found;
    if (currStr.length() < LENGTH) {
        for (int asciiCode = START; asciiCode <= END; ++asciiCode) {
            std::string nextStr = currStr + char(asciiCode);
            if (verbose) std::cout << "\r" << "current: " << nextStr << std::flush;
            if (nextStr == cipher) {
                if (verbose) std::cout << "\n" << std::endl;
                return nextStr;
            }
            found = recursiveBrute(cipher, verbose, nextStr);
            if (found.length() > 0) {
                return found;
            }
        }
    }
    return "";
}

void bruteForce(std::string cipher, bool verbose) {
    std::string found = recursiveBrute(cipher=cipher, verbose=verbose);
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
