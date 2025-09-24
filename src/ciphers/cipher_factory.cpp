#include "cipher_factory.h"
#include "beaufort.h"
#include "caesar.h"
#include "atbash.h"
#include "vigenere.h"

CipherBoxParser* AtbashFactory::create() {
    Atbash *box = new Atbash();
    AtbashParser *parser = new AtbashParser(box);
    return parser;
}

CipherBoxParser* CaesarFactory::create() {
    CaesarCipher *box = new CaesarCipher();
    CaesarParser *parser = new CaesarParser(box);
    return parser;
}

CipherBoxParser* VigenereFactory::create() {
    VigenereCipher *box = new VigenereCipher();
    VigenereParser *parser = new VigenereParser(box);
    return parser;
}


CipherBoxParser* BeaufortFactory::create() {
    BeaufortCipher *box = new BeaufortCipher();
    BeaufortParser *parser = new BeaufortParser(box);
    return parser;
}