#include "caesar.h"
#include "cipher.h"
#include <cctype>
#include <unordered_map>
#include <sys/types.h>
#include <deque>
#include <iostream>

using namespace std;
using namespace cipher;

CaesarCipher::CaesarCipher(): 
    CipherBox("Caesar Cipher", "", ""),
    NumericKeyfulCipher(0) {}

void CaesarCipher::set_numeric_key(int value) {
    NumericKeyfulCipher::set_numeric_key(value % 26);
}
        
char CaesarCipher::shift(char a, int shift) {
    if (shift < 0) {
        shift = 26 + (shift % 26);
    }
    if (isalpha(a)) {
        if (islower(a)) {
            return (((a - 'a') % 26) + shift) % 26 + 'a';
        } else {
            return (((a - 'A') % 26) + shift) % 26 + 'A';
        }
    } else {
        return a;
    }
} 

void CaesarCipher::encrypt() {
    string cipher = get_clear_text();
    uint length = cipher.length();
    for (int x = 0; x < length; x++) {
        cipher[x] = shift(cipher[x], get_numeric_key());
    }
    set_cipher_text(cipher);
}

void CaesarCipher::decrypt() {
    string cipher = get_cipher_text();
    uint length = cipher.length();
    for (int x = 0; x < length; x++) {
        cipher[x] = shift(cipher[x], -get_numeric_key());
    }
    set_clear_text(cipher);
}

CaesarParser::CaesarParser(CaesarCipher *box):
    CipherBoxParser(box) {
        unordered_map<string, deque<string>> *args = new unordered_map<string, deque<string>> {
            {"text", deque<string>()},
            {"key", deque<string>()},
            {"mode", deque<string>()},
        };
        set_arg_types(args);

        unordered_map<string, string> *aliases = new unordered_map<string, string> {
            {"-t", "text"},
            {"--text", "text"},
            {"-k", "key"},
            {"--key", "key"},
            {"-m", "mode"},
            {"--mode", "mode"},
        };
        set_aliases(aliases);

        unordered_map<string, function<bool(CipherBoxParser*)>> *actions = new unordered_map<string, function<bool(CipherBoxParser*)>> {
            {
                "text",
                [](CipherBoxParser *parser) -> bool {
                    CaesarCipher *caesar = (CaesarCipher*)parser->get_cipher_box();

                    deque<string> texts = parser->get_arg_types()->find("text")->second;

                    if (texts.empty()) {
                        cout << "Caesar Cipher: No text inputted!\n";
                        return false;
                    }

                    if (texts.size() > 1) {
                        cout << "Caesar Cipher: Too many text inputs!\n";
                        return false;
                    }

                    caesar->set_clear_text(texts.front());
                    caesar->set_cipher_text(texts.front());

                    return true;
                },
            },
            {
                "key",
                [](CipherBoxParser *parser) -> bool {
                    CaesarCipher *caesar = (CaesarCipher*)parser->get_cipher_box();
                    
                    deque<string> keys = parser->get_arg_types()->find("key")->second;

                    if (keys.empty()) {
                        cout << "Caesar Cipher: No key inputted!\n";
                        return false;
                    }

                    if (keys.size() > 1) {
                        cout << "Caesar Cipher: Too many keys!\n";
                        return false;
                    }
                    
                    try {
                        caesar->set_numeric_key(stoi(keys.front()));
                        return true;
                    } catch(...) {
                        cout << "Caesar Cipher: Key is not an integer!\n";
                        return false;
                    }
                },
            },
            {
                "mode",
                [](CipherBoxParser *parser) -> bool {
                    CaesarCipher *caesar = (CaesarCipher*)parser->get_cipher_box();

                    deque<string> modes = parser->get_arg_types()->find("mode")->second;
                    if (modes.empty()) {
                        modes.push_back("encrypt");
                    }
                    if (modes.size() > 1) {
                        cout << "Caesar Cipher: Too many modes!\n";
                        return false;
                    }

                    if (modes.front().compare("encrypt") == 0) {
                        caesar->encrypt();
                        cout << caesar->get_cipher_text() << endl;
                    } else if (modes.front().compare("decrypt") == 0) {
                        caesar->decrypt();
                        cout << caesar->get_clear_text() << endl;
                    } else {
                        cout << "Caesar Cipher: Mode not recognized!\n";
                        return false;
                    }
                    return true;
                },
            },
        };

        set_actions(actions);
    }

void CaesarParser::process_tokens(deque<string> *tokens) {
    CipherBoxParser::process_tokens(tokens);

    bool result = get_actions()->find("text")->second(this);
    if (!result) { return; }

    result = get_actions()->find("key")->second(this);
    if (!result) { return; }

    result = get_actions()->find("mode")->second(this);
    if (!result) { return; }
}