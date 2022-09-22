//
// Created by Gregory Knapp on 6/23/20.
//

#ifndef LAB1_TOKEN_H
#define LAB1_TOKEN_H


#include <string>
#include <iostream>
#include <sstream>

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES,
                FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDFILE};

using namespace std;

class Token {

public:
    Token(string token, TokenType type, int line);
    ~Token() {};
    string toString();
    string typeToString(TokenType type);

protected:
    int lineNumber;
    TokenType tokenType;
    string tokenValue;
};

#endif //LAB1_TOKEN_H
