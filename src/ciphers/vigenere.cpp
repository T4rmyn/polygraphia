#include "vigenere.h"
#include "cipher.h"
#include <cctype>
#include <unordered_map>
#include <sys/types.h>
#include <deque>
#include <iostream>

using namespace std;
using namespace cipher;

VigenereCipher::VigenereCipher(): 
    CipherBox("Vigenere Cipher", "", ""),
    StringKeyfulCipher("") {}

void VigenereCipher::set_string_key(string key) {
    StringKeyfulCipher::set_string_key(key);
}

char VigenereCipher::shift(char value, char key, bool encrypt) {
    if (!isalpha(value)) {
        return value;
    }

    value = tolower(value) - 'a';
    key = tolower(key) - 'a';

    if (encrypt) {
        return ((value + key) % 26) + 'a';
    } else {
        int charshift = value - key;
        if (charshift < 0) {
            return (26 + (charshift % 26)) + 'a';
        } else {
            return ((value - key) % 26) + 'a';
        }
    }
}

void VigenereCipher::encrypt() {
    string cleartext = get_clear_text();
    string key = get_string_key();
    uint length = cleartext.length();
    uint keylen = key.length();
    int y = 0;
    for (int x = 0; x < length; x++) {
        if (!isalpha(cleartext[x])) {
            continue;
        }
        if (y >= keylen) {
            y = 0;
        }
        cleartext[x] = shift(cleartext[x], key[y], true);
        cout << cleartext << endl;
        y += 1;
    }
    set_cipher_text(cleartext);
}

void VigenereCipher::decrypt() {
    string ciphertext = get_cipher_text();
    string key = get_string_key();
    uint length = ciphertext.length();
    uint keylen = key.length();
    int y = 0;
    for (int x = 0; x < length; x++) {
        if (!isalpha(ciphertext[x])) {
            continue;
        }
        if (y >= keylen) {
            y = 0;
        }
        ciphertext[x] = shift(ciphertext[x], key[y], false);
        y += 1;
    }
    set_clear_text(ciphertext);
}

VigenereParser::VigenereParser(VigenereCipher *box):
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
                    VigenereCipher *vigenere = (VigenereCipher*)parser->get_cipher_box();

                    deque<string> texts = parser->get_arg_types()->find("text")->second;

                    if (texts.empty()) {
                        cout << "Vigenere Cipher: No text inputted!\n";
                        return false;
                    }

                    if (texts.size() > 1) {
                        cout << "Vigenere Cipher: Too many text inputs!\n";
                        return false;
                    }

                    vigenere->set_clear_text(texts.front());
                    vigenere->set_cipher_text(texts.front());

                    return true;
                },
            },
            {
                "key",
                [](CipherBoxParser *parser) -> bool {
                    VigenereCipher *vigenere = (VigenereCipher*)parser->get_cipher_box();
                    
                    deque<string> keys = parser->get_arg_types()->find("key")->second;

                    if (keys.empty()) {
                        cout << "Vigenere Cipher: No key inputted!\n";
                        return false;
                    }

                    if (keys.size() > 1) {
                        cout << "Vigenere Cipher: Too many keys!\n";
                        return false;
                    }
                    
                    bool is_alpha = true;
                    for (char c : keys.front()) {
                        if (!isalpha(c)) {
                            is_alpha = false;
                        }
                    }

                    if (is_alpha) {
                        vigenere->set_string_key(keys.front());
                        return true;
                    } else {
                        cout << "Vigenere Cipher: Key is not all alphabetic!\n";
                        return false;
                    }
                },
            },
            {
                "mode",
                [](CipherBoxParser *parser) -> bool {
                    VigenereCipher *vigenere = (VigenereCipher*)parser->get_cipher_box();

                    deque<string> modes = parser->get_arg_types()->find("mode")->second;
                    if (modes.empty()) {
                        modes.push_back("encrypt");
                    }
                    if (modes.size() > 1) {
                        cout << "Vigenere Cipher: Too many modes!\n";
                        return false;
                    }

                    if (modes.front().compare("encrypt") == 0) {
                        vigenere->encrypt();
                        cout << vigenere->get_cipher_text() << endl;
                    } else if (modes.front().compare("decrypt") == 0) {
                        vigenere->decrypt();
                        cout << vigenere->get_clear_text() << endl;
                    } else {
                        cout << "Vigenere Cipher: Mode not recognized!\n";
                        return false;
                    }
                    return true;
                },
            },
        };

        set_actions(actions);
    }

void VigenereParser::process_tokens(deque<string> *tokens) {
    CipherBoxParser::process_tokens(tokens);

    bool result = get_actions()->find("text")->second(this);
    if (!result) { return; }

    result = get_actions()->find("key")->second(this);
    if (!result) { return; }

    result = get_actions()->find("mode")->second(this);
    if (!result) { return; }
}