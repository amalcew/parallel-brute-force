#include <iostream>

#define START 97 //33
#define END 122 // 126
#define LENGTH 4

bool iterator(std::string cipher, std::string str) {
    bool found;
    if (str.length() < LENGTH) {
        for (int asciiCode = START; asciiCode <= END; ++asciiCode) {
            std::string next = str + char(asciiCode);
            std::cout << next << std::endl;
            if (next == cipher) {
                //std::cout << "password found: " << next << std::endl;
                return true;
            }
            found = iterator(cipher, next);
            if (found) {
                return true;
            }
        }
    }
    return false;
}

void bruteForce(std::string cipher) {
    bool found = iterator(cipher, "");
    if (found) {
        std::cout << "password found." << std::endl;
    } else {
        std::cout << "password not found!" << std::endl;
    }
}

int main() {
    std::string plain = "hjka";
    bruteForce(plain);
    return 0;
}
