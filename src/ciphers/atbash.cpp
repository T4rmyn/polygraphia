#include "atbash.h"
#include "cipher.h"
#include <iostream>
#include "../parsers/parser.h"

using namespace std;
using namespace cipher;

Atbash::Atbash():
    CipherBox("Atbash", "", "") {}

char Atbash::shift(char a) {
    if (isalpha(a)) {
        if (isupper(a)) {
            return 25 - (a - 'A') + 'A';
        } else {
            return 25 - (a - 'a') + 'a';
        }
    }
    return a;
} 
    
void Atbash::encrypt() {
    string cipher = get_clear_text();
    for (int i = 0; i < cipher.length(); i++) {
        cipher[i] = shift(cipher[i]);
    }
    set_cipher_text(cipher);
}

void Atbash::decrypt() {
    string clear = get_cipher_text();
    for (int i = 0; i < clear.length(); i++) {
        clear[i] = shift(clear[i]);
    }
    set_clear_text(clear);
}

AtbashParser::AtbashParser(Atbash *box):
    CipherBoxParser(box) {
        unordered_map<string, deque<string>> *args = new unordered_map<string, deque<string>> {
            {"text", deque<string>()},
            {"mode", deque<string>()},
        };
        set_arg_types(args);

        unordered_map<string, string> *aliases = new unordered_map<string, string> {
            {"-t", "text"},
            {"--text", "text"},
            {"-m", "mode"},
            {"--mode", "mode"},
        };
        set_aliases(aliases);

        unordered_map<string, function<bool(CipherBoxParser*)>> *actions = new unordered_map<string, function<bool(CipherBoxParser*)>> {
            {
                "text",
                [](CipherBoxParser *parser) -> bool {
                    Atbash *atbash = (Atbash*)parser->get_cipher_box();

                    deque<string> texts = parser->get_arg_types()->find("text")->second;
                    if (texts.size() > 1) {
                        cout << "Atbash: Too many text inputs!\n";
                        return false;
                    }

                    atbash->set_clear_text(texts.front());
                    atbash->set_cipher_text(texts.front());

                    return true;
                },
            },
            {
                "mode",
                [](CipherBoxParser *parser) -> bool {
                    Atbash *atbash = (Atbash*)parser->get_cipher_box();

                    deque<string> modes = parser->get_arg_types()->find("mode")->second;
                    if (modes.empty()) {
                        modes.push_back("encrypt");
                    }
                    if (modes.size() > 1) {
                        cout << "Atbash: Too many modes!\n";
                        return false;
                    }

                    if (modes.front().compare("encrypt") == 0) {
                        atbash->encrypt();
                        cout << atbash->get_cipher_text() << endl;
                    } else if (modes.front().compare("decrypt") == 0) {
                        atbash->decrypt();
                        cout << atbash->get_clear_text() << endl;
                    } else {
                        cout << "Atbash: Mode not recognized!\n";
                        return false;
                    }
                    return true;
                },
            },
        };

        set_actions(actions);
    }

void AtbashParser::process_tokens(deque<string> *tokens) {
    CipherBoxParser::process_tokens(tokens);

    bool result = get_actions()->find("text")->second(this);
    if (!result) { return; }

    result = get_actions()->find("mode")->second(this);
    if (!result) { return; }
}
