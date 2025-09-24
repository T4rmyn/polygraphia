#ifndef BEAUFORT_H
#define BEAUFORT_H

#include "cipher.h"
#include "../parsers/parser.h"
#include <sys/types.h>
#include <deque>

using namespace std;
using namespace cipher;

namespace cipher {
    class BeaufortCipher: public StringKeyfulCipher, public CipherBox {
        public:
            explicit BeaufortCipher();

            void set_string_key(string value) override;
            char shift(char value, char key);
            void encrypt() override;
            void decrypt() override;
    };

    class BeaufortParser: public CipherBoxParser {
        public:
            explicit BeaufortParser(BeaufortCipher *box);
        
            void process_tokens(deque<string> *tokens) override;
    };
}

#endif