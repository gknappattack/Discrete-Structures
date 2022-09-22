#include <iostream>
#include "Scanner.h"

using namespace std;

int main(int argc, char* argv[]) {
    string filename = argv[1];

    Scanner myScanner(filename);
    myScanner.tokenize();
    myScanner.printTokens();

    return 0;
}