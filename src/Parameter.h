#include <string>
#include <stdexcept>
#include "Token.h"

class Parameter : private Token {

public:
    Parameter(TokenType tokenType, std::string tokenValue, int lineNumber) : Token(validateTokenType(tokenType), tokenValue, lineNumber) {}

    std::string toString() const {
        if (type == ID) {
            return value; 
        } else { // its a string
            return '\'' + value + '\'';
        }
    }

private:

    static TokenType validateTokenType(TokenType tokenType) {
        if (tokenType == STRING || tokenType == ID) {
            return tokenType;
        }
        throw std::invalid_argument("Invalid Token Type for Parameter");
    }

};