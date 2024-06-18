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

    static std::string getFileContents(const std::string& fileName) {
        std::ifstream inputStream;
        std::stringstream ss;
        inputStream.open(fileName);
        ss << inputStream.rdbuf();
        inputStream.close();
        return ss.str();
    }

    char pop() {
        return input.at(index++);
    }

    char peek() const {
        return input.at(index);
    }

    static bool wordDelimiter(const char& c) {
        return isspace(c) || !isalnum(c);
    }

    static bool commentDelimiter(const char& c) {
        return c == '\n';
    }

    std::string getTextUntilDelimter(const std::function<bool(char)>& delimiterFunc) {
        std::stringstream ss;
        ss << currCharacter;
        while (true) {
            currCharacter = peek();
            if (delimiterFunc(currCharacter)) break;
            if (currCharacter == '\n') lineNumber++;
            ss << currCharacter;
            pop();
        }
        return ss.str();
    }

    std::string readWord() {
        return getTextUntilDelimter(&Scanner::wordDelimiter);
    }

    std::string readComment() {
        return getTextUntilDelimter(&Scanner::commentDelimiter);
    }

    Token readString() {
        int startingLineNumber = lineNumber;
        std::stringstream ss;
        ss << currCharacter;
        while (true) {
            if (index == input.size()) {
                return {UNDEFINED, ss.str(), startingLineNumber};
            }
            currCharacter = pop();
            ss << currCharacter;
            if (currCharacter == '\n') lineNumber++;
            if (currCharacter == '\'') break;
        }
        return {STRING, ss.str(), startingLineNumber};
    }

    void removeWhiteSpace() {
        while (true) {
            if (index == input.size()) {
                return;
            }
            currCharacter = pop();
            if (currCharacter == '\n') lineNumber++;
            if (!std::isspace(currCharacter)) break;
        }
    }

    Token getSingleCharacterTokens() const {
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
                return {UNDEFINED, "", lineNumber};
        }
    }

    Token getColonOrColonDash() {
        char nextChar = peek();
        if (nextChar == '-') {
            pop();
            return {COLON_DASH, ":-", lineNumber};
        } 
        return {COLON, ":", lineNumber};
    }

    TokenType getTokenTypeFromWord(const std::string& word) const {
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

    Token getWordRelatedToken() {
        std::string word = readWord();
        TokenType tokenType = getTokenTypeFromWord(word);
        return {tokenType, word, lineNumber};
    }

public:
    explicit Scanner(std::string input) : input(std::move(input)) {}

    /**
     * @brief Scans the next token in the provided input string
     * @return The next token: a token object
    */
    Token scanToken() {
        // Remove whitespice and potentially reach end of file
        removeWhiteSpace();
        if (index == input.size()) {
            return {EOFile, "", lineNumber};
        }
        // Check and return any single charracter tokens
        if (Token token = getSingleCharacterTokens(); token.getType() != UNDEFINED) {
            return token;
        }
        // Check for colon and colon-dash
        if (currCharacter == ':') {
            return getColonOrColonDash();
        }
        // Handle IDs, Queries, Schemes, etc.
        if (isalpha(currCharacter)) {
            return getWordRelatedToken();
        }
        // Handle string
        if (currCharacter == '\'') {
            return readString();
        }
        // Handle comment
        if (currCharacter == '#') {
            return {COMMENT, readComment(), lineNumber};
        }
        // Handle undefined
        std::string undefinedValue(1, currCharacter);
        return {UNDEFINED, undefinedValue, lineNumber};
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