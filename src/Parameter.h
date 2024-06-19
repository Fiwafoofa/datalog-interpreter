#pragma once
#include <string>
#include <stdexcept>
#include "Token.h"

class Parameter : private Token {

public:
    Parameter(TokenType tokenType, std::string tokenValue, int lineNumber) : Token(validateTokenType(tokenType), tokenValue, lineNumber) {}

    Parameter(Token token) : Token(validateTokenType(token.getType()), token.getTokenValue(), token.getLineNumber()) {}

    std::string toString() const {
        return value;
    }

private:

    static TokenType validateTokenType(TokenType tokenType) {
        if (tokenType == STRING || tokenType == ID) {
            return tokenType;
        }
        throw std::invalid_argument("Invalid Token Type for Parameter");
    }

};