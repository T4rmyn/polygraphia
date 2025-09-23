#ifndef CAESAR_H
#define CAESAR_H

#include "cipher.h"
#include "../parsers/parser.h"
#include <sys/types.h>
#include <deque>

using namespace std;
using namespace cipher;

namespace cipher {
    class CaesarCipher: public NumericKeyfulCipher, public CipherBox {
        public:
            explicit CaesarCipher();

            void set_numeric_key(int value) override;
            char shift(char a, int shift);
            void encrypt() override;
            void decrypt() override;
    };

    class CaesarParser: public CipherBoxParser {
        public:
            explicit CaesarParser(CaesarCipher *box);
        
            void process_tokens(deque<string> *tokens) override;
    };
}

#endif