//
// Created by Gregory Knapp on 6/30/20.
//

#ifndef LAB2_PARSER_H
#define LAB2_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>


class Parser {
public:
    Parser(vector<Token> list);
    ~Parser();
    void parse();
    void parseDatalogProgram();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIDList();
    void parseParameter();
    void parseExpression();
    void parseOperator();
    void match(TokenType t);
    void getToken();
    DatalogProgram passLog();

private:
    vector<Token> tokenList;
    Token currentToken;
    int tokenNum;
    DatalogProgram myDatalog;
    Predicate myPredicate;
    Rule myRule;
    string myExpression;
    bool isExpression;
};


#endif //LAB2_PARSER_H
