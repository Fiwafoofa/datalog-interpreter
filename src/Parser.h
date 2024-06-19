#include <iostream>
#include <list>
#include "Token.h"
#include "DatalogProgram.h"

class Parser {
public:
    Parser(const std::list<Token>& tokens) : tokens(tokens) {}

    DatalogProgram parseDatalogProgram() {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();

        match(FACTS);
        match(COLON);
        fact();
        factList();

        match(RULES);
        match(COLON);
        rule();
        ruleList();

        match(QUERIES);
        match(COLON);
        query();
        queryList();

        match(EOFile);

        return datalogProgram;
    }

    static bool isCommentToken(Token token) {
        return token.getType() == COMMENT;
    }

    static DatalogProgram parse(const std::list<Token>& tokens) {
        std::list<Token> filteredTokens;
        for (const Token& token : tokens) {
            if (token.getType() != COMMENT) {
                filteredTokens.push_back(token);
            }
        }
        Parser parser = Parser(filteredTokens);
        return parser.parseDatalogProgram();
    }

private:
    DatalogProgram datalogProgram;
    std::list<Token> tokens;
    Predicate currPredicate;
    Rule currRule;
    Token lastMatchedToken;

    TokenType currTokenType() const {
        return tokens.front().getType();
    }

    void advanceToken() {
        tokens.pop_front();
    }

    void match(TokenType tokenType) {
        if (tokenType == currTokenType()) {
            lastMatchedToken = tokens.front();
            advanceToken();
        } else {
            throw tokens.front();
        }
    }

    void schemeList() {
        if (currTokenType() == ID) {
            scheme();
            schemeList();
        }
        // lambda
    }

    void factList() {
        if (currTokenType() == ID) {
            fact();
            factList();
        } 
        // lambda
    }

    void ruleList() {
        if (currTokenType() == ID) {
            rule();
            ruleList();
        }
        // lambda
    }

    void queryList() {
        if (currTokenType() == ID) {
            query();
            queryList();
        } 
        // lambda
    }

    void scheme() {
        currPredicate = Predicate();
        match(ID);
        currPredicate.setName(lastMatchedToken.getTokenValue());
        match(LEFT_PAREN);
        match(ID);
        currPredicate.addParameter(Parameter(lastMatchedToken));
        idList();
        match(RIGHT_PAREN);
        datalogProgram.addToSchemes(currPredicate);
    }

    void fact() {
        if (currTokenType() == ID) {
            currPredicate = Predicate();
            match(ID);
            currPredicate.setName(lastMatchedToken.getTokenValue());
            match(LEFT_PAREN);
            match(STRING);  
            datalogProgram.addToDomains(lastMatchedToken.getTokenValue());
            currPredicate.addParameter(Parameter(lastMatchedToken));
            stringList();
            match(RIGHT_PAREN);
            match(PERIOD);
            datalogProgram.addToFacts(currPredicate);
        }
        // lambda
    }

    void rule() {
        if (currTokenType() == ID) {
            currRule = Rule();
            headPredicate();
            currRule.setHeadPredicate(currPredicate);
            match(COLON_DASH);
            predicate();
            currRule.addToPredicateList(currPredicate);
            predicateList();
            match(PERIOD);
            datalogProgram.addToRules(currRule);
        }
        // lambda
    }

    void query() {
        predicate();
        match(Q_MARK);
        datalogProgram.addToQueries(currPredicate);
    }

    void headPredicate() {
        currPredicate = Predicate();
        match(ID);
        currPredicate.setName(lastMatchedToken.getTokenValue());
        match(LEFT_PAREN);
        match(ID);  
        currPredicate.addParameter(Parameter(lastMatchedToken));
        idList();
        match(RIGHT_PAREN);
    }

    void predicate() {
        currPredicate = Predicate();
        match(ID);
        currPredicate.setName(lastMatchedToken.getTokenValue());
        match(LEFT_PAREN);
        parameter();
        currPredicate.addParameter(Parameter(lastMatchedToken));
        parameterList();
        match(RIGHT_PAREN);
    }

    void predicateList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            predicate();
            currRule.addToPredicateList(currPredicate);
            predicateList();
        }
        // lambda
    }

    void parameterList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            parameter();
            currPredicate.addParameter(Parameter(lastMatchedToken));
            parameterList();
        }
        // lambda
    }

    void stringList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            match(STRING);
            currPredicate.addParameter(Parameter(lastMatchedToken));
            datalogProgram.addToDomains(lastMatchedToken.getTokenValue());
            stringList();
        } else {
            // lambda
        }
    }

    void idList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            match(ID);
            currPredicate.addParameter(Parameter(lastMatchedToken));
            idList();
        }
        // lambda
    }

    void parameter() {
        if (currTokenType() == STRING) {
            match(STRING);
        } else {
            match(ID);
        }
    }
};