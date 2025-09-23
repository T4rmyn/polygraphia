#ifndef PARSER_H
#define PARSER_H

#include "../ciphers/cipher.h"
#include <deque>
#include <functional>
#include <unordered_map>

using namespace std;
using namespace cipher;

class BaseParser {
    public:
        virtual void process_tokens(deque<string> *tokens) = 0;
};

class CipherBoxParser: public BaseParser {
    private:
        CipherBox *cipher_box;
        unordered_map<string, deque<string>> *arg_types;
        unordered_map<string, string> *aliases;
        unordered_map<string, function<bool(CipherBoxParser*)>> *actions;
    
    public:
        explicit CipherBoxParser(CipherBox *a);

        virtual void process_tokens(deque<string> *tokens);

        void set_cipher_box(CipherBox *value);
        CipherBox* get_cipher_box();

        void set_arg_types(unordered_map<string, deque<string>> *value);
        unordered_map<string, deque<string>>* get_arg_types();

        void set_aliases(unordered_map<string, string> *value);
        unordered_map<string, string>* get_aliases();

        void set_actions(unordered_map<string, function<bool(CipherBoxParser*)>> *value);
        unordered_map<string, function<bool(CipherBoxParser*)>>* get_actions();
};

#endif