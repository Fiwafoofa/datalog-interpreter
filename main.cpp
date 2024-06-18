#include <iostream>
#include <list>
#include "Token.h"
#include "Scanner.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "./exe filename.txt" << std::endl;
        return -1;
    }

    std::string fileName = argv[1];
    std::list<Token> tokens = Scanner::getTokensFromFile(fileName);
    for (const Token& token : tokens) {
        std::cout << token.toString() << std::endl;
    }

    return 0;
}
