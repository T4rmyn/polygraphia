#include "cipher.h"
#include <string>

using namespace std;
using namespace cipher;

NumericKeyfulCipher::NumericKeyfulCipher(int a) {
    numeric_key = a;
}

void NumericKeyfulCipher::set_numeric_key(int value) {
    numeric_key = value;
}

int NumericKeyfulCipher::get_numeric_key() {
    return numeric_key;
}
        
StringKeyfulCipher::StringKeyfulCipher(string a) {
    string_key = a;
}

void StringKeyfulCipher::set_string_key(string value) {
    string_key = value;
}

string StringKeyfulCipher::get_string_key() {
    return string_key;
}

CipherBox::CipherBox(string a, string b, string c) {
    cipher_name = a;
    clear_text = b;
    cipher_text = c;
}

void CipherBox::set_cipher_name(string value) {
    cipher_name = value;
}

string CipherBox::get_cipher_name() {
    return cipher_name;
}

void CipherBox::set_clear_text(string value) {
    clear_text = value;
}

string CipherBox::get_clear_text() {
    return clear_text;
}

void CipherBox::set_cipher_text(string value) {
    cipher_text = value;
}

string CipherBox::get_cipher_text() {
    return cipher_text;
}