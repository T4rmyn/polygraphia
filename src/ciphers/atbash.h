#ifndef ATBASH_H
#define ATBASH_H

#include "cipher.h"
#include "../parsers/parser.h"

using namespace std;
using namespace cipher;

namespace cipher {
    class Atbash: public CipherBox {
        public:
            explicit Atbash();

            char shift(char a);
            void encrypt() override;
            void decrypt() override;
    };

    class AtbashParser: public CipherBoxParser {
        public:
            AtbashParser(Atbash *box);
        
            void process_tokens(deque<string> *tokens) override;
    };
}

#endif