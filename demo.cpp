#include <iostream>
#include <cmath>

#define START 97 //a //33
#define END 122 //z // 126
#define LENGTH 4

void bruteForce(std::string plain) {
    int allCombinations = std::pow(END - START + 1, LENGTH);
    std::string endStr = "zzzz";
    while (1) {
        // traktować stringi jako ciągi kodów ASCII, gdzie każdy bit liczony od 0 do 26 + 97 (długość alfabetu) jest modulowany przez 122, aby dokonać zapętlenia

    }
}

int main() {
    std::string plain = "hjkl";

    bruteForce(plain);
    return 0;
}