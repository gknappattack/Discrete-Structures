#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Database.h"

using namespace std;

int main(int argc, char* argv[]) {
    string filename = argv[1];

    Scanner myScanner(filename);
    myScanner.tokenize();

    vector<Token> myTokens = myScanner.passVector();

    Parser myParser(myTokens);

    myParser.parse();

    Database myDatabase(myParser.passLog());
    myDatabase.createDatabase();


    return 0;
}