#include "cipher_factory.h"
#include "caesar.h"
#include "atbash.h"

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
