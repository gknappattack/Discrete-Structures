//
// Created by Gregory Knapp on 6/29/20.
//

#include "Token.h"

Token::Token() {
    tokenType = UNDEFINED;
    tokenValue = "";
    lineNumber = 0;
}

Token::Token(string token, TokenType type, int line) {
    tokenType = type;
    tokenValue = token;
    lineNumber = line;
}

string Token::toString() {
    stringstream ss;
    //TODO: In future labs see if I need to print tokens w/ endline or not. Currently no endline.
    ss << "(" << typeToString(tokenType) << ",\"" << tokenValue << "\"," << lineNumber << ")";
    return ss.str();
}

string Token::typeToString(TokenType type) {
    switch (type) {
        case COMMA : return "COMMA";
        case PERIOD : return "PERIOD";
        case Q_MARK : return "Q_MARK";
        case LEFT_PAREN : return "LEFT_PAREN";
        case RIGHT_PAREN : return "RIGHT_PAREN";
        case COLON : return "COLON";
        case COLON_DASH : return "COLON_DASH";
        case MULTIPLY : return "MULTIPLY";
        case ADD : return "ADD";
        case SCHEMES : return "SCHEMES";
        case FACTS : return "FACTS";
        case RULES : return "RULES";
        case QUERIES : return "QUERIES";
        case ID : return "ID";
        case STRING : return "STRING";
        case COMMENT : return "COMMENT";
        case UNDEFINED : return "UNDEFINED";
        case ENDFILE : return "EOF";
    }
    return "ERROR";
}
TokenType Token::getType() {
    return tokenType;
}
string Token::getValue() {
    return tokenValue;
}
