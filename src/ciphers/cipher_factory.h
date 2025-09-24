#ifndef CIPHERFACTORY_H
#define CIPHERFACTORY_H

#include "beaufort.h"
#include "cipher.h"
#include "../parsers/parser.h"

namespace cipher {
    class CipherFactory {
        public:
            virtual CipherBoxParser* create() = 0;
    };

    class AtbashFactory: public CipherFactory {
        public:
            CipherBoxParser* create() override;
    };

    class CaesarFactory: public CipherFactory {
        public:
            CipherBoxParser* create() override;
    };

    class VigenereFactory: public CipherFactory {
        public:
            CipherBoxParser* create() override;
    };

    class BeaufortFactory: public CipherFactory {
        public:
            CipherBoxParser* create() override;
    };
}

#endif