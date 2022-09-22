//
// Created by Gregory Knapp on 6/30/20.
//

#include "Parser.h"

Parser::Parser(vector<Token> list) {
    tokenList = list;
    tokenNum = 0;
    isExpression = false;
}

Parser::~Parser() = default;

void Parser::parse() {
    currentToken = tokenList.at(0);
    tokenNum += 1;

    try {
        parseDatalogProgram();
    }
    catch (Token error) {
        cout << "Failure!" << endl;
        cout << "  " << error.toString();
        return;
    }

    //cout << "Success!" << endl;

}

void Parser::parseDatalogProgram() {
    match(SCHEMES);
    match(COLON);
    parseScheme();
    parseSchemeList();
    match(FACTS);
    match(COLON);
    if (currentToken.getType() == ID) {
        parseFactList();
    }
    match(RULES);
    match(COLON);
    if (currentToken.getType() == ID) {
        parseRuleList();
    }
    myPredicate.clear();
    match(QUERIES);
    match(COLON);
    parseQuery();
    if (currentToken.getType() != ENDFILE) {
        parseQueryList();
    }
}

void Parser::parseScheme() {
    myPredicate.setID(currentToken.getValue());
    match(ID);
    match(LEFT_PAREN);
    myPredicate.addToVector(currentToken.getValue());
    match(ID);
    parseIDList();
    match(RIGHT_PAREN);
    myDatalog.addScheme(myPredicate);
}

void Parser::parseFact() {
    myPredicate.setID(currentToken.getValue());
    match(ID);
    match(LEFT_PAREN);
    myPredicate.addToVector(currentToken.getValue());
    myDatalog.addDomain(currentToken.getValue());
    match(STRING);
    parseStringList();
    match(RIGHT_PAREN);
    match(PERIOD);
    myDatalog.addFact(myPredicate);
}

void Parser::parseRule() {
    parseHeadPredicate();
    match(COLON_DASH);
    myPredicate.clear();

    parsePredicate();
    parsePredicateList();
    myDatalog.addRule(myRule);
    match(PERIOD);
}

void Parser::parseQuery() {
    parsePredicate();
    match(Q_MARK);
    myDatalog.addQuery(myPredicate);
}

void Parser::parseSchemeList() {
    myPredicate.clear();
    if (currentToken.getType() == ID) {
        parseScheme();
        parseSchemeList();
    }
}

void Parser::parseFactList() {
    myPredicate.clear();
    parseFact();
    if (currentToken.getType() == ID) {
        parseFactList();
    }
}

void Parser::parseRuleList() {
    myPredicate.clear();
    myRule.clear();
    parseRule();
    if (currentToken.getType() == ID) {
        parseRuleList();
    }

}

void Parser::parseQueryList() {
    myPredicate.clear();
    if (currentToken.getType() == ID) {
        parseQuery();
        parseQueryList();
    }
}

void Parser::parseHeadPredicate() {
    myPredicate.setID(currentToken.getValue());
    match(ID);
    match(LEFT_PAREN);
    myPredicate.addToVector(currentToken.getValue());
    match(ID);
    parseIDList();
    match(RIGHT_PAREN);
    myRule.addHeadPredicate(myPredicate);
}

void Parser::parsePredicate() {
    myPredicate.setID(currentToken.getValue());
    match(ID);
    match(LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(RIGHT_PAREN);
}

void Parser::parsePredicateList() {
    myRule.addToVector(myPredicate);
    myPredicate.clear();

    if (currentToken.getType() == COMMA) {
        match(COMMA);
        parsePredicate();
        parsePredicateList();
    }
}

void Parser::parseParameterList() {
    if (isExpression) {
        myPredicate.addToVector(myExpression);
        isExpression = false;
        myExpression.clear();
    }

    if (currentToken.getType() == COMMA) {
        match(COMMA);
        parseParameter();


        parseParameterList();
    }
}

void Parser::parseStringList() {
    if (currentToken.getType() == COMMA) {
        match(COMMA);
        myPredicate.addToVector(currentToken.getValue());
        myDatalog.addDomain(currentToken.getValue());
        match(STRING);
        parseStringList();
    }
}

void Parser::parseIDList() {
    if (currentToken.getType() == COMMA) {
        match(COMMA);
        myPredicate.addToVector(currentToken.getValue());
        match(ID);
        parseIDList();
    }
}

void Parser::parseParameter() {
    if (currentToken.getType() == STRING) {

        if (!isExpression) {
            myPredicate.addToVector(currentToken.getValue());
        }
        else {
            myExpression += currentToken.getValue();
        }

        match(STRING);
    }
    else if (currentToken.getType() == ID) {

        if (!isExpression) {
            myPredicate.addToVector(currentToken.getValue());
        }
        else {
            myExpression += currentToken.getValue();
        }
        match(ID);
    }
    else {
        parseExpression();
    }
}

void Parser::parseExpression() {
    isExpression = true;
    myExpression += currentToken.getValue();
    match(LEFT_PAREN);
    parseParameter();
    parseOperator();
    parseParameter();
    myExpression += currentToken.getValue();
    match(RIGHT_PAREN);
}

void Parser::parseOperator() {
    if (currentToken.getType() == ADD) {
        myExpression += currentToken.getValue();
        match(ADD);
    }
    else if (currentToken.getType() == MULTIPLY) {
        myExpression += currentToken.getValue();
        match(MULTIPLY);
    }
    else {
        throw currentToken;
    }
}

void Parser::match(TokenType t) {
    if (t == currentToken.getType()) {
        getToken();
    }
    else {
        throw currentToken;
    }
}

void Parser::getToken() {
    currentToken = tokenList.at(tokenNum);
    tokenNum += 1;
}

DatalogProgram Parser::passLog() {
    return myDatalog;
}

//TODO: remove debug statements, check by writing output to file