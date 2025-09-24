#ifndef VIGENERE_H
#define VIGENERE_H

#include "cipher.h"
#include "../parsers/parser.h"
#include <sys/types.h>
#include <deque>

using namespace std;
using namespace cipher;

namespace cipher {
    class VigenereCipher: public StringKeyfulCipher, public CipherBox {
        public:
            explicit VigenereCipher();

            void set_string_key(string value) override;
            char shift(char value, char key, bool encrypt);
            void encrypt() override;
            void decrypt() override;
    };

    class VigenereParser: public CipherBoxParser {
        public:
            explicit VigenereParser(VigenereCipher *box);
        
            void process_tokens(deque<string> *tokens) override;
    };
}

#endif