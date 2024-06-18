#pragma once
#include <string>
#include "Token.h"
#include <list>
#include <fstream>
#include <sstream>
#include <utility>

class Scanner {
private:
    std::string input;
    int lineNumber = 1;
    int index = 0;

    char popChar() {
        return input.at(index++);
    }

    static std::string getFileContents(const std::string& fileName) {
        std::ifstream inputStream;
        inputStream.open(fileName);
        std::stringstream ss;
        ss << inputStream.rdbuf();
        std::string fileInput = ss.str();
        inputStream.close();
        std::cout << fileInput << std::endl;
        return fileInput;
    }

    std::string readWord() {
        std::stringstream ss;
        char currCharacter;
        while (true) {
            currCharacter = popChar();
            if (std::isspace(currCharacter)) break;
            ss << currCharacter;
        }

        return ss.str();
    }

public:
    explicit Scanner(std::string input) : input(std::move(input)) {}

    Token scanToken() {
        char currCharacter;
        while (true) {
            if (index == input.size()) {
                return {EOFile, "", lineNumber};
            }
            currCharacter = popChar();
            if (currCharacter == '\n') lineNumber++;
            if (!std::isspace(currCharacter)) break;
        }

        switch (currCharacter) {
            case ',':
                return {COMMA, ",", lineNumber};
            case '.':
                return {PERIOD, ".", lineNumber};
            case '?':
                return {Q_MARK, "?", lineNumber};
            case '(':
                return {LEFT_PAREN, "(", lineNumber};
            case ')':
                return {RIGHT_PAREN, ")", lineNumber};
            case '*':
                return {MULTIPLY, "*", lineNumber};
            case '+':
                return {ADD, "+", lineNumber};
            default:
                return {EOFile, "", lineNumber};

//                case COLON: // also colon-dash
        }
    }

    static std::list<Token> getTokensFromFile(const std::string& fileName) {
        Scanner scanner = Scanner(getFileContents(fileName));
        std::list<Token> tokens;
        while (true) {
            Token t = scanner.scanToken();
            tokens.push_back(t);
            if (t.getType() == EOFile) break;
        }
        return tokens;
    }
};