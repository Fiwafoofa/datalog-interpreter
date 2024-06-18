#pragma once
#include <string>
#include "Token.h"
#include <list>
#include <fstream>
#include <sstream>
#include <functional>

class Scanner {
private:
    std::string input;
    int lineNumber = 1;
    int index = 0;
    char currCharacter;

    char pop() {
        return input.at(index++);
    }

    char peek() {
        return input.at(index);
    }

    static std::string getFileContents(const std::string& fileName) {
        std::ifstream inputStream;
        inputStream.open(fileName);
        std::stringstream ss;
        ss << inputStream.rdbuf();
        std::string fileInput = ss.str();
        inputStream.close();
        return fileInput;
    }

    static bool wordDelimiter(char c) {
        return isspace(c) || !isalnum(c);
    }

    static bool singleQuoteDelimiter(char c) {
        return c == '\'';
    }

    static bool commentDelimiter(char c) {
        return c == '\n';
    }

    std::string getTextUntilDelimter(std::function<bool(char)> delimiterFunc) {
        std::stringstream ss;
        ss << currCharacter;
        while (true) {
            if (index == input.size()) {
                return "";
            }

            currCharacter = peek();
            if (delimiterFunc(currCharacter)) break;
            if (currCharacter == '\n') lineNumber++;

            ss << currCharacter;
            pop();
        }
        return ss.str();
    }

    std::string readString() {
        return getTextUntilDelimter(&Scanner::singleQuoteDelimiter);
    }

    std::string readWord() {
        return getTextUntilDelimter(&Scanner::wordDelimiter);
    }

    std::string readComment() {
        return getTextUntilDelimter(&Scanner::commentDelimiter);
    }

    TokenType getTokenTypeFromWord(std::string word) {
        if (word == "Schemes") {
            return SCHEMES;
        } else if (word == "Facts") {
            return FACTS;
        } else if (word == "Rules") {
            return RULES;
        } else if (word == "Queries") {
            return QUERIES;
        } else {
            return ID;
        }
    }

public:
    explicit Scanner(std::string input) : input(std::move(input)) {}

    /**
     * @brief Scans the next token in the provided input string
     * @return The next token: a token object
    */
    Token scanToken() {
        while (true) {
            if (index == input.size()) {
                return {EOFile, "", lineNumber};
            }
            currCharacter = pop();
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
        }

        if (currCharacter == ':') {
            char nextChar = peek();
            if (nextChar == '-') {
                pop();
                return {COLON_DASH, ":-", lineNumber};
            } 
            return {COLON, ":", lineNumber};
        }

        if (isalpha(currCharacter)) {
            std::string word = readWord();
            TokenType tokenType = getTokenTypeFromWord(word);
            return {tokenType, word, lineNumber};
        }

        if (currCharacter == '\'') {
            std::string stringValue = readString();
            stringValue += pop();
            return {STRING, stringValue, lineNumber};
        }

        if (currCharacter == '#') {
            std::string commentValue = readComment();
            return {COMMENT, commentValue, lineNumber};
        }

        // undefined stuff
        std::string undefinedValue(1, currCharacter);
        return {UNDEFINED, undefinedValue, lineNumber};
            
        // return {EOFile, "", lineNumber};
    }

    /**
     * @brief Gets all the tokens from the provided fileName and returns a list 
     * of Token objects
     * @param fileName The fileName to scan tokens from
     * @return A list of Token objects
    */
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