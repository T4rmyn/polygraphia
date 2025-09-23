#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <functional>
#include <unordered_map>
#include <optional>
#include <string>
#include "../parsers/parser.h"

using namespace std;
using namespace cipher;

class Mediator {
    private:
        unordered_map<string, function<CipherBoxParser*()>> parsers;

    public:
        Mediator();
        optional<CipherBoxParser*> get_cipher_box_parser(string cipher_name);
        unordered_map<string, function<CipherBoxParser*()>> get_parsers();
};

#endif