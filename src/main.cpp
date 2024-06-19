#include <iostream>
#include <list>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"


int main(int argc, char* argv[]) {    
    if (argc < 2) {
        std::cout << "./exe filename.txt" << std::endl;
        return -1;
    }

    std::string fileName = argv[1];
    std::list<Token> tokens = Scanner::getTokensFromFile(fileName);
    try {
        DatalogProgram datalogProgram = Parser::parse(tokens);
        std::cout << "Success!\n" << datalogProgram.toString() << std::endl;
    } catch (Token token) {
        std::cout << "Failure!\n  " << token.toString() << std::endl;
        return 1;
    }

    return 0;
}
