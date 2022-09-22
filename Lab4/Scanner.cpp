//
// Created by Gregory Knapp on 6/23/20.
//

#include "Scanner.h"


Scanner::Scanner() {
    currentLine = 0;
    fileName = "";
}

Scanner::Scanner(string file) {
    fileName = file;
    currentLine = 1;
}

Scanner::~Scanner() {
}

void Scanner::tokenize() {
    char c;
    string token;

    ifstream myfile (fileName);
    if (!myfile.is_open()) {
        cout << "Could not open file" << endl;
    }
    else {
        while(true) {

            // Check if end of file
            if (myfile.peek() == EOF) {

                // Create new token
                createAndAddToken("", ENDFILE, currentLine);
                break;
            }

            // Get next token
            c = myfile.get();
            token += c;

            // Check if Token is ID or Keyword using isalpha
            if (isalpha(c)) {

                // Get next value until it is not an alpha or digit
                while (isalpha(myfile.peek()) || isdigit(myfile.peek())) {
                    c = myfile.get();
                    token += c;
                }

                // Check for keywords - else create ID token
                if (token == "Facts") {
                    createAndAddToken(token, FACTS, currentLine);
                }
                else if (token == "Rules") {
                    createAndAddToken(token, RULES, currentLine);
                }
                else if (token == "Schemes") {
                    createAndAddToken(token, SCHEMES, currentLine);
                }
                else if (token == "Queries") {
                    createAndAddToken(token, QUERIES, currentLine);
                }
                else {
                    createAndAddToken(token, ID, currentLine);
                }
            }
            else if (!isalpha(c) && !isspace(c)) { // Check for non-ID tokens using switch statements
                int newLines = 0;

                switch(c) {
                    case ',' :
                        createAndAddToken(token, COMMA, currentLine);
                        break;
                    case '.' :
                        createAndAddToken(token, PERIOD, currentLine);
                        break;
                    case '?' :
                        createAndAddToken(token, Q_MARK, currentLine);
                        break;
                    case '(' :
                        createAndAddToken(token, LEFT_PAREN, currentLine);
                        break;
                    case ')' :
                        createAndAddToken(token, RIGHT_PAREN, currentLine);
                        break;
                    case ':' :

                        // First, check for colon dash
                        if (myfile.peek() == '-') {

                            //Create colon-dash token
                            c = myfile.get();
                            token += c;
                            createAndAddToken(token, COLON_DASH, currentLine);
                        } // Else - create colon
                        else {
                            createAndAddToken(token, COLON, currentLine);
                        }
                        break;
                    case '*' :
                        createAndAddToken(token, MULTIPLY, currentLine);
                        break;
                    case '+' :
                        createAndAddToken(token, ADD, currentLine);
                        break;
                    case '#' :

                        // Check if there is a multiline comment
                        if (myfile.peek() == '|') {

                            // Get values until the end of the comment
                            while (true) {
                                // Get next character in comment
                                c = myfile.get();
                                token += c;

                                // Increment lines if newline is found
                                if (c == '\n') {
                                    newLines += 1;
                                }

                                //Check if commment reaches end of file - make Undefined token
                                if (myfile.peek() == EOF) {
                                    token += '\n';
                                    createAndAddToken(token, UNDEFINED, currentLine);
                                    currentLine += newLines;
                                    break;
                                }

                                // Check for | then check for end of comment
                                if (c == '|') {
                                    // Look for ending comment mark # - create Comment token
                                    if (myfile.peek() == '#') {
                                        c = myfile.get();
                                        token += c;
                                        currentLine += newLines;
                                        break;
                                    }
                                }
                                // # not found - continue scanning comment
                            }
                        }
                        else { // Get single line comment until new line - create comment token

                            while (myfile.peek() != '\n') {
                                c = myfile.get();
                                token += c;
                            }
                        }
                        break;
                    case '\'' :

                        // Get values until end of string
                        while (true) {
                            // Get next value
                            c = myfile.get();
                            token += c;

                            // Increment lines if newline is found
                            if (c == '\n') {
                                newLines += 1;
                            }

                            //Check if string reaches end of file
                            if (myfile.peek() == EOF) {
                                token += '\n';
                                createAndAddToken(token, UNDEFINED, currentLine);
                                currentLine += newLines;
                                break;
                            }

                            // Check for single quote ' - check if it is the end of string or for a second '
                            if (c == '\'') {
                                // Check for consecutive '
                                if (myfile.peek() == '\'') {
                                    // If found, treat as apostrophe and continue scanning string
                                    c = myfile.get();
                                    token += c;
                                }
                                else {
                                    // End of string found, create token
                                    createAndAddToken(token, STRING, currentLine);
                                    currentLine += newLines;
                                    break;
                                }
                            }
                        }
                        break;
                    default :
                        createAndAddToken(token, UNDEFINED, currentLine);
                }
            }
            else { // Current Character is a whitespace character
                // Check if it is a newline, increment line number
                if (c == '\n') {
                    currentLine += 1;
                }
            }

            //Reset token
            token = "";
        }
        myfile.close();
    }
}


void Scanner::printTokens() {
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        cout << tokens.at(i).toString();
    }
    cout << "Total Tokens = " << tokens.size();
}
void Scanner::createAndAddToken(string token, TokenType type, int line)  {
    Token myToken(token,type,line);
    tokens.push_back(myToken);
}

vector<Token> Scanner::passVector() {
    return tokens;
}


