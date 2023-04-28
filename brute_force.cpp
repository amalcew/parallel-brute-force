#include <iostream>

#define START 97 //33
#define END 122 // 126
#define LENGTH 2

std::string recursiveBrute(std::string cipher, bool verbose=true, bool flsh=true, std::string currStr="") {
    std::string found;
    if (currStr.length() < LENGTH) {
        for (int asciiCode = START; asciiCode <= END; ++asciiCode) {
            std::string nextStr = currStr + char(asciiCode);
            if (verbose && flsh) std::cout << "\r" << "current: " << nextStr << std::flush;
            if (verbose && !flsh) std::cout << nextStr << std::endl;
            if (nextStr == cipher) {
                if (verbose) std::cout << "\n" << std::endl;
                return nextStr;
            }
            found = recursiveBrute(cipher, verbose, flsh, nextStr);
            if (!found.empty()) {
                return found;
            }
        }
    }
    return "";
}

void bruteForce(std::string cipher, bool verbose, bool flsh) {
    std::string found = recursiveBrute(cipher=cipher, verbose=verbose, flsh=flsh);
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
