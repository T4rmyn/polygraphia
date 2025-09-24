#include "beaufort.h"
#include "cipher.h"
#include <cctype>
#include <unordered_map>
#include <sys/types.h>
#include <deque>
#include <iostream>

using namespace std;
using namespace cipher;

BeaufortCipher::BeaufortCipher(): 
    CipherBox("Beaufort Cipher", "", ""),
    StringKeyfulCipher("") {}

void BeaufortCipher::set_string_key(string key) {
    StringKeyfulCipher::set_string_key(key);
}

char BeaufortCipher::shift(char value, char key) {
    if (!isalpha(value)) {
        return value;
    }

    value = tolower(value) - 'a';
    key = tolower(key) - 'a';

    int charshift = (key - value) % 26;

    if (charshift < 0) {
        return (26 + (charshift % 26)) + 'a';
    } else {
        return (charshift) + 'a';
    }
}

void BeaufortCipher::encrypt() {
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
        cleartext[x] = shift(cleartext[x], key[y]);
        y += 1;
    }
    set_cipher_text(cleartext);
}

void BeaufortCipher::decrypt() {}

BeaufortParser::BeaufortParser(BeaufortCipher *box):
    CipherBoxParser(box) {
        unordered_map<string, deque<string>> *args = new unordered_map<string, deque<string>> {
            {"text", deque<string>()},
            {"key", deque<string>()},
        };
        set_arg_types(args);

        unordered_map<string, string> *aliases = new unordered_map<string, string> {
            {"-t", "text"},
            {"--text", "text"},
            {"-k", "key"},
            {"--key", "key"},
        };
        set_aliases(aliases);

        unordered_map<string, function<bool(CipherBoxParser*)>> *actions = new unordered_map<string, function<bool(CipherBoxParser*)>> {
            {
                "text",
                [](CipherBoxParser *parser) -> bool {
                    BeaufortCipher *beaufort = (BeaufortCipher*)parser->get_cipher_box();

                    deque<string> texts = parser->get_arg_types()->find("text")->second;

                    if (texts.empty()) {
                        cout << "Beaufort Cipher: No text inputted!\n";
                        return false;
                    }

                    if (texts.size() > 1) {
                        cout << "Beaufort Cipher: Too many text inputs!\n";
                        return false;
                    }

                    beaufort->set_clear_text(texts.front());
                    beaufort->set_cipher_text(texts.front());

                    return true;
                },
            },
            {
                "key",
                [](CipherBoxParser *parser) -> bool {
                    BeaufortCipher *beaufort = (BeaufortCipher*)parser->get_cipher_box();
                    
                    deque<string> keys = parser->get_arg_types()->find("key")->second;

                    if (keys.empty()) {
                        cout << "Beaufort Cipher: No key inputted!\n";
                        return false;
                    }

                    if (keys.size() > 1) {
                        cout << "Beaufort Cipher: Too many keys!\n";
                        return false;
                    }
                    
                    bool is_alpha = true;
                    for (char c : keys.front()) {
                        if (!isalpha(c)) {
                            is_alpha = false;
                        }
                    }

                    if (is_alpha) {
                        beaufort->set_string_key(keys.front());
                        beaufort->encrypt();
                        cout << beaufort->get_cipher_text() << endl;
                        return true;
                    } else {
                        cout << "Beaufort Cipher: Key is not all alphabetic!\n";
                        return false;
                    }
                },
            },
        };

        set_actions(actions);
    }

void BeaufortParser::process_tokens(deque<string> *tokens) {
    CipherBoxParser::process_tokens(tokens);

    bool result = get_actions()->find("text")->second(this);
    if (!result) { return; }

    result = get_actions()->find("key")->second(this);
    if (!result) { return; }
}