//
// Created by Gregory Knapp on 6/23/20.
//

#ifndef LAB1_SCANNER_H
#define LAB1_SCANNER_H

#include "Token.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>


using namespace std;

class Scanner {
public:
    Scanner();
    Scanner(string file);
    ~Scanner();
    void tokenize();
    void printTokens();
    void createAndAddToken(string token, TokenType type, int line);
private:
    string fileName;
    int currentLine;
    vector<Token> tokens;
};

#endif //LAB1_SCANNER_H
