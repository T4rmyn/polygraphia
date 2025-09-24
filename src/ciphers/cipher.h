#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include <string>

using namespace std;

namespace cipher {
    class NumericKeyfulCipher {
        private:
            int numeric_key;

        public:
            explicit NumericKeyfulCipher(int a);

            virtual void set_numeric_key(int value);
            int get_numeric_key();
    };

    class StringKeyfulCipher {
        private:
            string string_key;
        
        public:
            explicit StringKeyfulCipher(string a);

            virtual void set_string_key(string value);
            string get_string_key();
    };

    class CipherBox {
        private:
            string cipher_name;
            string clear_text;
            string cipher_text;

        public:
            explicit CipherBox(string a, string b, string c);

            void set_cipher_name(string value);
            string get_cipher_name();

            void set_clear_text(string value);
            string get_clear_text();

            void set_cipher_text(string value);
            string get_cipher_text();

            virtual void encrypt() = 0;
            virtual void decrypt() = 0;
    };
}

#endif