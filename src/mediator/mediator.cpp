#include "mediator.h"
#include "../ciphers/cipher_factory.h"

using namespace std;

Mediator::Mediator() {
    parsers = {
        {
            "caesar", 
            []() -> CipherBoxParser* {
                CipherFactory* factory = new CaesarFactory();
                return factory->create();
            }
        },{
            "atbash",
            []() -> CipherBoxParser* {
                CipherFactory* factory = new AtbashFactory();
                return factory->create();
            }
        },
    };
}

optional<CipherBoxParser*> Mediator::get_cipher_box_parser(string cipher_name) {
    if (parsers.find(cipher_name) == parsers.end()) {
        return nullopt;
    } else {
        return parsers.at(cipher_name)();
    }
}

unordered_map<string, function<CipherBoxParser*()>> Mediator::get_parsers() {
    return parsers;
}