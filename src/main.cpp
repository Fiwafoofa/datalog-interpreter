#include <iostream>
#include <list>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"


int main(int argc, char* argv[]) {    

    std::list<Token> tokens = {
        Token(ID,"Ned",2),
        // Token(LEFT_PAREN,"(",2),
        Token(ID,"Ted",2),
        Token(COMMA,",",2),
        Token(ID,"Zed",2),
        Token(RIGHT_PAREN,")",2),
    };

    Parser p = Parser(tokens);
    p.scheme();

    // if (argc < 2) {
    //     std::cout << "./exe filename.txt" << std::endl;
    //     return -1;
    // }

    // std::string fileName = argv[1];
    // std::list<Token> tokens = Scanner::getTokensFromFile(fileName);
    // for (const Token& token : tokens) {
    //     std::cout << token.toString() << std::endl;
    // }
    // std::cout << "Total Tokens = " << tokens.size() << std::endl;
    return 0;
}
