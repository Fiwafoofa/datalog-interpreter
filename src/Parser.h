#include <iostream>
#include <list>
#include "Token.h"
#include "DatalogProgram.h"

class Parser {
public:
    Parser(const std::list<Token>& tokens) : tokens(tokens) {}

    void parseDatalogProgram() {
        match(SCHEMES);
        // match()
    }

    void idList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        } else {
            // lambda
        }
    }

    void scheme() {
        if (currTokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        }
    }

private:
    DatalogProgram datalogProgram = DatalogProgram();
    std::list<Token> tokens;

    TokenType currTokenType() const {
        return tokens.front().getType();
    }

    void advanceToken() {
        tokens.pop_front();
    }

    void match(TokenType tokenType) {
        std::cout << "match " << tokenType << std::endl;
        if (tokenType == currTokenType()) {
            advanceToken();
        } else {
            throw tokens.front();
        }
    }

};