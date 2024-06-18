#pragma once
#include <string>
#include <sstream>
#include <utility>

enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOFile
};

class Token {
public:
    Token(TokenType tokenType, std::string tokenValue, int lineNumber)
        : type(tokenType), value(std::move(tokenValue)), line(lineNumber) {}

    [[nodiscard]] std::string toString() const {
        std::stringstream out;
        out << "(" << typeName() << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }

    [[nodiscard]] TokenType getType() const {
        return type;
    }

protected:
    TokenType type;
    std::string value;
    int line;

    [[nodiscard]] std::string typeName() const {
        switch (type) {
            case COMMA:
                return "COMMA";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "Schemes";
            case FACTS:
                return "Facts";
            case RULES:
                return "Rules";
            case QUERIES:
                return "Queries";
            case EOFile:
                return "END";
            case ID:
                return "ID";
            case COMMENT:
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case STRING:
                return "STRING";
            default:
                return value;
        }
    }

};
