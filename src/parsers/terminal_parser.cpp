#include "terminal_parser.h"
#include "../mediator/mediator.h"
#include <optional>
#include <iostream>

void TerminalParser::process_tokens(deque<string> *tokens) {
    if (tokens->empty()) {
        cout << "no\n";
    } else {
        string first_arg = tokens->front();
        Mediator *mediator = new Mediator();

        optional<CipherBoxParser*> cipher_box = mediator->get_cipher_box_parser(first_arg);
        if (cipher_box.has_value()) {
            tokens->pop_front();
            cipher_box.value()->process_tokens(tokens);
        } else {
            cout << "no3\n";
        }
    }
}