#include "parser.h"
#include <functional>

CipherBoxParser::CipherBoxParser(CipherBox *a) {
    cipher_box = a;
    arg_types = new unordered_map<string, deque<string>>();
}

void CipherBoxParser::process_tokens(deque<string> *tokens) {
    for (int i = 0 ; i < tokens->size(); i++) {
        unordered_map<string, string>::iterator arg_type = get_aliases()->find(tokens->at(i));
        if (arg_type == get_aliases()->end()) {
            return;
        } else {
            for (int j = i + 1; j < tokens->size(); j++) {
                if (get_aliases()->find(tokens->at(j)) == get_aliases()->end()) {
                    get_arg_types()->find(arg_type->second)->second.push_back(tokens->at(j));
                } else {
                    i = j - 1;
                    break;
                }
            }
        }
        if (i == tokens->size() - 2) {
            break;
        }
    }
}

void CipherBoxParser::set_cipher_box(CipherBox *value) {
    cipher_box = value;
}
CipherBox* CipherBoxParser::get_cipher_box() {
    return cipher_box;
}

void CipherBoxParser::set_arg_types(unordered_map<string, deque<string>> *value) {
    arg_types = value;
};
unordered_map<string, deque<string>>* CipherBoxParser::get_arg_types() {
    return arg_types;
}

void CipherBoxParser::set_aliases(unordered_map<string, string> *value) {
    aliases = value;
}
unordered_map<string, string>* CipherBoxParser::get_aliases() {
    return aliases;
}

void CipherBoxParser::set_actions(unordered_map<string, function<bool(CipherBoxParser*)>> *value) {
    actions = value;
}
unordered_map<string, function<bool(CipherBoxParser*)>>* CipherBoxParser::get_actions() {
    return actions;
}