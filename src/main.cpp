#include <iostream>
#include <deque>
#include "parsers/terminal_parser.h"
using namespace std;
using namespace cipher;

int main(int argc, char *argv[]) {
    TerminalParser *parser = new TerminalParser();
    deque<string> *tokens = new deque<string>();
    for (int i = 0; i < argc; i++) {
        string token = string(argv[i]);
        tokens->push_back(token);
    }
    tokens->pop_front();
    parser->process_tokens(tokens);

    return 0;
}